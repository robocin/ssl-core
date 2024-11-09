#include "navigation/processing/entities/robot_move.h"

namespace navigation {

RobotMove::RobotMove(::robocin::Point2Df velocity, float angularVelocity) :
    velocity_(velocity),
    angularVelocity_(angularVelocity) {}

RobotMove::RobotMove(float angularVelocity) :
    velocity_(::robocin::Point2Df(0.0, 0.0)),
    angularVelocity_(angularVelocity) {}

RobotMove::RobotMove() : velocity_(::robocin::Point2Df(0.0, 0.0)), angularVelocity_(0.0) {}

::robocin::Point2Df RobotMove::velocity() const { return velocity_; }
float RobotMove::angularVelocity() const { return angularVelocity_; }

} // namespace navigation
