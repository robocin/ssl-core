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

  void fromProto(protocols::communication::Command command) override;

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

  void fromProto(protocols::communication::Output output) override;

  CommandMessage command;
};

class CommunicationMessage
    : public robocin::IProtoConvertible<protocols::communication::RobotInfo> {
 public:
  CommunicationMessage(std::vector<OutputMessage> output_messages = std::vector<OutputMessage>{});

  [[nodiscard]] protocols::communication::RobotInfo toProto() const override;

  void fromProto(protocols::communication::RobotInfo robot_info) override;

  std::vector<OutputMessage> output_messages;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMUNICATION_COMMUNICATION_MESSAGE_H
