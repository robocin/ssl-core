#include "communication/processing/messages/communication/communication_message.h"

namespace communication {

////////////// CommandOutputMessage //////////////
OutputRobotMessage::OutputRobotMessage(uint32_t id,
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

protocols::communication::OutputRobot OutputRobotMessage::toProto() const {
  protocols::communication::OutputRobot command_output;
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

void OutputRobotMessage::fromProto(const protocols::communication::OutputRobot& command_output) {
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
CommunicationMessage::CommunicationMessage(std::vector<OutputRobotMessage> commands) :
    commands(std::move(commands)) {}

protocols::communication::Communication CommunicationMessage::toProto() const {
  protocols::communication::Communication robot_command;
  for (const auto& command : commands) {
    robot_command.add_output()->CopyFrom(command.toProto());
  }

  return robot_command;
}

void CommunicationMessage::fromProto(const protocols::communication::Communication& robot_command) {
}

} // namespace communication
