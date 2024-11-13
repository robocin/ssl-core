#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/go_to_ball.h"

#include "ally_analyzer.h"
#include "ball_analyzer.h"
#include "behavior/parameters/parameters.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"

#include <robocin/geometry/point2d.h>

namespace behavior {

GoToBall::GoToBall() = default;

OutputMessage GoToBall::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec GoToBall state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  checkAndHandleTransitions(world);
  return makeGoToBallOutput(world);
}

void GoToBall::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToKickBall(world)) {
    state_machine_->transitionTo(new KickBall);
    return;
  }
  if (shouldTransitionToAlign(world)) {
    state_machine_->transitionTo(new Align);
    return;
  }
}

bool GoToBall::shouldTransitionToAlign(const World& world) const {
  return (ForwardFollowAndKickBallCommon::isAllyBehindBall(world, ally_id_.number.value())
          && ForwardFollowAndKickBallCommon::isBallInRangeToKick(world, ally_id_.number.value())
          && BallAnalyzer::isBallMoving(world.ball));
}

bool GoToBall::shouldTransitionToKickBall(const World& world) const {
  return (
      ForwardFollowAndKickBallCommon::isAllyLookingToTargetAndBall(world, ally_id_.number.value())
      && ForwardFollowAndKickBallCommon::isBallInRangeToKick(world, ally_id_.number.value())
      && !ForwardFollowAndKickBallCommon::isBallInsideEnemyArea(world));
}

robocin::Point2Df GoToBall::getMotionTarget(const World& world) const {
  return AllyAnalyzer::targetBehindBallLookingToTarget(
      world,
      ally_id_.number.value(),
      ForwardFollowAndKickBallCommon::getKickTarget(),
      pApproachAngleThreshold());
}

float GoToBall::getMotionAngle(const World& world) const {
  std::optional<RobotMessage> ally
      = ForwardFollowAndKickBallCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return 0.0f;
  }

  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df kick_target = ForwardFollowAndKickBallCommon::getKickTarget();

  const float ally_to_ball_distance = ally_position.distanceTo(ball_position);
  const float ball_radius = 22.0f;

  robocin::Point2Df ball_to_kick_target_vector = kick_target - ball_position;
  robocin::Point2Df ally_to_ball_vector = ball_position - ally_position;

  bool is_forward_close_to_ball = ally_to_ball_distance < pRobotRadius() + 2 * ball_radius;

  bool have_enough_angle_to_look_to_target
      = std::abs(mathematics::angleBetween(ball_to_kick_target_vector, ally_to_ball_vector))
        < mathematics::degreesToRadians(60);

  if (is_forward_close_to_ball && (!have_enough_angle_to_look_to_target)) {
    return (ball_position - ally_position).angle();
  }
  return (kick_target - ball_position).angle();
}

GoToPointMessage::MovingProfile GoToBall::getMotionMovingProfile(const World& world) const {
  return GoToPointMessage::MovingProfile::BalancedInDefaultSpeed;
}

KickCommandMessage GoToBall::makeKickCommandMessage(const World& world) {
  return KickCommandMessage{0.0, false, false, true, false};
}

PeripheralActuationMessage GoToBall::makePeripheralActuation(const World& world) {
  return PeripheralActuationMessage{makeKickCommandMessage(world)};
}

OutputMessage GoToBall::makeGoToBallOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeGoToBallRobotId(world)},
                       MotionMessage{makeGoToBallMotion(world)},
                       PlanningMessage{makeGoToBallPlanning(world)}};
}

RobotIdMessage GoToBall::makeGoToBallRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage GoToBall::makeGoToBallMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point),
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       makePeripheralActuation(world)};
};

PlanningMessage GoToBall::makeGoToBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
