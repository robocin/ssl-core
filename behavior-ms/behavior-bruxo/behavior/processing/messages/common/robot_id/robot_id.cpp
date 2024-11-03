#include "behavior/processing/messages/common/robot_id/robot_id.h"

namespace behavior {

// RobotIdMessage
RobotIdMessage::RobotIdMessage(std::optional<Color> color, std::optional<uint32_t> number) :
    color{std::move(color)},
    number{std::move(number)} {}

RobotIdMessage::RobotIdMessage(const protocols::common::RobotId& robot_id_proto) {
  fromProto(robot_id_proto);
};

protocols::common::RobotId RobotIdMessage::toProto() const {
  protocols::common::RobotId robot_id;

  robot_id.set_color(
      static_cast<protocols::common::RobotId_Color>(color.value_or(Color::COLOR_UNSPECIFIED)));
  robot_id.set_number(number.value());

  return robot_id;
}

void RobotIdMessage::fromProto(const protocols::common::RobotId& robot_id) {
  color = static_cast<Color>(robot_id.color());
  number = robot_id.number();
}

} // namespace behavior
