#ifndef BEHAVIOR_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H

#include "behavior/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

/*
* @class GoToPointMessage
* @brief A class that represents the go to point message.
()
*/
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

  explicit GoToPointMessage(std::optional<robocin::Point2D<float>> target = std::nullopt,
                            std::optional<double> target_angle = std::nullopt,
                            std::optional<MovingProfile> moving_profile = std::nullopt,
                            std::optional<PrecisionToTarget> precision_to_target = std::nullopt,
                            std::optional<bool> sync_rotate_with_linear_movement = std::nullopt);

  [[nodiscard]] protocols::behavior::GoToPoint toProto() const override;

  void fromProto(const protocols::behavior::GoToPoint& go_to_point) override;

  std::optional<robocin::Point2D<float>> target;
  std::optional<double> target_angle;
  std::optional<MovingProfile> moving_profile;
  std::optional<PrecisionToTarget> precision_to_target;
  std::optional<bool> sync_rotate_with_linear_movement;
};

class GoToPointWithTrajectoryMessage
    : public robocin::IProtoConvertible<protocols::behavior::GoToPointWithTrajectory> {
 public:
  GoToPointWithTrajectoryMessage();

  [[nodiscard]] protocols::behavior::GoToPointWithTrajectory toProto() const override {
    protocols::behavior::GoToPointWithTrajectory go_to_point_with_trajectory;
    return go_to_point_with_trajectory;
  };

  void fromProto(
      const protocols::behavior::GoToPointWithTrajectory& go_to_point_with_trajectory) override {
    // Implementação específica para converter de proto para GoToPointWithTrajectoryMessage
  };
};

class RotateInPointMessage : public robocin::IProtoConvertible<protocols::behavior::RotateInPoint> {
 public:
  RotateInPointMessage();

  [[nodiscard]] protocols::behavior::RotateInPoint toProto() const override {
    protocols::behavior::RotateInPoint rotate_in_point;
    return rotate_in_point;
  };

  void fromProto(const protocols::behavior::RotateInPoint& rotate_in_point) override {
    // Implementação específica para converter de proto para RotateInPointMessage
  };
};

class RotateOnSelfMessage : public robocin::IProtoConvertible<protocols::behavior::RotateOnSelf> {
 public:
  RotateOnSelfMessage();

  [[nodiscard]] protocols::behavior::RotateOnSelf toProto() const override {
    protocols::behavior::RotateOnSelf rotate_on_self;
    return rotate_on_self;
  };

  void fromProto(const protocols::behavior::RotateOnSelf& rotate_on_self) override {
    // Implementação específica para converter de proto para RotateOnSelfMessage
  };
};

class MotionMessage : public robocin::IProtoConvertible<protocols::behavior::unification::Motion> {
 public:
  MotionMessage(std::optional<GoToPointMessage> go_to_point = std::nullopt,
                std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory
                = std::nullopt,
                std::optional<RotateInPointMessage> rotate_in_point = std::nullopt,
                std::optional<RotateOnSelfMessage> rotate_on_self = std::nullopt,
                std::optional<PeripheralActuationMessage> peripheral_actuation = std::nullopt);

  [[nodiscard]] protocols::behavior::unification::Motion toProto() const override;

  void fromProto(const protocols::behavior::unification::Motion& motion) override;

  std::optional<GoToPointMessage> go_to_point;
  std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory;
  std::optional<RotateInPointMessage> rotate_in_point;
  std::optional<RotateOnSelfMessage> rotate_on_self;
  std::optional<PeripheralActuationMessage> peripheral_actuation;
};

} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_MOTION_MOTION_MESSAGE_H
