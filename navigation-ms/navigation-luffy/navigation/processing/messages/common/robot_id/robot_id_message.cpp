#include "navigation/processing/messages/common/robot_id/robot_id_message.h"

#include <optional>
#include <protocols/common/robot_id.pb.h>

namespace navigation {
namespace {
namespace rc {
using protocols::common::RobotId;
using protocols::common::RobotId_Color;
} // namespace rc
} // namespace

RobotIdMessage::Color getColor(rc::RobotId_Color color_proto) {
  switch (color_proto) {
    case protocols::common::RobotId_Color_COLOR_YELLOW: return RobotIdMessage::Color::COLOR_YELLOW;
    case protocols::common::RobotId_Color_COLOR_BLUE: return RobotIdMessage::Color::COLOR_BLUE;
    default: return RobotIdMessage::Color::COLOR_UNSPECIFIED;
  }
}

RobotIdMessage::RobotIdMessage(const rc::RobotId& robot_id_proto) { fromProto(robot_id_proto); };

protocols::common::RobotId RobotIdMessage::toProto() const { return protocols::common::RobotId{}; };

void RobotIdMessage::fromProto(const rc::RobotId& robot_id_proto) {
  if (robot_id_proto.has_color()) {
    color = getColor(robot_id_proto.color());
  }

  number = robot_id_proto.number();
};

RobotIdMessage::RobotIdMessage(uint32_t number, std::optional<Color> color) :
    number(number),
    color(color) {}

}; // namespace navigation
