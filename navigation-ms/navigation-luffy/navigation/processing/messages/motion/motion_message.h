#ifndef NAVIGATION_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H
#define NAVIGATION_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H

#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"
#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "protocols/behavior/behavior_unification.pb.h"
#include "robocin/geometry/point2d.h"

#include <cstdint>
#include <optional>
#include <protocols/behavior/motion.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>
#include <vector>

namespace navigation {

class GoToPointMessage : public robocin::IProtoConvertible<protocols::behavior::GoToPoint> {
 public:
  enum MovingProfile {
    // Move safely profile
    SafeInStopSpeed = 0,

    // Specific movement profile
    BalancedInApproachBallSpeed = 1,
    BalancedInCarryBallSpeed = 2,
    BalancedInCarryBallLowSpeed = 3,

    // Goto point direct profile
    DirectApproachBallSpeed = 4,
    DirectSafeKickBallSpeed = 5,
    DirectBalancedKickBallSpeed = 6,
    DirectKickBallwithEnemyClose = 7,
    gotoBallWithEnemy = 8,
    PushBallInPenalty = 9,
    TOTOZINHO = 10,

    // Default movement profile
    BalancedInSlowSpeed = 11,
    BalancedInMedianSpeed = 12,
    BalancedInDefaultSpeed = 13,
    BalancedInHighSpeed = 14,

    // Goalkepper profile
    GoalkeeperInTopSpeed = 15,

    // Penalty push ball
    PenaltyPushBall = 16,
  };

  enum PrecisionToTarget {
    HIGH = 0,
    NORMAL = 1,
  };

  std::optional<robocin::Point2D<float>> target;
  std::optional<double> target_angle;
  std::optional<MovingProfile> moving_profile;
  std::optional<PrecisionToTarget> precision_to_target;
  std::optional<bool> sync_rotate_with_linear_movement;

  explicit GoToPointMessage(std::optional<robocin::Point2D<float>> target = std::nullopt,
                            std::optional<double> target_angle = std::nullopt,
                            std::optional<MovingProfile> moving_profile = std::nullopt,
                            std::optional<PrecisionToTarget> precision_to_target = std::nullopt,
                            std::optional<bool> sync_rotate_with_linear_movement = std::nullopt);

  explicit GoToPointMessage(const protocols::behavior::GoToPoint& go_to_point_proto);

  [[nodiscard]] protocols::behavior::GoToPoint toProto() const override;

  void fromProto(const protocols::behavior::GoToPoint& go_to_point_proto) override;
};

class PathConfigMessage : public robocin::IProtoConvertible<protocols::behavior::PathConfig> {
 public:
  std::optional<robocin::Point2Df> target_velocity;
  std::optional<bool> avoid_ball;
  std::optional<bool> avoid_ball_placement;
  std::optional<bool> avoid_ally_penalty_area;
  std::optional<bool> avoid_enemy_penalty_area;
  std::optional<bool> avoid_ally_robots;
  std::optional<bool> avoid_enemy_robots;
  std::vector<int32_t> ally_skipped;
  std::vector<int32_t> enemy_skipped;

  PathConfigMessage(std::optional<robocin::Point2Df> target_velocity = std::nullopt,
                    std::optional<bool> avoid_ball = std::nullopt,
                    std::optional<bool> avoid_ball_placement = std::nullopt,
                    std::optional<bool> avoid_ally_penalty_area = std::nullopt,
                    std::optional<bool> avoid_enemy_penalty_area = std::nullopt,
                    std::optional<bool> avoid_ally_robots = std::nullopt,
                    std::optional<bool> avoid_enemy_robots = std::nullopt,
                    std::vector<int32_t> ally_skipped = {},
                    std::vector<int32_t> enemy_skipped = {});

  explicit PathConfigMessage(const protocols::behavior::PathConfig& path_config_proto);
  [[nodiscard]] protocols::behavior::PathConfig toProto() const override;

  void fromProto(const protocols::behavior::PathConfig& path_config_proto) override;
};

class PathNodeMessage : public robocin::IProtoConvertible<protocols::behavior::PathNode> {
 public:
  std::optional<robocin::Point2Df> position;
  std::optional<robocin::Point2Df> velocity;
  std::optional<double> time;

  explicit PathNodeMessage(std::optional<robocin::Point2Df> position = std::nullopt,
                           std::optional<robocin::Point2Df> velocity = std::nullopt,
                           std::optional<double> time = std::nullopt);

  explicit PathNodeMessage(const protocols::behavior::PathNode& path_node_proto);

  [[nodiscard]] protocols::behavior::PathNode toProto() const override;

  void fromProto(const protocols::behavior::PathNode& path_node_proto) override;
};

class DiscretizedPathMessage
    : public robocin::IProtoConvertible<protocols::behavior::DiscretizedPath> {
 public:
  DiscretizedPathMessage();
  DiscretizedPathMessage(std::vector<PathNodeMessage> path, GoToPointMessage go_to_point);
  explicit DiscretizedPathMessage(
      const protocols::behavior::DiscretizedPath& discretized_path_proto);

  [[nodiscard]] protocols::behavior::DiscretizedPath toProto() const override;

  std::vector<PathNodeMessage> path;
  GoToPointMessage go_to_point;

  void fromProto(const protocols::behavior::DiscretizedPath& discretized_path_proto) override;
};
class GoToPointWithTrajectoryMessage
    : public robocin::IProtoConvertible<protocols::behavior::GoToPointWithTrajectory> {
 public:
  GoToPointWithTrajectoryMessage();
  GoToPointWithTrajectoryMessage(std::optional<GoToPointMessage> go_to_point = std::nullopt,
                                 std::optional<PathConfigMessage> path_config = std::nullopt);
  explicit GoToPointWithTrajectoryMessage(
      const protocols::behavior::GoToPointWithTrajectory& go_to_point_with_trajectory_proto);
  [[nodiscard]] protocols::behavior::GoToPointWithTrajectory toProto() const override;

  std::optional<GoToPointMessage> go_to_point;
  std::optional<PathConfigMessage> path_config;

  void fromProto(const protocols::behavior::GoToPointWithTrajectory&
                     go_to_point_with_trajectory_proto) override;
};

class RotateInPointMessage : public robocin::IProtoConvertible<protocols::behavior::RotateInPoint> {
 public:
  explicit RotateInPointMessage(std::optional<robocin::Point2Df> target = std::nullopt,
                                std::optional<double> target_angle = std::nullopt,
                                std::optional<bool> clockwise = std::nullopt,
                                std::optional<double> orbit_radius = std::nullopt,
                                std::optional<double> rotate_velocity = std::nullopt,
                                std::optional<double> min_velocity = std::nullopt,
                                std::optional<double> approach_kp = std::nullopt,
                                std::optional<double> angle_kp = std::nullopt);
  explicit RotateInPointMessage(const protocols::behavior::RotateInPoint& rotate_in_point_proto);
  [[nodiscard]] protocols::behavior::RotateInPoint toProto() const override;

  std::optional<robocin::Point2Df> target;
  std::optional<double> target_angle;
  std::optional<bool> clockwise;
  std::optional<double> orbit_radius;
  std::optional<double> rotate_velocity;
  std::optional<double> min_velocity;
  std::optional<double> approach_kp;
  std::optional<double> angle_kp;

  void fromProto(const protocols::behavior::RotateInPoint& rotate_in_point_proto) override;
};

class RotateOnSelfMessage : public robocin::IProtoConvertible<protocols::behavior::RotateOnSelf> {
 public:
  explicit RotateOnSelfMessage(const protocols::behavior::RotateOnSelf& rotate_on_self_proto);
  explicit RotateOnSelfMessage(std::optional<double> target_angle = std::nullopt,
                               std::optional<robocin::Point2Df> velocity = std::nullopt,
                               std::optional<double> kp = std::nullopt);
  [[nodiscard]] protocols::behavior::RotateOnSelf toProto() const override;

  std::optional<double> target_angle;
  std::optional<robocin::Point2Df> velocity;
  std::optional<double> kp;

  void fromProto(const protocols::behavior::RotateOnSelf& rotate_on_self_proto) override;
};

class MotionMessage : public robocin::IProtoConvertible<protocols::behavior::unification::Motion> {
 public:
  MotionMessage();

  explicit MotionMessage(std::optional<GoToPointMessage> go_to_point = std::nullopt,
                         std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory
                         = std::nullopt,
                         std::optional<RotateInPointMessage> rotate_in_point = std::nullopt,
                         std::optional<RotateOnSelfMessage> rotate_on_self = std::nullopt,
                         std::optional<PeripheralActuationMessage> peripheral_actuation
                         = std::nullopt);

  explicit MotionMessage(const protocols::behavior::unification::Motion& motion_proto);

  std::optional<GoToPointMessage> go_to_point;
  std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory;
  std::optional<RotateInPointMessage> rotate_in_point;
  std::optional<RotateOnSelfMessage> rotate_on_self;
  std::optional<PeripheralActuationMessage> peripheral_actuation;

  [[nodiscard]] protocols::behavior::unification::Motion toProto() const override;

  void fromProto(const protocols::behavior::unification::Motion& motion_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H
