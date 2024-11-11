#include "navigation/processing/messages/common/robot_kick/kick_command.h"

namespace navigation {
KickCommandMessage::KickCommandMessage() = default;
KickCommandMessage::KickCommandMessage(std::optional<double> strength,
                                       std::optional<bool> is_front,
                                       std::optional<bool> is_chip,
                                       std::optional<bool> charge_capacitor,
                                       std::optional<bool> is_bypass_ir) :
    strength(strength),
    is_front(is_front),
    is_chip(is_chip),
    charge_capacitor(charge_capacitor),
    is_bypass_ir(is_bypass_ir) {}

protocols::common::RobotKick::KickCommand KickCommandMessage::toProto() const {
  protocols::common::RobotKick::KickCommand kick_proto;
  if (strength.has_value()) {
    kick_proto.set_kick_strength(strength.value());
  }
  if (is_front.has_value()) {
    kick_proto.set_is_front(is_front.value());
  }
  if (is_chip.has_value()) {
    kick_proto.set_is_chip(is_chip.value());
  }
  if (charge_capacitor.has_value()) {
    kick_proto.set_charge_capacitor(charge_capacitor.value());
  }
  if (is_bypass_ir.has_value()) {
    kick_proto.set_is_bypass_ir(is_bypass_ir.value());
  }
  return kick_proto;
};

void KickCommandMessage::fromProto(
    const protocols::common::RobotKick::KickCommand& kick_command_proto) {
  strength = kick_command_proto.kick_strength();
  is_front = kick_command_proto.is_front();
  is_chip = kick_command_proto.is_chip();
  charge_capacitor = kick_command_proto.charge_capacitor();
  is_bypass_ir = kick_command_proto.is_bypass_ir();
}

KickCommandMessage::KickCommandMessage(
    const protocols::common::RobotKick::KickCommand& kick_command_proto) {
  KickCommandMessage::fromProto(kick_command_proto);
}

} // namespace navigation
