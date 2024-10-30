#ifndef BEHAVIOR_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
#define BEHAVIOR_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H

#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

/**
 * @class RobotIdMessage
 * @brief A class that represents the robot id.
 *
 * This class is used to represent the robot id. It contains the color and the number of the robot.
 */
class RobotIdMessage : public robocin::IProtoConvertible<protocols::common::RobotId> {
  enum Color {
    COLOR_UNSPECIFIED = 0,
    COLOR_YELLOW = 1,
    COLOR_BLUE = 2,
  };

 public:
  explicit RobotIdMessage(std::optional<Color> color = std::nullopt,
                          std::optional<uint32_t> number = 0);

  [[nodiscard]] protocols::common::RobotId toProto() const override;

  void fromProto(const protocols::common::RobotId& robot_id) override;

  std::optional<Color> color;
  std::optional<uint32_t> number;
};

} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
