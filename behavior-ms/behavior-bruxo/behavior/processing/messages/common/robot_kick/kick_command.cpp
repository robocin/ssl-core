#include "behavior/processing/messages/common/robot_kick/kick_command.h"

namespace behavior {

KickCommandMessage::KickCommandMessage(float strength,
                                       bool is_front,
                                       bool is_chip,
                                       bool charge_capacitor,
                                       bool is_bypass_ir) :
    strength(strength),
    is_front(is_front),
    is_chip(is_chip),
    charge_capacitor(charge_capacitor),
    is_bypass_ir(is_bypass_ir) {};

[[nodiscard]] protocols::common::RobotKick::KickCommand KickCommandMessage::toProto() const {
  protocols::common::RobotKick::KickCommand proto;

  proto.set_kick_strength(strength);
  proto.set_is_front(is_front);
  proto.set_is_chip(is_chip);
  proto.set_charge_capacitor(charge_capacitor);
  proto.set_is_bypass_ir(is_bypass_ir);

  return proto;
};

void KickCommandMessage::fromProto(
    const protocols::common::RobotKick::KickCommand& kick_command_proto) {};

} // namespace behavior
