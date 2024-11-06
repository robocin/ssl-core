#include "communication/processing/messages/communication/communication_message.h"

namespace communication {

////////////// CommandMessage //////////////
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

void CommandMessage::fromProto(const protocols::communication::Command& command) {
  message_type.fromProto(command.msg_type());
  robot_id.fromProto(command.robot_id());
  robot_velocity.fromProto(command.robot_velocity());
  robot_kick.kick_command.fromProto(command.kick_command());
  robot_dribbler.dribbler_command.fromProto(command.dribbler_command());
  robot_flags.fromProto(command.robot_flags());
}

////////////// OutputMessage //////////////
OutputMessage::OutputMessage(CommandMessage commands) : command(std::move(commands)) {}

protocols::communication::Output OutputMessage::toProto() const {
  protocols::communication::Output output;
  output.mutable_command()->CopyFrom(command.toProto());

  return output;
}

void OutputMessage::fromProto(const protocols::communication::Output& output) {
  command.fromProto(output.command());
}

////////////// CommunicationMessage //////////////
CommunicationMessage::CommunicationMessage(std::vector<OutputMessage> output_messages) :
    output_messages(std::move(output_messages)) {}

protocols::communication::RobotInfo CommunicationMessage::toProto() const {
  protocols::communication::RobotInfo robot_info;
  for (const auto& output_message : output_messages) {
    robot_info.add_output()->CopyFrom(output_message.toProto());
  }

  return robot_info;
}

void CommunicationMessage::fromProto(const protocols::communication::RobotInfo& robot_info) {}

////////////// CommandOutputMessage //////////////
CommandOutputMessage::CommandOutputMessage(uint32_t id,
                                           double vx,
                                           double vy,
                                           double vw,
                                           bool front,
                                           bool chip,
                                           bool charge,
                                           double kick_strength,
                                           bool dribbler,
                                           double dribbler_speed) :
    id(id),
    vx(vx),
    vy(vy),
    vw(vw),
    front(front),
    chip(chip),
    charge(charge),
    kick_strength(kick_strength),
    dribbler(dribbler),
    dribbler_speed(dribbler_speed) {}

protocols::communication::CommandOutput CommandOutputMessage::toProto() const {
  protocols::communication::CommandOutput command_output;
  command_output.set_id(id);
  command_output.set_vx(vx);
  command_output.set_vy(vy);
  command_output.set_vw(vw);
  command_output.set_front(front);
  command_output.set_chip(chip);
  command_output.set_charge(charge);
  command_output.set_kick_strength(kick_strength);
  command_output.set_dribbler(dribbler);
  command_output.set_dribbler_speed(dribbler_speed);

  return command_output;
}

void CommandOutputMessage::fromProto(
    const protocols::communication::CommandOutput& command_output) {
  id = command_output.id();
  vx = command_output.vx();
  vy = command_output.vy();
  vw = command_output.vw();
  front = command_output.front();
  chip = command_output.chip();
  charge = command_output.charge();
  kick_strength = command_output.kick_strength();
  dribbler = command_output.dribbler();
  dribbler_speed = command_output.dribbler_speed();
}

////////////// RobotCommandMessage //////////////
RobotCommandMessage::RobotCommandMessage(std::vector<CommandOutputMessage> commands) :
    commands(std::move(commands)) {}

protocols::communication::RobotCommand RobotCommandMessage::toProto() const {
  protocols::communication::RobotCommand robot_command;
  for (const auto& command : commands) {
    robot_command.add_robot_command()->CopyFrom(command.toProto());
  }

  return robot_command;
}

void RobotCommandMessage::fromProto(const protocols::communication::RobotCommand& robot_command) {}

} // namespace communication
