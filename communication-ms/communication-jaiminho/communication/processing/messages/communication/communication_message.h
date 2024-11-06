#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H

#include "communication/processing/messages/common/message_type/message_type.h"
#include "communication/processing/messages/common/robot_dribbler/robot_dribbler.h"
#include "communication/processing/messages/common/robot_id/robot_id.h"
#include "communication/processing/messages/common/robot_kick/robot_kick.h"
#include "communication/processing/messages/common/robot_velocity/robot_velocity.h"
#include "communication/processing/messages/flags/flags.h"

#include <protocols/communication/communication.pb.h>
#include <robocin/output/log.h>
#include <robocin/utility/iproto_convertible.h>
#include <vector>

namespace communication {

class OutputRobotMessage
    : public robocin::IProtoConvertible<protocols::communication::OutputRobot> {
 public:
  explicit OutputRobotMessage(uint32_t id = 0,
                              double vx = 0,
                              double vy = 0,
                              double vw = 0,
                              bool front = false,
                              bool chip = false,
                              bool charge = false,
                              double kick_strength = 0,
                              bool dribbler = false,
                              double dribbler_speed = 0);

  [[nodiscard]] protocols::communication::OutputRobot toProto() const override;

  void fromProto(const protocols::communication::OutputRobot& command_output) override;

  uint32_t id;
  double vx;
  double vy;
  double vw;
  bool front;
  bool chip;
  bool charge;
  double kick_strength;
  bool dribbler;
  double dribbler_speed;
};

class CommunicationMessage
    : public robocin::IProtoConvertible<protocols::communication::Communication> {
 public:
  explicit CommunicationMessage(std::vector<OutputRobotMessage> commands
                                = std::vector<OutputRobotMessage>{});

  [[nodiscard]] protocols::communication::Communication toProto() const override;

  void fromProto(const protocols::communication::Communication& robot_command) override;

  std::vector<OutputRobotMessage> commands;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H
