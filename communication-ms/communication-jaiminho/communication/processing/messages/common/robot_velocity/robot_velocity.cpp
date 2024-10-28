#include "robot_velocity.h"

namespace communication {

RobotVelocityMessage::RobotVelocityMessage(std::optional<robocin::Point2D<float>> velocity,
                                           std::optional<float> angular_velocity) :
    velocity(std::move(velocity)),
    angular_velocity(std::move(angular_velocity)) {}

protocols::common::RobotVelocity RobotVelocityMessage::toProto() const {
  protocols::common::RobotVelocity robot_velocity;
  protocols::common::Point2Df point2Df;
  if (velocity.has_value()) {
    point2Df.set_x(velocity.value().x);
    point2Df.set_y(velocity.value().y);
    robot_velocity.mutable_velocity()->CopyFrom(point2Df);
  }
  robot_velocity.set_angular_velocity(angular_velocity.value_or(0));

  return robot_velocity;
}

void RobotVelocityMessage::fromProto(protocols::common::RobotVelocity robot_velocity) {
  if (robot_velocity.has_velocity()) {
    robocin::Point2D<float> point2Df;
    point2Df.x = robot_velocity.velocity().x();
    point2Df.y = robot_velocity.velocity().y();
    velocity = point2Df;
  }
  angular_velocity = robot_velocity.angular_velocity();
}

} // namespace communication
