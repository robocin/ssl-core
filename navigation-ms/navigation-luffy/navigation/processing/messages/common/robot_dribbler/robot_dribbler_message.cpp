#include "navigation/processing/messages/common/robot_dribbler/robot_dribbler_message.h"

#include <algorithm>

namespace navigation {

DribblerCommandMessage::DribblerCommandMessage(double dribbler_speed, bool is_active) :
    dribbler_speed(dribbler_speed),
    is_active(is_active) {}

protocols::common::RobotDribbler::DribblerCommand DribblerCommandMessage::toProto() const {
  return protocols::common::RobotDribbler::DribblerCommand{};
};

DribblerInfoMessage::DribblerInfoMessage(double dribbler_speed,
                                         double dribbler_current,
                                         bool is_ball_detected) :
    dribbler_speed(dribbler_speed),
    dribbler_current(dribbler_current),
    is_ball_detected(is_ball_detected) {}

protocols::common::RobotDribbler::DribblerInfo DribblerInfoMessage::toProto() const {
  return protocols::common::RobotDribbler::DribblerInfo{};
};

RobotDribblerMessage::RobotDribblerMessage(std::optional<DribblerCommandMessage> dribbler_command
                                           = std::nullopt,
                                           std::optional<DribblerInfoMessage> dribbler_info
                                           = std::nullopt) :

    dribbler_command(std::move(dribbler_command)),
    dribbler_info(std::move(dribbler_info)) {}

protocols::common::RobotDribbler RobotDribblerMessage::toProto() const {
  return protocols::common::RobotDribbler{};
};
} // namespace navigation
