#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_VELOCITY_ROBOT_VELOCITY_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_VELOCITY_ROBOT_VELOCITY_H

#include <optional>
#include <protocols/common/geometry.pb.h>
#include <protocols/common/robot_velocity.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class RobotVelocityMessage : public robocin::IProtoConvertible<protocols::common::RobotVelocity> {
 public:
  explicit RobotVelocityMessage(std::optional<robocin::Point2D<float>> velocity = std::nullopt,
                                std::optional<float> angular_velocity = std::nullopt);

  [[nodiscard]] protocols::common::RobotVelocity toProto() const override;

  void fromProto(const protocols::common::RobotVelocity& robot_velocity) override;

  std::optional<robocin::Point2D<float>> velocity;
  std::optional<float> angular_velocity;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_VELOCITY_ROBOT_VELOCITY_H
