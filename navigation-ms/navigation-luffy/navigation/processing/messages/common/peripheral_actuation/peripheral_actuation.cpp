#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

#include <optional>

namespace navigation {

void PeripheralActuationMessage::fromProto(
    const protocols::common::PeripheralActuation& peripheral_actuation_proto) {
  if (peripheral_actuation_proto.has_kick_command()) {
    kick_command = KickCommandMessage(peripheral_actuation_proto.kick_command());
  }
  if (peripheral_actuation_proto.has_robot_dribbler()) {
    robot_dribbler = RobotDribblerMessage(peripheral_actuation_proto.robot_dribbler());
  }
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
  protocols::common::PeripheralActuation actuation_proto;
  if (kick_command.has_value()) {
    actuation_proto.mutable_kick_command()->CopyFrom(kick_command->toProto());
  }
  if (robot_dribbler.has_value()) {
    actuation_proto.mutable_robot_dribbler()->CopyFrom(robot_dribbler->toProto());
  }
  return actuation_proto;
};

} // namespace navigation
