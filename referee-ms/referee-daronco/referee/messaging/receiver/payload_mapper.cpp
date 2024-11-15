#include "referee/messaging/receiver/payload_mapper.h"

#include "referee/messaging/receiver/payload.h"

#include <robocin/network/zmq_datagram.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace referee {
namespace {

namespace service_discovery = robocin::service_discovery;

using ::robocin::wlog;
using ::robocin::ZmqDatagram;

namespace rc {

using ::protocols::perception::Detection;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;

} // namespace tp

} // namespace
void PrintCommandField(const protocols::third_party::game_controller::Referee& referee_msg) {
    const google::protobuf::Descriptor* descriptor = referee_msg.GetDescriptor();
    const google::protobuf::Reflection* reflection = referee_msg.GetReflection();

    // Get the field descriptor for the 'command' field
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName("command");
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) % 1000;

    if (field && field->type() == google::protobuf::FieldDescriptor::TYPE_ENUM) {
        // Get the enum value as an integer
        int enum_value = reflection->GetEnumValue(referee_msg, field);

        // Get the enum descriptor to look up the name
        const google::protobuf::EnumValueDescriptor* enum_desc = field->enum_type()->FindValueByNumber(enum_value);
        // if (enum_desc) {
        //     // std::cout << "Command: " << enum_desc->name() << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << '\n';
        // } else {
        //     // std::cout << "Unknown command value: " << enum_value << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count() << std::endl;
        // }
    }
}

Payload PayloadMapper::fromZmqDatagrams(std::span<const ZmqDatagram> messages) const {
  std::vector<rc::Detection> detections;
  std::vector<tp::Referee> game_controller_referees;

  for (const ZmqDatagram& zmq_datagram : messages) {
    if (zmq_datagram.topic() == service_discovery::kPerceptionDetectionTopic) {
      rc::Detection detection;
      detection.ParseFromString(std::string{zmq_datagram.message()});
      detections.emplace_back(std::move(detection));

    } else if (zmq_datagram.topic() == service_discovery::kGameControllerRefereeTopic) {
      tp::Referee game_controller_referee;
      game_controller_referee.ParseFromString(std::string{zmq_datagram.message()});
      PrintCommandField(game_controller_referee);
      game_controller_referees.emplace_back(std::move(game_controller_referee));
    } else {
      // wlog("zmq_datagram with topic '{}' not processed.", zmq_datagram.topic());
    }
  }

  return Payload{std::move(detections), std::move(game_controller_referees)};
}

} // namespace referee
