#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_VELOCITY_ROBOT_KICK_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_VELOCITY_ROBOT_KICK_H

#include <protocols/common/geometry.pb.h>
#include <protocols/common/robot_velocity.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class RobotVelocityMessage : public robocin::IProtoConvertible<protocols::common::RobotVelocity> {
 public:
  explicit RobotVelocityMessage(std::optional<robocin::Point2D<float>> velocity = std::nullopt,
                                std::optional<float> angular_velocity = std::nullopt);

  [[nodiscard]] protocols::common::RobotVelocity toProto() const override {
    protocols::common::RobotVelocity robot_velocity;
    protocols::common::Point2Df point2Df;
    if (velocity.has_value()) {
      point2Df.set_x(velocity.value().x);
      point2Df.set_y(velocity.value().y);
      robot_velocity.mutable_velocity()->CopyFrom(point2Df);
    }
    robot_velocity.set_angular_velocity(angular_velocity.value_or(0));

    return robot_velocity;
  };

  void fromProto(protocols::common::RobotVelocity robot_velocity) override {
    if (robot_velocity.has_velocity()) {
      robocin::Point2D<float> point2Df;
      point2Df.x = robot_velocity.velocity().x();
      point2Df.y = robot_velocity.velocity().y();
      velocity = point2Df;
    }
    angular_velocity = robot_velocity.angular_velocity();
  };

  std::optional<robocin::Point2D<float>> velocity;
  std::optional<float> angular_velocity;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_VELOCITY_ROBOT_KICK_H
