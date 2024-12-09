#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

#include <optional>

namespace navigation {

void PeripheralActuationMessage::fromProto(
    const protocols::common::PeripheralActuation& peripheral_actuation_proto) {
  kick_command = KickCommandMessage(peripheral_actuation_proto.kick_command());
  robot_dribbler = RobotDribblerMessage(peripheral_actuation_proto.robot_dribbler());
}

PeripheralActuationMessage::PeripheralActuationMessage(
    std::optional<KickCommandMessage> kick_command,
    std::optional<RobotDribblerMessage> robot_dribbler) :

    kick_command(std::move(kick_command)),
    robot_dribbler(std::move(robot_dribbler)) {}

PeripheralActuationMessage::PeripheralActuationMessage(
    const protocols::common::PeripheralActuation& peripheral_actuation_proto) {
  PeripheralActuationMessage::fromProto(peripheral_actuation_proto);
}
protocols::common::PeripheralActuation PeripheralActuationMessage::toProto() const {
  return protocols::common::PeripheralActuation{};
};

} // namespace navigation
