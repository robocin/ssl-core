#include "decision/controller/producer_controller.h"

#include <memory>
#include <print>
#include <robocin/detection_util/clock.h>
#include <robocin/memory/object_ptr.h>
#include <robocin/network/zmq_poller.h>
#include <robocin/network/zmq_subscriber_socket.h>
#include <robocin/parameters/parameters.h>
#include <robocin/wip/service_discovery/addresses.h>
#include <thread>

namespace parameters = ::robocin::parameters;
namespace detection_util = ::robocin::detection_util;
namespace service_discovery = robocin::service_discovery;

using decision::IController;
using decision::IMessageReceiver;
using decision::IPayloadMapper;
using decision::MessageReceiver;
using decision::Payload;
using decision::PayloadMapper;
using decision::ProducerController;
using ::robocin::ConditionVariableConcurrentQueue;
using ::robocin::IConcurrentQueue;
using ::robocin::IZmqPoller;
using ::robocin::IZmqSubscriberSocket;
using ::robocin::object_ptr;
using ::robocin::ZmqPoller;
using ::robocin::ZmqSubscriberSocket;

std::unique_ptr<IMessageReceiver> makeMessageReceiver() {
  static constexpr std::array kPerceptionTopics = {
      service_discovery::kPerceptionDetectionTopic,
  };
  static constexpr std::array kRefereeTopics = {
      service_discovery::kRefereeGameStatusTopic,
  };

  std::unique_ptr<IZmqSubscriberSocket> referee_socket = std::make_unique<ZmqSubscriberSocket>();
  referee_socket->connect(service_discovery::kRefereeAddress, kRefereeTopics);

  std::unique_ptr<IZmqSubscriberSocket> perception_socket = std::make_unique<ZmqSubscriberSocket>();
  perception_socket->connect(service_discovery::kPerceptionAddress, kPerceptionTopics);

  std::unique_ptr<IZmqPoller> zmq_poller = std::make_unique<ZmqPoller>();
  zmq_poller->push(*referee_socket);
  zmq_poller->push(*perception_socket);

  std::unique_ptr<IPayloadMapper> payload_mapper = std::make_unique<PayloadMapper>();

  return std::make_unique<MessageReceiver>(std::move(perception_socket),
                                           std::move(referee_socket),
                                           std::move(zmq_poller),
                                           std::move(payload_mapper));
}

std::unique_ptr<IController> makeProducer(object_ptr<IConcurrentQueue<Payload>> messages) {
  return std::make_unique<ProducerController>(messages, makeMessageReceiver());
}

int main() {
  std::println("decision-guardiola is running!");

  std::unique_ptr<IConcurrentQueue<Payload>> messages
      = std::make_unique<ConditionVariableConcurrentQueue<Payload>>();

  std::unique_ptr<IController> producer_controller = makeProducer(messages);

  std::jthread producer_thread(&IController::run, producer_controller.get());

  return 0;
}
