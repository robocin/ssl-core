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

  GoToPointMessage();
  GoToPointMessage(robocin::Point2D<float> target,
                   double target_angle,
                   MovingProfile moving_profile,
                   PrecisionToTarget precision_to_target,
                   bool sync_rotate_with_linear_movement);
  explicit GoToPointMessage(const protocols::behavior::GoToPoint& go_to_point_proto);

  robocin::Point2D<float> target;
  double target_angle;
  MovingProfile moving_profile;
  PrecisionToTarget precision_to_target;
  bool sync_rotate_with_linear_movement;

  [[nodiscard]] protocols::behavior::GoToPoint toProto() const override;

  void fromProto(const protocols::behavior::GoToPoint& go_to_point_proto) override;
};

class PathConfigMessage : public robocin::IProtoConvertible<protocols::behavior::PathConfig> {
 public:
  PathConfigMessage();
  PathConfigMessage(robocin::Point2Df target_velocity,
                    bool avoid_ball,
                    bool avoid_ball_placement,
                    bool avoid_ally_penalty_area,
                    bool avoid_enemy_penalty_area,
                    bool avoid_ally_robots,
                    bool avoid_enemy_robots,
                    std::vector<int32_t> ally_skipped,
                    std::vector<int32_t> enemy_skipped);
  explicit PathConfigMessage(const protocols::behavior::PathConfig& path_config_proto);
  [[nodiscard]] protocols::behavior::PathConfig toProto() const override;

  robocin::Point2Df target_velocity;
  bool avoid_ball;
  bool avoid_ball_placement;
  bool avoid_ally_penalty_area;
  bool avoid_enemy_penalty_area;
  bool avoid_ally_robots;
  bool avoid_enemy_robots;

  std::vector<int32_t> ally_skipped;
  std::vector<int32_t> enemy_skipped;

  void fromProto(const protocols::behavior::PathConfig& path_config_proto) override;
};

class PathNodeMessage : public robocin::IProtoConvertible<protocols::behavior::PathNode> {
 public:
  PathNodeMessage();
  PathNodeMessage(robocin::Point2Df position, robocin::Point2Df velocity, double time);
  explicit PathNodeMessage(const protocols::behavior::PathNode& path_node_proto);

  [[nodiscard]] protocols::behavior::PathNode toProto() const override;

  robocin::Point2Df position;
  robocin::Point2Df velocity;
  double time;

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
  GoToPointWithTrajectoryMessage(GoToPointMessage go_to_point, PathConfigMessage path_config);
  explicit GoToPointWithTrajectoryMessage(
      const protocols::behavior::GoToPointWithTrajectory& go_to_point_with_trajectory_proto);
  [[nodiscard]] protocols::behavior::GoToPointWithTrajectory toProto() const override;

  GoToPointMessage go_to_point;
  PathConfigMessage path_config;

  void fromProto(const protocols::behavior::GoToPointWithTrajectory&
                     go_to_point_with_trajectory_proto) override;
};

class RotateInPointMessage : public robocin::IProtoConvertible<protocols::behavior::RotateInPoint> {
 public:
  RotateInPointMessage();
  RotateInPointMessage(robocin::Point2Df target,
                       double target_angle,
                       bool clockwise,
                       double orbit_radius,
                       double rotate_velocity,
                       double min_velocity,
                       double approach_kp,
                       double angle_kp);
  explicit RotateInPointMessage(const protocols::behavior::RotateInPoint& rotate_in_point_proto);
  [[nodiscard]] protocols::behavior::RotateInPoint toProto() const override;

  robocin::Point2Df target;
  double target_angle;
  bool clockwise;
  double orbit_radius;
  double rotate_velocity;
  double min_velocity;
  double approach_kp;
  double angle_kp;

  void fromProto(const protocols::behavior::RotateInPoint& rotate_in_point_proto) override;
};

class RotateOnSelfMessage : public robocin::IProtoConvertible<protocols::behavior::RotateOnSelf> {
 public:
  RotateOnSelfMessage();
  explicit RotateOnSelfMessage(const protocols::behavior::RotateOnSelf& rotate_on_self_proto);
  RotateOnSelfMessage(double target_angle, robocin::Point2Df velocity, double kp);
  [[nodiscard]] protocols::behavior::RotateOnSelf toProto() const override;

  double target_angle;
  robocin::Point2Df velocity;
  double kp;

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
