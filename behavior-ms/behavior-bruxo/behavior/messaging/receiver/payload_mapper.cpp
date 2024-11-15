#include "behavior/messaging/receiver/payload_mapper.h"

#include "behavior/messaging/receiver/payload.h"

#include <robocin/network/zmq_datagram.h>
#include <robocin/output/log.h>
#include <iostream>
#include <robocin/wip/service_discovery/addresses.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

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
      // robocin::ilog("Received from referee: {}", game_status_message.DebugString());
      auto now = std::chrono::system_clock::now();
      std::time_t now_time = std::chrono::system_clock::to_time_t(now);
          auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) % 1000;
      std::cout << "[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count() << "] GAME STATUS: " << game_status_message.command().DebugString() << std::endl;
      game_status.emplace_back(std::move(game_status_message));

    } else {
      // wlog("zmq_datagram with topic '{}' not processed.", zmq_datagram.topic());
    }
  }
  return Payload{std::move(detections), std::move(decisions), std::move(game_status)};
}

} // namespace behavior
