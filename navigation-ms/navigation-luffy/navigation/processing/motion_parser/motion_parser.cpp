#include "navigation/processing/motion_parser/motion_parser.h"

#include <cstdlib>
#include <navigation/parameters/parameters.h>
#include <navigation/processing/entities/robot_move.h>
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

RobotMove MotionParser::fromGoToPoint(const rc::GoToPoint& go_to_point,
                                      const rc::Robot& robot) {
  robocin::Point2D robot_position = robocin::Point2D(robot.position().x(), robot.position().y());
  robocin::Point2D target_position
      = robocin::Point2D(go_to_point.target().x(), go_to_point.target().y());

  double distanceToGoal = robot_position.distanceTo(target_position);
  double max_velocity = 2.2;

  auto smallestAngleDiff = [](double lhs, double rhs) {
    double angle = fmod(rhs - lhs, 2 * PI);
    if (angle >= PI) {
      return angle - 2 * PI;
    } else if (angle < -PI) {
      return angle + 2 * PI;
    }
    return angle;
  };

  auto fromPolar = [](auto length, auto angle) {
    return std::make_pair(std::cos(angle) * length, std::sin(angle) * length);
  };

  if (distanceToGoal > 50) {
    auto theta = (target_position - robot_position).angle();

    auto dTheta = smallestAngleDiff(robot.angle(), go_to_point.target_angle());
    auto v_prop = std::abs(smallestAngleDiff(PI - 0.1, dTheta)) * max_velocity / (PI - 0.1);

    return RobotMove(fromPolar(v_prop, theta), 5 * dTheta);

  } else {
    // anglePID()
    auto dTheta = smallestAngleDiff(robot.angle(), go_to_point.target_angle());

    return RobotMove(5 * dTheta);
  }
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
  const double delta_theta = robocin::smallestAngleDiff(robot.angle(), rotate_in_point.target_angle());
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
