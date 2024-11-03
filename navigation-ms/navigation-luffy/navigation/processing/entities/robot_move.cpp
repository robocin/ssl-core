#include "navigation/processing/entities/robot_move.h"

namespace navigation {

RobotMove::RobotMove(::robocin::Point2Dd velocity, double angularVelocity) :
    velocity_(velocity),
    angularVelocity_(angularVelocity) {}

RobotMove::RobotMove(double angularVelocity) :
    velocity_(::robocin::Point2Dd(0.0, 0.0)),
    angularVelocity_(angularVelocity) {}

RobotMove::RobotMove() : velocity_(::robocin::Point2Dd(0.0, 0.0)), angularVelocity_(0.0) {}

::robocin::Point2Dd RobotMove::velocity() const { return velocity_; }
double RobotMove::angularVelocity() const { return angularVelocity_; }

} // namespace navigation