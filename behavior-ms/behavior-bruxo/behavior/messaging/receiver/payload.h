#ifndef BEHAVIOR_MESSAGING_RECEIVER_PAYLOAD_H
#define BEHAVIOR_MESSAGING_RECEIVER_PAYLOAD_H

#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <robocin/network/zmq_datagram.h>
#include <span>
#include <vector>

namespace behavior {

/**
 * @class Payload
 * @brief Manages a collection of input packets.
 *
 * The Payload class is responsible for storing and managing a collection of detection messages,
 * parameters, or any other received message from external components which are created from
 * datagrams.
 */
class Payload {
 public:
  Payload(std::vector<::protocols::perception::Detection> detections,
          std::vector<::protocols::decision::Decision> decision,
          std::vector<::protocols::referee::GameStatus> game_status);

  [[nodiscard]] std::span<const ::protocols::perception::Detection> getDetectionMessages() const;

  [[nodiscard]] std::span<const ::protocols::decision::Decision> getDecisionMessages() const;

  [[nodiscard]] std::span<const ::protocols::referee::GameStatus> getGameStatusMessages() const;
  [[nodiscard]] bool empty() const;

 private:
  std::vector<::protocols::perception::Detection> detections_;
  std::vector<::protocols::decision::Decision> decisions_;
  std::vector<::protocols::referee::GameStatus> game_status_;
};

} // namespace behavior

#endif // BEHAVIOR_MESSAGING_RECEIVER_PAYLOAD_H
