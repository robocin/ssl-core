#include "decision/processing/messages/common/robot_id/robot_id.h"

namespace decision {
RobotIdMessage::RobotIdMessage(uint32_t number, std::optional<Color> color) :
    number(number),
    color(color) {}
} // namespace decision
