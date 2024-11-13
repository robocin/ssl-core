#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/kick_ball.h"

#include "behavior/parameters/parameters.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"
#include "common/peripheral_actuation/peripheral_actuation.h"
#include "common/robot_kick/kick_command.h"

#include <robocin/geometry/point2d.h>

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

robocin::Point2Df KickBall::getMotionTarget(const World& world) const {
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  return ball_position;
}

float KickBall::getMotionAngle(const World& world) const {
  robocin::Point2Df kick_target = ForwardFollowAndKickBallCommon::getKickTarget();
  robocin::Point2Df target_position = getMotionTarget(world);
  return (kick_target - target_position).angle();
}

GoToPointMessage::MovingProfile KickBall::getMotionMovingProfile(const World& world) const {
  return GoToPointMessage::MovingProfile::DirectBalancedKickBallSpeed;
}

KickCommandMessage KickBall::makeKickCommandMessage(const World& world) {
  return KickCommandMessage{pFrontKickStrenght(), true, false, false, false};
}

PeripheralActuationMessage KickBall::makePeripheralActuation(const World& world) {
  return PeripheralActuationMessage{makeKickCommandMessage(world)};
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
  return MotionMessage{std::move(go_to_point),
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       makePeripheralActuation(world)};
};

PlanningMessage KickBall::makeKickBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
