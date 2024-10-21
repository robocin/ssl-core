#ifndef NAVIGATION_PROCESSING_ROBOT_MOVE_H
#define NAVIGATION_PROCESSING_ROBOT_MOVE_H

#include <robocin/geometry/point2d.h>
namespace navigation {

class RobotMove {
  robocin::Point2Df velocity_;
  double angularVelocity_;

  public:
    RobotMove(robocin::Point2Df velocity, double angularVelocity);
    explicit RobotMove(double angularVelocity);

    ::robocin::Point2Df velocity() const { return velocity_; }
    double angularVelocity() const { return angularVelocity_; }
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_ROBOT_MOVE_H
