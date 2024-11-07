#include "navigation/processing/messages/common/robot_kick/kick_command.h"

namespace navigation {
KickCommandMessage::KickCommandMessage() = default;
KickCommandMessage::KickCommandMessage(double strength,
                                       bool is_front,
                                       bool is_chip,
                                       bool charge_capacitor,
                                       bool is_bypass_ir) :
    strength(strength),
    is_front(is_front),
    is_chip(is_chip),
    charge_capacitor(charge_capacitor),
    is_bypass_ir(is_bypass_ir) {}

protocols::common::RobotKick::KickCommand KickCommandMessage::toProto() const {
  return protocols::common::RobotKick::KickCommand{};
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
