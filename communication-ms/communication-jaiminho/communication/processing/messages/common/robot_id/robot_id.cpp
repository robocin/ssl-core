#include "communication/processing/messages/common/robot_id/robot_id.h"

namespace communication {

RobotIdMessage::RobotIdMessage(std::optional<Color> color, std::optional<uint32_t> number) :
    color{std::move(color)},
    number{std::move(number)} {}

} // namespace communication
