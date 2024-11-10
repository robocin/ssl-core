#include "behavior/processing/messages/common/robot_kick/kick_command.h"

namespace behavior {
[[nodiscard]] protocols::common::RobotKick::KickCommand KickCommandMessage::toProto() const {
  return protocols::common::RobotKick::KickCommand{};
};

void KickCommandMessage::fromProto(
    const protocols::common::RobotKick::KickCommand& kick_command_proto) {};

} // namespace behavior
