#include "navigation/messaging/receiver/payload_mapper.h"

#include "navigation/messaging/receiver/payload.h"

#include <robocin/network/zmq_datagram.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>

namespace navigation {
namespace {

namespace service_discovery = robocin::service_discovery;

using ::robocin::ilog;
using ::robocin::ZmqDatagram;

namespace rc {

using ::protocols::behavior::unification::Behavior;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

} // namespace

Payload PayloadMapper::fromZmqDatagrams(std::span<const ZmqDatagram> messages) const {
  std::vector<rc::Behavior> behaviors;
  std::vector<rc::Detection> detections;
  std::vector<rc::GameStatus> game_statuses;

  for (const ZmqDatagram& zmq_datagram : messages) {
    if (zmq_datagram.topic() == service_discovery::kBehaviorUnificationTopic) {
      rc::Behavior behavior;
      behavior.ParseFromString(std::string{zmq_datagram.message()});
      ilog("Received from behavior: {}", behavior.DebugString());
      behaviors.emplace_back(std::move(behavior));
    }
    if (zmq_datagram.topic() == service_discovery::kPerceptionDetectionTopic) {
      rc::Detection detection;
      detection.ParseFromString(std::string{zmq_datagram.message()});
      ilog("Received from perception: {}", detection.DebugString());
      detections.emplace_back(std::move(detection));
    }
    if (zmq_datagram.topic() == service_discovery::kRefereeGameStatusTopic) {
      rc::GameStatus game_status;
      game_status.ParseFromString(std::string{zmq_datagram.message()});
      // ilog("Received from referee: {}", game_status.DebugString());
      game_statuses.emplace_back(std::move(game_status));
    } else {
      // wlog("zmq_datagram with topic '{}' not processed.", zmq_datagram.topic());
    }
  }

  return Payload{std::move(behaviors), std::move(detections), std::move(game_statuses)};
}

} // namespace navigation
