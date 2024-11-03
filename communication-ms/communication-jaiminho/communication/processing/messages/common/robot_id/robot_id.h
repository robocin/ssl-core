#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H

#include <optional>
#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

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

  void fromProto(protocols::common::RobotId robot_id) override;

  std::optional<Color> color;
  std::optional<uint32_t> number;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_ID_H
