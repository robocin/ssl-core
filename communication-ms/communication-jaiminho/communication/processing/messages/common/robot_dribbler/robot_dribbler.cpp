#include "communication/processing/messages/common/robot_dribbler/robot_dribbler.h"

namespace communication {

DribblerCommandMessage::DribblerCommandMessage(std::optional<double> dribbler_speed,
                                               std::optional<bool> is_active) :
    dribbler_speed{std::move(dribbler_speed)},
    is_active{std::move(is_active)} {}

RobotDribblerMessage::RobotDribblerMessage(DribblerCommandMessage dribbler_command) :
    dribbler_command{std::move(dribbler_command)} {}

} // namespace communication
