#include "iframe_repository.h"
#include "vision/db/irepository_factory.h"
#include "vision/db/repository_factory_mapping.h"

#include <absl/synchronization/mutex.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <condition_variable>
#include <cstdlib>
#include <google/protobuf/duration.pb.h>
#include <google/protobuf/text_format.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <google/protobuf/util/time_util.h>
#include <protocols/common/robot_id.pb.h>
#include <protocols/third_party/detection/raw_wrapper.pb.h>
#include <protocols/ui/messages.pb.h>
#include <protocols/vision/frame.pb.h>
#include <random>
#include <robocin/concurrency/thread_pool.h>
#include <robocin/network/zmq_publisher_socket.h>
#include <robocin/network/zmq_request_reply_socket.h>
#include <robocin/network/zmq_subscriber_socket.h>
#include <span>
#include <string>
#include <thread>

using protocols::third_party::detection::SSL_DetectionRobot;
using protocols::third_party::detection::SSL_WrapperPacket;
using protocols::vision::Frame;
using protocols::vision::Robot;

using RobotIdColor = protocols::common::RobotId::Color;

using robocin::ThreadPool;
using robocin::ZmqDatagram;

using vision::IFrameRepository;
using vision::RepositoryFactoryMapping;
using vision::RepositoryType;

const uint64_t kFPS = 80;
uint64_t frame_id = 1;

const auto kFactory = RepositoryFactoryMapping{}[RepositoryType::MongoDb];
std::unique_ptr<IFrameRepository> frame_repository = kFactory->createFrameRepository();

// Database:

// saves a frame to the database.
void saveToDatabase(IFrameRepository& repository, const Frame& frame) { repository.save(frame); }

// fetches a frame range from the database.
std::vector<Frame> findRangeFromDatabase(IFrameRepository& repository,
                                     const int64_t& key_lower_bound,
                                     const int64_t& key_upper_bound) {
  return repository.findRange(key_lower_bound, key_upper_bound);
}


static constexpr std::string_view kThirdPartyAddress = "ipc:///tmp/gateway-pub-th-parties.ipc";
static constexpr std::string_view kVisionMessageTopic = "vision-third-party";
static constexpr std::string_view kVisionPublisherAddress = "ipc:///tmp/vision-async.ipc";

ThreadPool thread_pool(4);

std::mutex mutex;
std::condition_variable cv;
std::vector<ZmqDatagram> packages;

void subscriberRun() {
  std::cout << "Subscriber thread running..." << std::endl;
  robocin::ZmqSubscriberSocket vision_third_party_socket{};
  vision_third_party_socket.connect(kThirdPartyAddress, std::span{&kVisionMessageTopic, 1});

  uint64_t total_msgs_received = 0;

  while (true) {
    {
      std::lock_guard lock(mutex);

      while (true) {
        auto message = vision_third_party_socket.receive();
        if (message.message.empty()) {
          break;
        }
        // std::cout << std::format("received message!, total: {}", total_msgs_received++) <<
        // std::endl;
        packages.push_back(message);
      }
    }

    cv.notify_one();
  }
}

Frame mapWrapperPacketToFrame(const SSL_WrapperPacket& packet);

Frame parseMessage(std::string message) {
  SSL_WrapperPacket packet;
  packet.ParseFromString(message);

  Frame frame = mapWrapperPacketToFrame(packet);
  return frame;
}

void publisherRun() {
  std::cout << "Publisher thread running..." << std::endl;
  robocin::ZmqPublisherSocket vision_publisher;
  vision_publisher.bind(kVisionPublisherAddress);

  // Receive datagrams.
  while (true) {
    std::optional<Frame> processedFrame; 

    std::vector<ZmqDatagram> datagrams;
    {
      std::unique_lock lock(mutex);
      cv.wait(lock, [&] { return !packages.empty(); });

      datagrams.swap(packages);
    }

    // TODO($ISSUE_N): Move this workflow to a DatagramHandler class.
    for (auto& datagram : datagrams) {

      auto topic = datagram.topic;
      if (topic == kVisionMessageTopic) {
        SSL_WrapperPacket detection;
        detection.ParseFromString(datagram.message);
        processedFrame = parseMessage(datagram.message);  
      } else {
        std::cout << std::format("unexpected topic for ZmqDatagram: expect {}, got: {} instead.",
                                 kVisionMessageTopic,
                                 topic)
                  << std::endl;
      }
    }

    if(processedFrame.has_value()) {
      auto serialized_frame = processedFrame.value().SerializeAsString();
      vision_publisher.send("frame", serialized_frame);
      thread_pool.enqueue(saveToDatabase, std::ref(*frame_repository), std::cref(processedFrame.value()));
    }
  }
}

static constexpr std::string_view kReplyAddress = "ipc:///tmp/vision-sync.ipc";
void databaseHandlerRun() {
  std::cout << "Database thread running..." << std::endl;
  robocin::ZmqReplySocket vision_reply_socket{};
  vision_reply_socket.bind(kReplyAddress);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int64_t> distribution(1, 6);

  // Receive sync request.
  while (true) {
    if (auto request = vision_reply_socket.receive(); !request.empty()) {
      std::cout << "GetVisionChunk on VisionMS..." << std::endl;
      int64_t first_key = distribution(gen);
      int64_t second_key = distribution(gen);
      auto [lower, upper] = std::minmax(first_key, second_key);

      auto range
          = thread_pool.enqueue(findRangeFromDatabase, std::ref(*frame_repository), lower,
          upper);
          
      protocols::ui::GetVisionChunkResponse response;
      protocols::ui::ChunkResponseHeader &header = *response.mutable_header();
      header.mutable_request_start()->set_seconds(0);
      header.set_chunk_id(1);
      header.set_n_chunks(1);
      header.mutable_max_duration()->set_seconds(0);

      for (auto& frame : range.get()) {
        response.add_payloads()->CopyFrom(frame);
      }

      std::string serialized_response;
      response.SerializeToString(&serialized_response);
      vision_reply_socket.send(serialized_response);
    }
  }
}

int main() {
  std::cout << "Vision is runnning!" << std::endl;

  // TODO($ISSUE_N): Move the database management to a class.
  std::cout << "Creating factory and frame repository." << std::endl;

  std::future<bool> connection_status = frame_repository->connect();

  if (connection_status.wait(); connection_status.get()) {
    std::cout << "Connected to the database." << std::endl;
  } else {
    std::cout << "Failed to connect to the database." << std::endl;
    return -1;
  }

  std::jthread publisher_thread(publisherRun);
  std::jthread subscriber_thread(subscriberRun);
  std::jthread database_thread(databaseHandlerRun);

  return 0;
}


google::protobuf::Timestamp protobufTimestampNow() {
  return google::protobuf::util::TimeUtil::GetCurrentTime();
}

Robot mapWrapperRobotToRobot(const SSL_DetectionRobot& packet_robot, RobotIdColor color) {
  Robot robot;

  auto& robot_id = *robot.mutable_robot_id();
  robot_id.set_number(static_cast<int>(packet_robot.robot_id()));
  robot_id.set_color(color);

  robot.set_confidence(packet_robot.confidence());

  auto& position = *robot.mutable_position();
  position.set_x(packet_robot.x());
  position.set_y(packet_robot.y());

  robot.set_angle(packet_robot.orientation());

  // just to increase message size.
  auto& velocity = *robot.mutable_velocity();
  velocity.set_x(0);
  velocity.set_y(0);

  robot.set_angular_velocity(0);

  return robot;
};

Frame mapWrapperPacketToFrame(const SSL_WrapperPacket& packet) {
  static uint64_t serial_id = 0;
  static uint64_t field_serial_id = 0;

  Frame frame;

  auto& properties = *frame.mutable_properties();
  properties.set_serial_id(serial_id++);
  *properties.mutable_created_at() = protobufTimestampNow();
  properties.set_fps(60.0F); // NOLINT(*numbers*)

  for (const auto& packet_ball : packet.detection().balls()) {
    auto& ball = *frame.add_balls();

    ball.set_confidence(packet_ball.confidence());

    auto& position = *ball.mutable_position();
    position.set_x(packet_ball.x());
    position.set_y(packet_ball.y());
    position.set_z(packet_ball.z());

    // just to increase message size.
    auto& velocity = *ball.mutable_velocity();
    velocity.set_x(0);
    velocity.set_y(0);
    velocity.set_z(0);
  }

  for (const auto& packet_robot : packet.detection().robots_yellow()) {
    *frame.add_robots()
        = mapWrapperRobotToRobot(packet_robot, RobotIdColor::RobotId_Color_COLOR_YELLOW);
  }
  for (const auto& packet_robot : packet.detection().robots_blue()) {
    *frame.add_robots()
        = mapWrapperRobotToRobot(packet_robot, RobotIdColor::RobotId_Color_COLOR_BLUE);
  }

  if (packet.has_geometry()) {
    auto& field = *frame.mutable_field();
    field.set_serial_id(field_serial_id++);

    // NOLINTBEGIN(*conversions*)
    field.set_length(packet.geometry().field().field_length());
    field.set_width(packet.geometry().field().field_width());
    field.set_goal_depth(packet.geometry().field().goal_depth());
    field.set_goal_width(packet.geometry().field().goal_width());
    field.set_penalty_area_depth(packet.geometry().field().penalty_area_depth());
    field.set_penalty_area_width(packet.geometry().field().penalty_area_width());
    field.set_boundary_width(packet.geometry().field().boundary_width());
    field.set_goal_center_to_penalty_mark(packet.geometry().field().goal_center_to_penalty_mark());
    // NOLINTEND(*conversions*)
  }

  return frame;
}
