#include "robot_dribbler.h"

namespace communication {

DribblerCommandMessage::DribblerCommandMessage(std::optional<double> dribbler_speed,
                                               std::optional<bool> is_active) :
    dribbler_speed(std::move(dribbler_speed)),
    is_active(std::move(is_active)) {}

protocols::common::RobotDribbler_DribblerCommand DribblerCommandMessage::toProto() const {
  protocols::common::RobotDribbler_DribblerCommand dribbler_command;
  dribbler_command.set_dribbler_speed(dribbler_speed.value_or(0));
  dribbler_command.set_is_active(is_active.value_or(false));

  return dribbler_command;
}

void DribblerCommandMessage::fromProto(
    const protocols::common::RobotDribbler_DribblerCommand& dribbler_command) {
  dribbler_speed = dribbler_command.dribbler_speed();
  is_active = dribbler_command.is_active();
}

RobotDribblerMessage::RobotDribblerMessage(DribblerCommandMessage dribbler_command) :
    dribbler_command(std::move(dribbler_command)) {}

protocols::common::RobotDribbler RobotDribblerMessage::toProto() const {
  protocols::common::RobotDribbler robot_dribbler;
  robot_dribbler.mutable_dribbler_command()->CopyFrom(dribbler_command.toProto());
  return robot_dribbler;
}

void RobotDribblerMessage::fromProto(const protocols::common::RobotDribbler& robot_dribbler) {
  dribbler_command.fromProto(robot_dribbler.dribbler_command());
}

} // namespace communication
