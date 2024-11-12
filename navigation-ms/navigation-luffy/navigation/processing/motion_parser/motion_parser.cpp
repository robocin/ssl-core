#include "navigation/processing/motion_parser/motion_parser.h"

#include "navigation/processing/entities/ally.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/navigation/navigation_message.h"

#include <cstdlib>
#include <memory>
#include <navigation/parameters/parameters.h>
#include <navigation/processing/entities/robot_move.h>
#include <navigation/processing/utils/moving_profile_util.h>
#include <optional>
#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/angular.h>

namespace navigation {

MotionParser::MotionParser() = default;

NavigationOutputMessage MotionParser::parseMotion(std::unique_ptr<World>& world) {

  NavigationOutputMessage output_msg;
  std::optional<DiscretizedPathMessage> discretized_path;
  RobotMove move;

  if (world->robot_motion) {
    if (world->robot_motion->go_to_point) {
      move = fromGoToPoint(world);
    } else if (world->robot_motion->rotate_in_point) {
      move = fromRotateInPoint(world);
    } else if (world->robot_motion->rotate_on_self) {
      move = fromRotateOnSelf(world);
    } else {
      // PROCESSAMENTO DO GO_TO_POINT_WITH_TRAJECTORY + PLANNING
    }

    output_msg.left_velocity = move.velocity().y;
    output_msg.forward_velocity = move.velocity().x;
    output_msg.angular_velocity = move.angularVelocity();

    if (world->robot_motion->peripheral_actuation) {
      output_msg.peripheral_actuation = std::move(world->robot_motion->peripheral_actuation);
    }
  }

  // TODO: Add other fields to output
  output_msg.robot_id = std::move(world->current_ally.robot_id.value());
  output_msg.sequence_number = sequence_number_;
  sequence_number_ += 1;

  return output_msg;
}
////////////////////////////////////////////////////////////////////////////
RobotMove MotionParser::fromGoToPoint(std::unique_ptr<World>& world) {

  GoToPointMessage& go_to_point = world->robot_motion->go_to_point.value();
  robocin::Point2Df s0 = world->current_ally.position.value();
  robocin::Point2Df s = go_to_point.target.value();
  robocin::Point2Df delta_s = (s - s0) / M_to_MM;

  const float kp = ANGLE_KP;
  const float max_angular_vel = ROBOT_MAX_ANGULAR_VELOCITY;

  auto [minVelocity, maxVelocity]
      = MovingProfileUtil::minAndMaxVelocityToProfile(go_to_point.moving_profile.value());
  float prop_distance
      = MovingProfileUtil::propDistanceToProfile(go_to_point.moving_profile.value());

  if (delta_s.length() <= prop_distance) {
    maxVelocity = std::max(mathematics::map(static_cast<double>(delta_s.length()),
                                            0.0,
                                            static_cast<double>(prop_distance),
                                            minVelocity,
                                            maxVelocity),
                           minVelocity);
  }

  float tolerance_to_target
      = go_to_point.precision_to_target == GoToPointMessage::PrecisionToTarget::HIGH ?
            SMALL_TOLERANCE_TO_DESIRED_POSITION_M :
            DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M;

  const float delta_theta
      = ::robocin::smallestAngleDiff<float>(world->current_ally.angle.value(),
                                            static_cast<float>(go_to_point.target_angle.value()));

  if (delta_s.length() > tolerance_to_target) {

    // Uses an angle PID (only proportional for now), and first try to get in the right
    // angle, using only angular speed and then use linear speed to get into the point
    const float theta = delta_s.angle();
    float acc_prop = moving_profile::ROBOT_DEFAULT_LINEAR_ACCELERATION;
    auto v0 = world->current_ally.velocity.value() / M_to_MM;

    auto v = robocin::Point2D<float>::fromPolar(maxVelocity, theta);
    const float v0_decay = std::abs(v.angleTo(v0)) > PI / 3 ? ROBOT_VEL_BREAK_DECAY_FACTOR :
                                                              ROBOT_VEL_FAVORABLE_DECAY_FACTOR;

    // v = v0 + a*t
    v0 = v0 - (v0 * v0_decay) * CYCLE_STEP;

    auto acceleration_required
        = robocin::Point2D<float>((v.x - v0.x) / CYCLE_STEP, (v.y - v0.y) / CYCLE_STEP);

    float alpha = mathematics::map(std::abs(delta_theta),
                                   0.0F,
                                   static_cast<float>(std::numbers::pi),
                                   0.0F,
                                   1.0F);
    // -x^2 +1
    // float propFactor = (-(alpha * alpha) + 1);

    // (x -1)^2
    float prop_factor = (alpha - 1) * (alpha - 1);
    acc_prop *= prop_factor;

    if (acceleration_required.length() > acc_prop) {
      acceleration_required.resize(acc_prop);
    }

    // v = v0 + a*t
    auto new_velocity = v0 + acceleration_required * CYCLE_STEP;

    if (new_velocity.length() < ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY) {
      new_velocity.resize(ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY);
    }

    return RobotMove{new_velocity, std::clamp(kp * delta_theta, -max_angular_vel, max_angular_vel)};
  }

  return RobotMove{{0, 0}, std::clamp(kp * delta_theta, -max_angular_vel, max_angular_vel)};
}
////////////////////////////////////////////////////////////////////////////
RobotMove MotionParser::fromRotateInPoint(std::unique_ptr<World>& world) {

  RotateInPointMessage& rotate_in_point = world->robot_motion->rotate_in_point.value();
  const float velocity = [&]() {
    float velocity = rotate_in_point.rotate_velocity.value();
    velocity *= rotate_in_point.min_velocity.value();

    return velocity;
  }();

  const float robot_radius
      = (world->current_ally.position.value().distanceTo(rotate_in_point.target.value())) / M_to_MM;
  const float delta_theta = robocin::smallestAngleDiff(world->current_ally.angle.value(),
                                                       rotate_in_point.target_angle.value());
  const float approach_kp = rotate_in_point.approach_kp.value();
  const float angle_kp = rotate_in_point.angle_kp.value();

  // Rotate in the smaller angle
  const float orientation_factor = rotate_in_point.clockwise ? 1.0 : -1.0;
  const robocin::Point2Df coordinates = robocin::Point2Df(
      approach_kp * (robot_radius - rotate_in_point.orbit_radius.value() / M_to_MM),
      orientation_factor * velocity);
  const robocin::Point2Df rotated_coordinates
      = coordinates.rotatedCounterClockWise(world->current_ally.angle.value());
  const float angular_velocity
      = ((-(orientation_factor * velocity) / (rotate_in_point.orbit_radius.value() / M_to_MM))
         + (angle_kp * delta_theta));

  return RobotMove{rotated_coordinates, angular_velocity};
}
////////////////////////////////////////////////////////////////////////////
RobotMove MotionParser::fromRotateOnSelf(std::unique_ptr<World>& world) {

  RotateOnSelfMessage& rotate_on_self = world->robot_motion->rotate_on_self.value();
  auto delta_theta = robocin::smallestAngleDiff<float>(world->current_ally.angle.value(),
                                                       rotate_on_self.target_angle.value());

  return RobotMove{rotate_on_self.velocity.value(),
                   static_cast<float>(rotate_on_self.kp.value()) * delta_theta};
}
////////////////////////////////////////////////////////////////////////////
std::optional<DiscretizedPathMessage>
MotionParser::fromGoToPointWithTrajectory(std::unique_ptr<World>& world) {

  GoToPointWithTrajectoryMessage& go_to_point_with_trajectory
      = world->robot_motion->go_to_point_with_trajectory.value();

  if (MovingProfileUtil::profileRequireDirectGotoPoint(
          go_to_point_with_trajectory.go_to_point->moving_profile.value())) {
    return std::nullopt;
  }

  if (go_to_point_with_trajectory.path_config.has_value()) {
    //   if (auto result = bangBangPathTrajectory(go_to_point_with_trajectory)) {
    //     return result.value();
    //   }
  }

  // if (auto directResult = bangBangDirectTrajectory(go_to_point_with_trajectory)) {
  //   return directResult.value();
  // }

  return std::nullopt;
}
} // namespace navigation
