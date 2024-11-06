#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H

#include "communication/processing/messages/common/message_type/message_type.h"
#include "communication/processing/messages/common/robot_dribbler/robot_dribbler.h"
#include "communication/processing/messages/common/robot_id/robot_id.h"
#include "communication/processing/messages/common/robot_kick/robot_kick.h"
#include "communication/processing/messages/common/robot_velocity/robot_velocity.h"
#include "communication/processing/messages/flags/flags.h"

#include <protocols/communication/robot_info.pb.h>
#include <robocin/output/log.h>
#include <robocin/utility/iproto_convertible.h>
#include <vector>

namespace communication {

class CommandMessage : public robocin::IProtoConvertible<protocols::communication::Command> {
 public:
  CommandMessage(MessageTypeMessage message_type = MessageTypeMessage{},
                 RobotIdMessage robot_id = RobotIdMessage{},
                 RobotVelocityMessage robot_velocity = RobotVelocityMessage{},
                 RobotKickMessage robot_kick = RobotKickMessage{},
                 RobotDribblerMessage robot_dribbler = RobotDribblerMessage{},
                 FlagsMessage robot_flags = FlagsMessage{});

  [[nodiscard]] protocols::communication::Command toProto() const override;

  void fromProto(const protocols::communication::Command& command) override;

  MessageTypeMessage message_type;
  RobotIdMessage robot_id;
  RobotVelocityMessage robot_velocity;
  RobotKickMessage robot_kick;
  RobotDribblerMessage robot_dribbler;
  FlagsMessage robot_flags;
};

class OutputMessage : public robocin::IProtoConvertible<protocols::communication::Output> {
 public:
  OutputMessage(CommandMessage commands = CommandMessage{});

  [[nodiscard]] protocols::communication::Output toProto() const override;

  void fromProto(const protocols::communication::Output& output) override;

  CommandMessage command;
};

class CommandOutputMessage
    : public robocin::IProtoConvertible<protocols::communication::CommandOutput> {
 public:
  // PROTO BASE:
  //  message CommandOutput {
  //   uint32 id = 1;
  //   double vx = 2;
  //   double vy = 3;
  //   double vw = 4;
  //   bool front = 5;
  //   bool chip = 6;
  //   bool charge = 7;
  //   double kick_strength = 8;
  //   bool dribbler = 9;
  //   double dribbler_speed = 10;
  // }

  explicit CommandOutputMessage(uint32_t id = 0,
                                double vx = 0,
                                double vy = 0,
                                double vw = 0,
                                bool front = false,
                                bool chip = false,
                                bool charge = false,
                                double kick_strength = 0,
                                bool dribbler = false,
                                double dribbler_speed = 0);

  [[nodiscard]] protocols::communication::CommandOutput toProto() const override;

  void fromProto(const protocols::communication::CommandOutput& command_output) override;

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
    : public robocin::IProtoConvertible<protocols::communication::RobotInfo> {
 public:
  explicit CommunicationMessage(std::vector<OutputMessage> output_messages
                                = std::vector<OutputMessage>{});

  [[nodiscard]] protocols::communication::RobotInfo toProto() const override;

  void fromProto(const protocols::communication::RobotInfo& robot_info) override;

  std::vector<OutputMessage> output_messages;
};

class RobotCommandMessage
    : public robocin::IProtoConvertible<protocols::communication::RobotCommand> {
 public:
  explicit RobotCommandMessage(std::vector<CommandOutputMessage> commands
                               = std::vector<CommandOutputMessage>{});

  [[nodiscard]] protocols::communication::RobotCommand toProto() const override;

  void fromProto(const protocols::communication::RobotCommand& robot_command) override;

  std::vector<CommandOutputMessage> commands;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H
