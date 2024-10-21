#include <navigation/processing/utils/robot_move.h>

namespace navigation {

RobotMove::RobotMove(rc::Point2Df velocity, double angularVelocity) :
    velocity_(velocity),
    angularVelocity_(angularVelocity) {}

RobotMove::RobotMove(double angularVelocity) :
    velocity_(0, 0),
    angularVelocity_(angularVelocity) {}

} // namespace navigation
