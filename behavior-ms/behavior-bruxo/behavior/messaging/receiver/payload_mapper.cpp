#include "behavior/messaging/receiver/payload_mapper.h"

#include "behavior/messaging/receiver/payload.h"

#include <robocin/network/zmq_datagram.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>
#include <vector>

namespace behavior {
namespace {

namespace service_discovery = ::robocin::service_discovery;

using ::robocin::ilog;
using ::robocin::ZmqDatagram;

namespace rc {

using ::protocols::decision::Decision;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

} // namespace

Payload PayloadMapper::fromZmqDatagrams(std::span<const ZmqDatagram> messages) const {
  std::vector<rc::Detection> detections;
  std::vector<rc::Decision> decisions;
  std::vector<rc::GameStatus> game_status;

  for (const ZmqDatagram& zmq_datagram : messages) {
    if (zmq_datagram.topic() == service_discovery::kPerceptionDetectionTopic) {
      rc::Detection detection;
      detection.ParseFromString(std::string{zmq_datagram.message()});
      detections.emplace_back(std::move(detection));

    } else if (zmq_datagram.topic() == service_discovery::kDecisionTopic) {
      rc::Decision decision;
      decision.ParseFromString(std::string{zmq_datagram.message()});
      decisions.emplace_back(std::move(decision));

    } else if (zmq_datagram.topic() == service_discovery::kRefereeGameStatusTopic) {
      rc::GameStatus game_status_message;
      game_status_message.ParseFromString(std::string{zmq_datagram.message()});
      robocin::ilog("Received from referee: {}", game_status_message.DebugString());
      game_status.emplace_back(std::move(game_status_message));

    } else {
      // wlog("zmq_datagram with topic '{}' not processed.", zmq_datagram.topic());
    }
  }
  return Payload{std::move(detections), std::move(decisions), std::move(game_status)};
}

} // namespace behavior
