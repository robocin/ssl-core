#ifndef DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
#define DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H

#include <cstdint>
#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace decision {
constexpr uint32_t kRobotIdMessageNumber = 0;

class RobotIdMessage : public robocin::IProtoConvertible<protocols::common::RobotId> {
 public:
  enum Color {
    COLOR_UNSPECIFIED = 0,
    COLOR_YELLOW = 1,
    COLOR_BLUE = 2,
  };

  explicit RobotIdMessage(uint32_t number = kRobotIdMessageNumber,
                          std::optional<Color> color = std::nullopt);
  std::optional<Color> color;
  uint32_t number; // number should ALWAYS be sent from proto

  explicit RobotIdMessage(const protocols::common::RobotId& robot_id_proto);

  [[nodiscard]] protocols::common::RobotId toProto() const override;

  void fromProto(const protocols::common::RobotId& robot_id_proto) override;
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
