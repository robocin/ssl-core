#include "navigation/processing/motion_parser/motion_parser.h"

#include <cstdlib>
#include <navigation/parameters/parameters.h>
#include <navigation/processing/entities/robot_move.h>
#include <navigation/processing/utils/moving_profile_util.h>
#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/angular.h>

namespace navigation {

namespace {
namespace rc {
using ::protocols::behavior::GoToPoint;
using ::protocols::behavior::PathNode;
using ::protocols::behavior::PrecisionToTarget;
using ::protocols::behavior::RotateInPoint;
using ::protocols::behavior::RotateOnSelf;
using ::protocols::common::Point2Df;
using ::protocols::perception::Robot;
} // namespace rc
} // namespace

MotionParser::MotionParser() {}

RobotMove MotionParser::fromGoToPoint(const rc::GoToPoint& go_to_point, const rc::Robot& robot) {

  robocin::Point2Dd s0 = robocin::Point2Dd(robot.position().x(), robot.position().y());
  robocin::Point2Dd s = robocin::Point2Dd(go_to_point.target().x(), go_to_point.target().y());
  robocin::Point2Dd deltaS = (s - s0) / M_to_MM;

  const double kp = ANGLE_KP;
  const double maxAngularVel = ROBOT_MAX_ANGULAR_VELOCITY;

  auto [minVelocity, maxVelocity] = minAndMaxVelocityToProfile(go_to_point.moving_profile());
  double propDistance = propDistanceToProfile(go_to_point.moving_profile());

  if (deltaS.length() <= propDistance) {
    maxVelocity
        = std::max(mathematics::map((deltaS.length()), 0.0, propDistance, minVelocity, maxVelocity),
                   minVelocity);
  }

  double tolerance_to_target = go_to_point.precision_to_target() == rc::PrecisionToTarget::High ?
                                   SMALL_TOLERANCE_TO_DESIRED_POSITION_M :
                                   DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M;

  const double delta_theta
      = ::robocin::smallestAngleDiff<double>(robot.angle(), go_to_point.target_angle());

  if (deltaS.length() > tolerance_to_target) {

    // Uses an angle PID (only proportional for now), and first try to get in the right
    // angle, using only angular speed and then use linear speed to get into the point
    const double theta = deltaS.angle();
    double acc_prop = moving_profile::ROBOT_DEFAULT_LINEAR_ACCELERATION;
    auto v0 = robocin::Point2Dd(robot.velocity().x(), robot.velocity().y()) / M_to_MM;
    auto v = robocin::Point2D<double>::fromPolar(maxVelocity, theta);
    const double v0_decay = std::abs(v.angleTo(v0)) > PI / 3 ? ROBOT_VEL_BREAK_DECAY_FACTOR :
                                                               ROBOT_VEL_FAVORABLE_DECAY_FACTOR;

    // v = v0 + a*t
    v0 = v0 - (v0 * v0_decay) * CYCLE_STEP;

    auto acceleration_required
        = robocin::Point2D((v.x - v0.x) / CYCLE_STEP, (v.y - v0.y) / CYCLE_STEP);

    double alpha = mathematics::map(std::abs(delta_theta), 0.0, std::numbers::pi, 0.0, 1.0);
    // -x^2 +1
    // double propFactor = (-(alpha * alpha) + 1);

    // (x -1)^2
    double prop_factor = (alpha - 1) * (alpha - 1);
    acc_prop *= prop_factor;

    if (acceleration_required.length() > acc_prop) {
      acceleration_required.resize(acc_prop);
    }

    // v = v0 + a*t
    auto new_velocity = v0 + acceleration_required * CYCLE_STEP;

    if (new_velocity.length() < ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY) {
      new_velocity.resize(ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY);
    }

    // debug

    rc::PathNode new_path_node;

    new_path_node.set_time(0);

    rc::Point2Df* velocity_ptr = nullptr;
    velocity_ptr->set_x(0);
    velocity_ptr->set_y(0);
    new_path_node.set_allocated_velocity(velocity_ptr);

    rc::Point2Df* position_ptr = nullptr;
    position_ptr->set_x(go_to_point.target().x());
    position_ptr->set_y(go_to_point.target().y());
    new_path_node.set_allocated_position(position_ptr);

    return RobotMove{new_velocity, std::clamp(kp * delta_theta, -maxAngularVel, maxAngularVel)};
  }

  return RobotMove{{0, 0}, std::clamp(kp * delta_theta, -maxAngularVel, maxAngularVel)};
}

RobotMove MotionParser::fromRotateInPoint(const rc::RotateInPoint& rotate_in_point,
                                          const rc::Robot& robot) {

  // PROCESSAMENTO DO ROTATEINPOINT
  return RobotMove{};
}

RobotMove MotionParser::fromRotateOnSelf(const rc::RotateOnSelf& rotate_on_self,
                                         const rc::Robot& robot) {

  // PROCESSAMENTO DO ROTATEINPOINT
  return RobotMove{};
}

} // namespace navigation
