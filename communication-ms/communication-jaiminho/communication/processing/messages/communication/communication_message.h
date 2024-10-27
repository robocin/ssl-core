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
  CommandMessage(MessageTypeMessage = MessageTypeMessage{},
                 RobotIdMessage = RobotIdMessage{},
                 RobotVelocityMessage = RobotVelocityMessage{},
                 RobotKickMessage = RobotKickMessage{},
                 RobotDribblerMessage = RobotDribblerMessage{},
                 FlagsMessage = FlagsMessage{});

  [[nodiscard]] protocols::communication::Command toProto() const override {
    protocols::communication::Command command;
    command.set_msg_type(message_type.toProto());
    command.mutable_robot_id()->CopyFrom(robot_id.toProto());
    command.mutable_robot_velocity()->CopyFrom(robot_velocity.toProto());
    command.mutable_kick_command()->CopyFrom(robot_kick.kick_command.toProto());
    command.mutable_dribbler_command()->CopyFrom(robot_dribbler.dribbler_command.toProto());
    command.mutable_robot_flags()->CopyFrom(robot_flags.toProto());

    return command;
  };

  void fromProto(const protocols::communication::Command command) override {}

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

  [[nodiscard]] protocols::communication::Output toProto() const override {
    protocols::communication::Output output;
    output.mutable_command()->CopyFrom(command.toProto());

    return output;
  };

  void fromProto(const protocols::communication::Output output) override {}

  CommandMessage command;
};

class CommunicationMessage
    : public robocin::IProtoConvertible<protocols::communication::RobotInfo> {
 public:
  CommunicationMessage(std::vector<OutputMessage> output_messages = std::vector<OutputMessage>{});

  [[nodiscard]] protocols::communication::RobotInfo toProto() const override {
    protocols::communication::RobotInfo robot_info;
    for (const auto& output_message : output_messages) {
      robot_info.add_output()->CopyFrom(output_message.toProto());
    }

    return robot_info;
  };

  void fromProto(const protocols::communication::RobotInfo robot_info) override {}
  std::vector<OutputMessage> output_messages;
};
} // namespace communication
