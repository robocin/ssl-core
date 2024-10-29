#ifndef DECISION_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id_message.h"
#include "protocols/behavior/behavior_unification.pb.h"
#include "robocin/geometry/point2d.h"

#include <optional>
#include <protocols/behavior/motion.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>

namespace decision {

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

  GoToPointMessage(std::optional<robocin::Point2D<float>> target = std::nullopt,
                   std::optional<double> target_angle = std::nullopt,
                   std::optional<MovingProfile> moving_profile = std::nullopt,
                   std::optional<PrecisionToTarget> precision_to_target = std::nullopt,
                   std::optional<bool> sync_rotate_with_linear_movement = std::nullopt);

  std::optional<robocin::Point2D<float>> target;
  std::optional<double> target_angle;
  std::optional<MovingProfile> moving_profile;
  std::optional<PrecisionToTarget> precision_to_target;
  std::optional<bool> sync_rotate_with_linear_movement;

  [[nodiscard]] protocols::behavior::GoToPoint toProto() const override {
    return protocols::behavior::GoToPoint{};
  };

  void fromProto(const protocols::behavior::GoToPoint& go_to_point_proto) override;
};

class GoToPointWithTrajectoryMessage
    : public robocin::IProtoConvertible<protocols::behavior::GoToPointWithTrajectory> {
 public:
  GoToPointWithTrajectoryMessage();
  [[nodiscard]] protocols::behavior::GoToPointWithTrajectory toProto() const override {
    return protocols::behavior::GoToPointWithTrajectory{};
  };
  void fromProto(const protocols::behavior::GoToPointWithTrajectory&
                     go_to_point_with_trajectory_proto) override;
};

class RotateInPointMessage : public robocin::IProtoConvertible<protocols::behavior::RotateInPoint> {
 public:
  RotateInPointMessage();
  [[nodiscard]] protocols::behavior::RotateInPoint toProto() const override {
    return protocols::behavior::RotateInPoint{};
  };

  void fromProto(const protocols::behavior::RotateInPoint& rotate_in_point_proto) override;
};

class RotateOnSelfMessage : public robocin::IProtoConvertible<protocols::behavior::RotateOnSelf> {
 public:
  RotateOnSelfMessage();
  [[nodiscard]] protocols::behavior::RotateOnSelf toProto() const override {
    return protocols::behavior::RotateOnSelf{};
  };

  void fromProto(const protocols::behavior::RotateOnSelf& rotate_on_self_proto) override;
};

class MotionMessage : public robocin::IProtoConvertible<protocols::behavior::unification::Motion> {
 public:
  MotionMessage(std::optional<GoToPointMessage> go_to_point = std::nullopt,
                std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory
                = std::nullopt,
                std::optional<RotateInPointMessage> rotate_in_point = std::nullopt,
                std::optional<RotateOnSelfMessage> rotate_on_self = std::nullopt);

  std::optional<GoToPointMessage> go_to_point;
  std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory;
  std::optional<RotateInPointMessage> rotate_in_point;
  std::optional<RotateOnSelfMessage> rotate_on_self;

  [[nodiscard]] protocols::behavior::unification::Motion toProto() const override {
    return protocols::behavior::unification::Motion{};
  };

  void fromProto(const protocols::behavior::unification::Motion& motion_proto) override;
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H
