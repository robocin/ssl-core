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

MotionParser::MotionParser() = default;

RobotMove MotionParser::fromGoToPoint(const rc::GoToPoint& go_to_point, const rc::Robot& robot) {

  robocin::Point2Dd s0 = robocin::Point2Dd(robot.position().x(), robot.position().y());
  robocin::Point2Dd s = robocin::Point2Dd(go_to_point.target().x(), go_to_point.target().y());
  robocin::Point2Dd delta_s = (s - s0) / M_to_MM;

  const double kp = ANGLE_KP;
  const double max_angular_vel = ROBOT_MAX_ANGULAR_VELOCITY;

  auto [minVelocity, maxVelocity]
      = MovingProfileUtil::minAndMaxVelocityToProfile(go_to_point.moving_profile());
  double prop_distance = MovingProfileUtil::propDistanceToProfile(go_to_point.moving_profile());

  if (delta_s.length() <= prop_distance) {
    maxVelocity = std::max(
        mathematics::map((delta_s.length()), 0.0, prop_distance, minVelocity, maxVelocity),
        minVelocity);
  }

  double tolerance_to_target = go_to_point.precision_to_target() == rc::PrecisionToTarget::High ?
                                   SMALL_TOLERANCE_TO_DESIRED_POSITION_M :
                                   DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M;

  const double delta_theta
      = ::robocin::smallestAngleDiff<double>(robot.angle(), go_to_point.target_angle());

  if (delta_s.length() > tolerance_to_target) {

    // Uses an angle PID (only proportional for now), and first try to get in the right
    // angle, using only angular speed and then use linear speed to get into the point
    const double theta = delta_s.angle();
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

    return RobotMove{new_velocity, std::clamp(kp * delta_theta, -max_angular_vel, max_angular_vel)};
  }

  return RobotMove{{0, 0}, std::clamp(kp * delta_theta, -max_angular_vel, max_angular_vel)};
}

RobotMove MotionParser::fromRotateInPoint(const rc::RotateInPoint& rotate_in_point,
                                          const rc::Robot& robot) {

  const double velocity = [&]() {
    double velocity = rotate_in_point.rotate_velocity();
    velocity *= rotate_in_point.min_velocity();

    return velocity;
  }();
  ::robocin::Point2Dd target = {rotate_in_point.target().x(), rotate_in_point.target().y()};
  ::robocin::Point2Dd robot_pos = {robot.position().x(), robot.position().y()};

  const double robot_radius = (robot_pos.distanceTo(target)) / M_to_MM;
  const double delta_theta
      = robocin::smallestAngleDiff(robot.angle(), rotate_in_point.target_angle());
  const double approach_kp = rotate_in_point.approach_kp();
  const double angle_kp = rotate_in_point.angle_kp();

  // Rotate in the smaller angle
  const double orientation_factor = rotate_in_point.clockwise() ? 1.0 : -1.0;
  const robocin::Point2Dd coordinates
      = robocin::Point2Dd(approach_kp * (robot_radius - rotate_in_point.orbit_radius() / M_to_MM),
                          orientation_factor * velocity);
  const robocin::Point2Dd rotated_coordinates = coordinates.rotatedCounterClockWise(robot.angle());
  const double angular_velocity
      = ((-(orientation_factor * velocity) / (rotate_in_point.orbit_radius() / M_to_MM))
         + (angle_kp * delta_theta));

  return RobotMove{rotated_coordinates, angular_velocity};
}

RobotMove MotionParser::fromRotateOnSelf(const rc::RotateOnSelf& rotate_on_self,
                                         const rc::Robot& robot) {

  auto delta_theta
      = robocin::smallestAngleDiff<double>(robot.angle(), rotate_on_self.target_angle());
  robocin::Point2Dd velocity
      = robocin::Point2Dd{rotate_on_self.velocity().x(), rotate_on_self.velocity().y()};

  return RobotMove{velocity, rotate_on_self.kp() * delta_theta};
}

} // namespace navigation
