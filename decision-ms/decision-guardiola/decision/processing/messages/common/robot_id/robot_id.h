#ifndef DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
#define DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H

#include "decision/processing/messages/iproto_convertible.h"

#include <protocols/common/robot_id.pb.h>

namespace decision {

class RobotIdMessage : public IProtoConvertible<protocols::common::RobotId> {
  enum Color {
    COLOR_UNSPECIFIED = 0,
    COLOR_YELLOW = 1,
    COLOR_BLUE = 2,
  };

 public:
  explicit RobotIdMessage(std::optional<Color> color, uint32_t number);
  std::optional<Color> color;
  uint32_t number;

  [[nodiscard]] protocols::common::RobotId toProto() const override {
    return protocols::common::RobotId{};
  };
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
