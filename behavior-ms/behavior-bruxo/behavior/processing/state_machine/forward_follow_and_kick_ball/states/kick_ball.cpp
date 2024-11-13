#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/kick_ball.h"

#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"

namespace behavior {

KickBall::KickBall() = default;

OutputMessage KickBall::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec KickBall state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  checkAndHandleTransitions(world);
  return makeKickBallOutput(world);
}

void KickBall::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToGoToBall(world)) {
    state_machine_->transitionTo(new GoToBall);
    return;
  }
  if (shouldTransitionToAlign(world)) {
    state_machine_->transitionTo(new Align);
    return;
  }
}

bool KickBall::shouldTransitionToAlign(const World& world) const {
  return (ForwardFollowAndKickBallCommon::isAllyNotLookingToTargetAndBall(world,
                                                                          ally_id_.number.value())
          && !ForwardFollowAndKickBallCommon::allyLostBall(world, ally_id_.number.value())
          && !ForwardFollowAndKickBallCommon::isBallOnDribblerWithoutCheckingForAlignment(
              world,
              ally_id_.number.value()));
}

bool KickBall::shouldTransitionToGoToBall(const World& world) const {
  return (!ForwardFollowAndKickBallCommon::isAllyBehindBall(world, ally_id_.number.value())
          || ForwardFollowAndKickBallCommon::allyLostBall(world, ally_id_.number.value())
          || ForwardFollowAndKickBallCommon::isBallInsideEnemyArea(world));
}

float KickBall::getMotionAngle(const World& world) const { return true; }

GoToPointMessage::MovingProfile KickBall::getMotionMovingProfile(const World& world) const {
  return GoToPointMessage::MovingProfile::BalancedInMedianSpeed;
}

OutputMessage KickBall::makeKickBallOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeKickBallRobotId(world)},
                       MotionMessage{makeKickBallMotion(world)},
                       PlanningMessage{makeKickBallPlanning(world)}};
}

RobotIdMessage KickBall::makeKickBallRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage KickBall::makeKickBallMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage KickBall::makeKickBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
