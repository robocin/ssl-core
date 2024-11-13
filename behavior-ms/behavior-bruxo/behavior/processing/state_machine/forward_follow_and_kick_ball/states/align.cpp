#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/align.h"

#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"

namespace behavior {

Align::Align() = default;

OutputMessage Align::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec Align state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  std::cout << " ball position in goalkeeper fsm: " << ball_position.x << " " << ball_position.y
            << std::endl;
  checkAndHandleTransitions(world);
  return makeAlignOutput(world);
}

void Align::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToGoToBall(world)) {
    state_machine_->transitionTo(new GoToBall);
    return;
  }
  if (shouldTransitionToKickBall(world)) {
    state_machine_->transitionTo(new KickBall);
    return;
  }
}

bool Align::shouldTransitionToGoToBall(const World& world) const {
  return (!ForwardFollowAndKickBallCommon::isAllyBehindBall(world, ally_id_.number.value())
          || ForwardFollowAndKickBallCommon::allyLostBall(world, ally_id_.number.value())
          || ForwardFollowAndKickBallCommon::isBallInsideEnemyArea(world));
}

bool Align::shouldTransitionToKickBall(const World& world) const {
  return ForwardFollowAndKickBallCommon::isAllyNotLookingToTargetAndBall(world,
                                                                         ally_id_.number.value())
         && ForwardFollowAndKickBallCommon::isBallInRangeToKick(world, ally_id_.number.value());
}

float Align::getMotionAngle(const World& world) const { return true; }

GoToPointMessage::MovingProfile Align::getMotionMovingProfile(const World& world) const {
  return GoToPointMessage::MovingProfile::BalancedInMedianSpeed;
}

OutputMessage Align::makeAlignOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeAlignRobotId(world)},
                       MotionMessage{makeAlignMotion(world)},
                       PlanningMessage{makeAlignPlanning(world)}};
}

RobotIdMessage Align::makeAlignRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage Align::makeAlignMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage Align::makeAlignPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
