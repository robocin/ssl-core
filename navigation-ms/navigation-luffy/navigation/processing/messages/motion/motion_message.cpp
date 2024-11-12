#include "navigation/processing/messages/motion/motion_message.h"

#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <robocin/geometry/point2d.h>
#include <utility>

namespace navigation {
MotionMessage::MotionMessage() = default;

MotionMessage::MotionMessage(
    std::optional<GoToPointMessage> go_to_point,
    std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory,
    std::optional<RotateInPointMessage> rotate_in_point,
    std::optional<RotateOnSelfMessage> rotate_on_self,
    std::optional<PeripheralActuationMessage> peripheral_actuation) :
    go_to_point(std::move(go_to_point)),
    go_to_point_with_trajectory(std::move(go_to_point_with_trajectory)),
    rotate_in_point(std::move(rotate_in_point)),
    rotate_on_self(std::move(rotate_on_self)),
    peripheral_actuation(std::move(peripheral_actuation)) {}

protocols::behavior::unification::Motion MotionMessage::toProto() const {
  return protocols::behavior::unification::Motion{};
}

MotionMessage::MotionMessage(const protocols::behavior::unification::Motion& motion_proto) {
  MotionMessage::fromProto(motion_proto);
}

void MotionMessage::fromProto(const protocols::behavior::unification::Motion& motion_proto) {
  if (motion_proto.has_go_to_point()) {
    go_to_point = GoToPointMessage(motion_proto.go_to_point());
  }
  if (motion_proto.has_go_to_point_with_trajectory()) {
    go_to_point_with_trajectory
        = GoToPointWithTrajectoryMessage(motion_proto.go_to_point_with_trajectory());
  }
  if (motion_proto.has_rotate_in_point()) {
    rotate_in_point = RotateInPointMessage(motion_proto.rotate_in_point());
  }
  if (motion_proto.has_rotate_on_self()) {
    rotate_on_self = RotateOnSelfMessage(motion_proto.rotate_on_self());
  }
  if (motion_proto.has_peripheral_actuation()) {
    peripheral_actuation = PeripheralActuationMessage(motion_proto.peripheral_actuation());
  }
}
////////////////////////////////////////////////////////////////////////////////////////

PathNodeMessage::PathNodeMessage(std::optional<robocin::Point2Df> position,
                                 std::optional<robocin::Point2Df> velocity,
                                 std::optional<double> time) :
    position(position),
    velocity(velocity),
    time(time) {}

PathNodeMessage::PathNodeMessage(const protocols::behavior::PathNode& path_node_proto) {
  PathNodeMessage::fromProto(path_node_proto);
}

protocols::behavior::PathNode PathNodeMessage::toProto() const {
  protocols::behavior::PathNode path_node_proto;
  if (position.has_value()) {
    path_node_proto.mutable_position()->set_x(position->x);
    path_node_proto.mutable_position()->set_y(position->y);
  }
  if (velocity.has_value()) {
    path_node_proto.mutable_velocity()->set_x(velocity->x);
    path_node_proto.mutable_velocity()->set_y(velocity->y);
  }
  if (time.has_value()) {
    path_node_proto.set_time(time.value());
  }
  return path_node_proto;
}

void PathNodeMessage::fromProto(const protocols::behavior::PathNode& path_node_proto) {
  if (path_node_proto.has_position()) {
    position = robocin::Point2Df{path_node_proto.position().x(), path_node_proto.position().y()};
  }
  if (path_node_proto.has_velocity()) {
    velocity = robocin::Point2Df{path_node_proto.velocity().x(), path_node_proto.velocity().y()};
  }
  time = path_node_proto.time();
}
////////////////////////////////////////////////////////////////////////////////////////
DiscretizedPathMessage::DiscretizedPathMessage() = default;
DiscretizedPathMessage::DiscretizedPathMessage(std::vector<PathNodeMessage> path,
                                               GoToPointMessage go_to_point) :
    path(std::move(path)),
    go_to_point(std::move(go_to_point)) {}

DiscretizedPathMessage::DiscretizedPathMessage(
    const protocols::behavior::DiscretizedPath& discretized_path_proto) {
  DiscretizedPathMessage::fromProto(discretized_path_proto);
}

[[nodiscard]] protocols::behavior::DiscretizedPath DiscretizedPathMessage::toProto() const {
  return protocols::behavior::DiscretizedPath{};
}

void DiscretizedPathMessage::fromProto(
    const protocols::behavior::DiscretizedPath& discretized_path_proto) {
  for (const auto& path_proto : discretized_path_proto.path()) {
    path.emplace_back(path_proto);
  }
  if (discretized_path_proto.has_go_to_point()) {
    go_to_point = GoToPointMessage(discretized_path_proto.go_to_point());
  }
};
////////////////////////////////////////////////////////////////////////////////////////

GoToPointMessage::MovingProfile
convertToLocalMovingProfile(protocols::behavior::MovingProfile proto_profile) {
  switch (proto_profile) {
    case protocols::behavior::SafeInStopSpeed: return GoToPointMessage::SafeInStopSpeed;
    case protocols::behavior::BalancedInApproachBallSpeed:
      return GoToPointMessage::BalancedInApproachBallSpeed;
    case protocols::behavior::BalancedInCarryBallSpeed:
      return GoToPointMessage::BalancedInCarryBallSpeed;
    case protocols::behavior::BalancedInCarryBallLowSpeed:
      return GoToPointMessage::BalancedInCarryBallLowSpeed;
    case protocols::behavior::DirectApproachBallSpeed:
      return GoToPointMessage::DirectApproachBallSpeed;
    case protocols::behavior::DirectSafeKickBallSpeed:
      return GoToPointMessage::DirectSafeKickBallSpeed;
    case protocols::behavior::DirectBalancedKickBallSpeed:
      return GoToPointMessage::DirectBalancedKickBallSpeed;
    case protocols::behavior::DirectKickBallwithEnemyClose:
      return GoToPointMessage::DirectKickBallwithEnemyClose;
    case protocols::behavior::gotoBallWithEnemy: return GoToPointMessage::gotoBallWithEnemy;
    case protocols::behavior::PushBallInPenalty: return GoToPointMessage::PushBallInPenalty;
    case protocols::behavior::TOTOZINHO: return GoToPointMessage::TOTOZINHO;
    case protocols::behavior::BalancedInSlowSpeed: return GoToPointMessage::BalancedInSlowSpeed;
    case protocols::behavior::BalancedInMedianSpeed: return GoToPointMessage::BalancedInMedianSpeed;
    case protocols::behavior::BalancedInDefaultSpeed:
      return GoToPointMessage::BalancedInDefaultSpeed;
    case protocols::behavior::BalancedInHighSpeed: return GoToPointMessage::BalancedInHighSpeed;
    case protocols::behavior::GoalkeeperInTopSpeed: return GoToPointMessage::GoalkeeperInTopSpeed;
    case protocols::behavior::PenaltyPushBall: return GoToPointMessage::PenaltyPushBall;
    default: return GoToPointMessage::SafeInStopSpeed; // Default case if needed
  }
}

GoToPointMessage::PrecisionToTarget
convertPrecisionToTargetFromProto(protocols::behavior::PrecisionToTarget localPrecision) {
  switch (localPrecision) {
    case protocols::behavior::High: return GoToPointMessage::HIGH;
    default:
      return GoToPointMessage::NORMAL;
      // Default to NORMAL or handle as appropriate
  }
}

GoToPointMessage::GoToPointMessage(std::optional<robocin::Point2D<float>> target,
                                   std::optional<double> target_angle,
                                   std::optional<MovingProfile> moving_profile,
                                   std::optional<PrecisionToTarget> precision_to_target,
                                   std::optional<bool> sync_rotate_with_linear_movement) :
    target(target),
    target_angle(target_angle),
    moving_profile(moving_profile),
    precision_to_target(precision_to_target),
    sync_rotate_with_linear_movement(sync_rotate_with_linear_movement) {}

GoToPointMessage::GoToPointMessage(const protocols::behavior::GoToPoint& go_to_point_proto) {
  GoToPointMessage::fromProto(go_to_point_proto);
}

protocols::behavior::GoToPoint GoToPointMessage::toProto() const {
  return protocols::behavior::GoToPoint{};
};

void GoToPointMessage::fromProto(const protocols::behavior::GoToPoint& go_to_point_proto) {
  if (go_to_point_proto.has_target()) {
    target = robocin::Point2Df{go_to_point_proto.target().x(), go_to_point_proto.target().y()};
  }
  target_angle = go_to_point_proto.target_angle();
  moving_profile = convertToLocalMovingProfile(go_to_point_proto.moving_profile());
  precision_to_target = convertPrecisionToTargetFromProto(go_to_point_proto.precision_to_target());
  sync_rotate_with_linear_movement = go_to_point_proto.sync_rotate_with_linear_movement();
}

////////////////////////////////////////////////////////////////////////////////////////
RotateOnSelfMessage::RotateOnSelfMessage(std::optional<double> target_angle,
                                         std::optional<robocin::Point2Df> velocity,
                                         std::optional<double> kp) :
    target_angle(target_angle),
    velocity(velocity),
    kp(kp) {}

RotateOnSelfMessage::RotateOnSelfMessage(
    const protocols::behavior::RotateOnSelf& rotate_on_self_proto) {
  RotateOnSelfMessage::fromProto(rotate_on_self_proto);
}

void RotateOnSelfMessage::fromProto(const protocols::behavior::RotateOnSelf& rotate_on_self_proto) {
  double target_angle = rotate_on_self_proto.target_angle();
  if (rotate_on_self_proto.has_velocity()) {
    velocity = robocin::Point2Df{rotate_on_self_proto.velocity().x(),
                                 rotate_on_self_proto.velocity().y()};
  }
  double kp = rotate_on_self_proto.kp();
}

protocols::behavior::RotateOnSelf RotateOnSelfMessage::toProto() const {
  return protocols::behavior::RotateOnSelf{};
};
////////////////////////////////////////////////////////////////////////////////////////
RotateInPointMessage::RotateInPointMessage(std::optional<robocin::Point2Df> target,
                                           std::optional<double> target_angle,
                                           std::optional<bool> clockwise,
                                           std::optional<double> orbit_radius,
                                           std::optional<double> rotate_velocity,
                                           std::optional<double> min_velocity,
                                           std::optional<double> approach_kp,
                                           std::optional<double> angle_kp) :
    target(target),
    target_angle(target_angle),
    clockwise(clockwise),
    orbit_radius(orbit_radius),
    rotate_velocity(rotate_velocity),
    min_velocity(min_velocity),
    approach_kp(approach_kp),
    angle_kp(angle_kp) {}

RotateInPointMessage::RotateInPointMessage(
    const protocols::behavior::RotateInPoint& rotate_in_point_proto) {
  RotateInPointMessage::fromProto(rotate_in_point_proto);
}

void RotateInPointMessage::fromProto(
    const protocols::behavior::RotateInPoint& rotate_in_point_proto) {
  if (rotate_in_point_proto.has_target()) {
    target
        = robocin::Point2Df{rotate_in_point_proto.target().x(), rotate_in_point_proto.target().y()};
  }
  target_angle = rotate_in_point_proto.target_angle();
  clockwise = rotate_in_point_proto.clockwise();
  orbit_radius = rotate_in_point_proto.orbit_radius();
  rotate_velocity = rotate_in_point_proto.rotate_velocity();
  min_velocity = rotate_in_point_proto.min_velocity();
  approach_kp = rotate_in_point_proto.approach_kp();
  angle_kp = rotate_in_point_proto.angle_kp();
}

protocols::behavior::RotateInPoint RotateInPointMessage::toProto() const {
  return protocols::behavior::RotateInPoint{};
};

////////////////////////////////////////////////////////////////////////////////////////
PathConfigMessage::PathConfigMessage(std::optional<robocin::Point2Df> target_velocity,
                                     std::optional<bool> avoid_ball,
                                     std::optional<bool> avoid_ball_placement,
                                     std::optional<bool> avoid_ally_penalty_area,
                                     std::optional<bool> avoid_enemy_penalty_area,
                                     std::optional<bool> avoid_ally_robots,
                                     std::optional<bool> avoid_enemy_robots,
                                     std::vector<int32_t> ally_skipped,
                                     std::vector<int32_t> enemy_skipped) :
    target_velocity(target_velocity),
    avoid_ball(avoid_ball),
    avoid_ball_placement(avoid_ball_placement),
    avoid_ally_penalty_area(avoid_ally_penalty_area),
    avoid_enemy_penalty_area(avoid_enemy_penalty_area),
    avoid_ally_robots(avoid_ally_robots),
    avoid_enemy_robots(avoid_enemy_robots),
    ally_skipped(std::move(ally_skipped)),
    enemy_skipped(std::move(enemy_skipped)) {}

PathConfigMessage::PathConfigMessage(const protocols::behavior::PathConfig& path_config_proto) {
  PathConfigMessage::fromProto(path_config_proto);
}

void PathConfigMessage::fromProto(const protocols::behavior::PathConfig& path_config_proto) {
  if (path_config_proto.has_target_velocity()) {
    target_velocity = robocin::Point2Df{path_config_proto.target_velocity().x(),
                                        path_config_proto.target_velocity().y()};
  }
  bool avoid_ball = path_config_proto.avoid_ball();
  bool avoid_ball_placement = path_config_proto.avoid_ball_placement();
  bool avoid_ally_penalty_area = path_config_proto.avoid_ally_penalty_area();
  bool avoid_enemy_penalty_area = path_config_proto.avoid_enemy_penalty_area();
  bool avoid_ally_robots = path_config_proto.avoid_ally_robots();
  bool avoid_enemy_robots = path_config_proto.avoid_enemy_robots();

  for (auto ally_skipped_proto : path_config_proto.ally_skipped()) {
    ally_skipped.emplace_back(ally_skipped_proto);
  }
  for (auto enemy_skipped_proto : path_config_proto.ally_skipped()) {
    enemy_skipped.emplace_back(enemy_skipped_proto);
  }
}
protocols::behavior::PathConfig PathConfigMessage::toProto() const {
  return protocols::behavior::PathConfig{};
};
////////////////////////////////////////////////////////////////////////////////////////

GoToPointWithTrajectoryMessage::GoToPointWithTrajectoryMessage() = default;
GoToPointWithTrajectoryMessage::GoToPointWithTrajectoryMessage(
    std::optional<GoToPointMessage> go_to_point,
    std::optional<PathConfigMessage> path_config) :
    go_to_point(std::move(go_to_point)),
    path_config(std::move(path_config)) {}

GoToPointWithTrajectoryMessage::GoToPointWithTrajectoryMessage(
    const protocols::behavior::GoToPointWithTrajectory& go_to_point_with_trajectory_proto) {
  GoToPointWithTrajectoryMessage::fromProto(go_to_point_with_trajectory_proto);
}

protocols::behavior::GoToPointWithTrajectory GoToPointWithTrajectoryMessage::toProto() const {
  return protocols::behavior::GoToPointWithTrajectory{};
};

void GoToPointWithTrajectoryMessage::fromProto(
    const protocols::behavior::GoToPointWithTrajectory& go_to_point_with_trajectory_proto) {
  if (go_to_point.has_value()) {
    go_to_point = GoToPointMessage(go_to_point_with_trajectory_proto.go_to_point());
  }
  if (path_config.has_value()) {
    path_config = PathConfigMessage(go_to_point_with_trajectory_proto.path_config());
  }
}
} // namespace navigation
