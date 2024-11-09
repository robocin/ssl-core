#include "navigation/processing/entities/move_state.h"

namespace navigation {
MoveState::MoveState(::robocin::Point2Dd velocity,
                     ::robocin::Point2Dd position,
                     double angular_velocity,
                     double angle) :
    velocity_(velocity),
    position_(position),
    angular_velocity_(angular_velocity),
    angle_(angle) {}

::robocin::Point2Dd MoveState::velocity() const { return velocity_; }

::robocin::Point2Dd MoveState::position() const { return position_; }

double MoveState::angularVelocity() const { return angular_velocity_; }

double MoveState::angle() const { return angle_; }
} // namespace navigation
