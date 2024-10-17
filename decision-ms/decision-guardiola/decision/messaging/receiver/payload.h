#ifndef DECISION_MESSAGING_RECEIVER_PAYLOAD_H
#define DECISION_MESSAGING_RECEIVER_PAYLOAD_H

#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <robocin/network/zmq_datagram.h>
#include <span>
#include <vector>

namespace decision {

// TODO: atualizar comentário
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
  // TODO: criar os tipos que vão vir no payload do decision
  Payload(std::vector<::protocols::perception::Detection> detections,
          std::vector<::protocols::referee::GameStatus> game_statuses);

  [[nodiscard]] std::span<const ::protocols::perception::Detection> getDetections() const;

  [[nodiscard]] std::span<const ::protocols::referee::GameStatus> getGameStatuses() const;

  [[nodiscard]] bool empty() const;

 private:
  std::vector<::protocols::perception::Detection> detections_;
  std::vector<::protocols::referee::GameStatus> game_statuses_;
  // TODO(matheusvtna, joseviccruz): add parameters collection.
  // TODO(matheusvtna, joseviccruz): add telemetries collection.
};

} // namespace decision

#endif // DECISION_MESSAGING_RECEIVER_PAYLOAD_H
