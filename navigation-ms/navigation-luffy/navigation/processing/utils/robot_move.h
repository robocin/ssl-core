#ifndef NAVIGATION_PROCESSING_ROBOT_MOVE_H
#define NAVIGATION_PROCESSING_ROBOT_MOVE_H

#include <robocin/geometry/point2d.h>
namespace navigation {

namespace rc {
using ::robocin::Point2Df;
} // namespace rc

class RobotMove {
  rc::Point2Df velocity_;
  double angularVelocity_;

 public:
  RobotMove(rc::Point2Df velocity, double angularVelocity);
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_ROBOT_MOVE_H
