#ifndef NAVIGATION_PROCESSING_ROBOT_MOVE_H
#define NAVIGATION_PROCESSING_ROBOT_MOVE_H

#include <robocin/geometry/point2d.h>

namespace navigation {

class RobotMove {
  ::robocin::Point2Df velocity_;
  float angularVelocity_;

 public:
  RobotMove(::robocin::Point2Df velocity, float angularVelocity);

  explicit RobotMove(float angularVelocity);

  RobotMove();

  [[nodiscard]] ::robocin::Point2Df velocity() const;
  [[nodiscard]] float angularVelocity() const;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_ROBOT_MOVE_H
