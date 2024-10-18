#ifndef BEHAVIOR_MESSAGING_RECEIVER_PAYLOAD_H
#define BEHAVIOR_MESSAGING_RECEIVER_PAYLOAD_H

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
 * The Payload class is responsible for storing and managing a collection of vision packets,
 * parameters, or any other received message from external components which are created from
 * datagrams.
 */
class Payload {
 public:
  Payload(std::vector<::protocols::perception::Detection> detections,
          std::vector<::protocols::referee::GameStatus> game_statuses);

  [[nodiscard]] std::span<const ::protocols::perception::Detection> getDetectionPackets() const;

  [[nodiscard]] std::span<const ::protocols::referee::GameStatus> getGameStatusPackets() const;

  [[nodiscard]] bool empty() const;

 private:
  std::vector<::protocols::perception::Detection> detections_;
  std::vector<::protocols::referee::GameStatus> game_statuses_;
};

} // namespace behavior

#endif // BEHAVIOR_MESSAGING_RECEIVER_PAYLOAD_H
