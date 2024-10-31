#include "communication/processing/messages/communication/communication_message.h"

namespace communication {

CommandMessage::CommandMessage(MessageTypeMessage message_type,
                               RobotIdMessage robot_id,
                               RobotVelocityMessage robot_velocity,
                               RobotKickMessage robot_kick,
                               RobotDribblerMessage robot_dribbler,
                               FlagsMessage robot_flags) :
    message_type(std::move(message_type)),
    robot_id(std::move(robot_id)),
    robot_velocity(std::move(robot_velocity)),
    robot_kick(std::move(robot_kick)),
    robot_dribbler(std::move(robot_dribbler)),
    robot_flags(std::move(robot_flags)) {}

protocols::communication::Command CommandMessage::toProto() const {
  protocols::communication::Command command;
  command.set_msg_type(message_type.toProto());
  command.mutable_robot_id()->CopyFrom(robot_id.toProto());
  command.mutable_robot_velocity()->CopyFrom(robot_velocity.toProto());
  command.mutable_kick_command()->CopyFrom(robot_kick.kick_command.toProto());
  command.mutable_dribbler_command()->CopyFrom(robot_dribbler.dribbler_command.toProto());
  command.mutable_robot_flags()->CopyFrom(robot_flags.toProto());

  return command;
}

void CommandMessage::fromProto(const protocols::communication::Command command) {
  message_type.fromProto(command.msg_type());
  robot_id.fromProto(command.robot_id());
  robot_velocity.fromProto(command.robot_velocity());
  robot_kick.kick_command.fromProto(command.kick_command());
  robot_dribbler.dribbler_command.fromProto(command.dribbler_command());
  robot_flags.fromProto(command.robot_flags());
}

OutputMessage::OutputMessage(CommandMessage commands) : command(std::move(commands)) {}

protocols::communication::Output OutputMessage::toProto() const {
  protocols::communication::Output output;
  output.mutable_command()->CopyFrom(command.toProto());

  return output;
}

void OutputMessage::fromProto(const protocols::communication::Output output) {
  command.fromProto(output.command());
}

CommunicationMessage::CommunicationMessage(std::vector<OutputMessage> output_messages) :
    output_messages(std::move(output_messages)) {}

protocols::communication::RobotInfo CommunicationMessage::toProto() const {
  protocols::communication::RobotInfo robot_info;
  for (const auto& output_message : output_messages) {
    robot_info.add_output()->CopyFrom(output_message.toProto());
  }

  return robot_info;
}

void CommunicationMessage::fromProto(const protocols::communication::RobotInfo robot_info) {}
} // namespace communication
