#ifndef NAVIGATION_PROCESSING_MOVE_STATE_H
#define NAVIGATION_PROCESSING_MOVE_STATE_H

#include <robocin/geometry/point2d.h>

namespace navigation {

class MoveState {
  ::robocin::Point2Dd velocity_;
  ::robocin::Point2Dd position_;
  double angular_velocity_;
  double angle_;

 public:
  MoveState(::robocin::Point2Dd velocity,
            ::robocin::Point2Dd position,
            double angular_velocity,
            double angle);

  [[nodiscard]] ::robocin::Point2Dd velocity() const;
  [[nodiscard]] ::robocin::Point2Dd position() const;
  [[nodiscard]] double angularVelocity() const;
  [[nodiscard]] double angle() const;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOVE_STATE_H
