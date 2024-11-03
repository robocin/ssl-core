#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

namespace navigation {
PeripheralActuationMessage::PeripheralActuationMessage(KickCommandMessage kick_command,
                                                       RobotDribblerMessage robot_dribbler) :

    kick_command(std::move(kick_command)),
    robot_dribbler(std::move(robot_dribbler)) {}

protocols::common::PeripheralActuation PeripheralActuationMessage::toProto() const {
  return protocols::common::PeripheralActuation{};
};

} // namespace navigation
