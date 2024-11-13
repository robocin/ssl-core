#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/go_to_ball.h"

#include "ball_analyzer.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"

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

float GoToBall::getMotionAngle(const World& world) const { return true; }

GoToPointMessage::MovingProfile GoToBall::getMotionMovingProfile(const World& world) const {
  return GoToPointMessage::MovingProfile::BalancedInMedianSpeed;
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
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage GoToBall::makeGoToBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
