#ifndef NAVIGATION_PROCESSING_ROBOT_MOVE_H
#define NAVIGATION_PROCESSING_ROBOT_MOVE_H

#include <robocin/geometry/point2d.h>

namespace navigation {

class RobotMove {
  ::robocin::Point2Dd velocity_;
  double angularVelocity_;

 public:
  RobotMove(::robocin::Point2Dd velocity, double angularVelocity);

  explicit RobotMove(double angularVelocity);

  RobotMove();

  [[nodiscard]] ::robocin::Point2Dd velocity() const;
  [[nodiscard]] double angularVelocity() const;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_ROBOT_MOVE_H
