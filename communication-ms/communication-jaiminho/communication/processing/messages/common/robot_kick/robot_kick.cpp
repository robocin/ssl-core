#include "robot_kick.h"

namespace communication {

KickCommandMessage::KickCommandMessage(std::optional<double> kick_strength,
                                       std::optional<bool> is_front,
                                       std::optional<bool> is_chip,
                                       std::optional<bool> charge_capacitor,
                                       std::optional<bool> is_bypass_ir) :
    kick_strength(std::move(kick_strength)),
    is_front(std::move(is_front)),
    is_chip(std::move(is_chip)),
    charge_capacitor(std::move(charge_capacitor)),
    is_bypass_ir(std::move(is_bypass_ir)) {}

protocols::common::RobotKick_KickCommand KickCommandMessage::toProto() const {
  protocols::common::RobotKick_KickCommand kick_command;
  kick_command.set_kick_strength(kick_strength.value_or(0));
  kick_command.set_is_front(is_front.value_or(false));
  kick_command.set_is_chip(is_chip.value_or(false));
  kick_command.set_charge_capacitor(charge_capacitor.value_or(false));
  kick_command.set_is_bypass_ir(is_bypass_ir.value_or(false));

  return kick_command;
}

void KickCommandMessage::fromProto(protocols::common::RobotKick_KickCommand kick_command) {
  kick_strength = kick_command.kick_strength();
  is_front = kick_command.is_front();
  is_chip = kick_command.is_chip();
  charge_capacitor = kick_command.charge_capacitor();
  is_bypass_ir = kick_command.is_bypass_ir();
}

RobotKickMessage::RobotKickMessage(KickCommandMessage kick_command) :
    kick_command(std::move(kick_command)) {}

protocols::common::RobotKick RobotKickMessage::toProto() const {
  protocols::common::RobotKick robot_kick;
  robot_kick.mutable_kick_command()->CopyFrom(kick_command.toProto());
  return robot_kick;
}

void RobotKickMessage::fromProto(protocols::common::RobotKick robot_kick) {
  kick_command.fromProto(robot_kick.kick_command());
}

} // namespace communication
