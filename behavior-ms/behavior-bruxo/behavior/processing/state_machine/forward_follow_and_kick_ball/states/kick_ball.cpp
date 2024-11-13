#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/kick_ball.h"

namespace behavior {

KickBall::KickBall() = default;

OutputMessage KickBall::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec KickBall state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  checkAndHandleTransitions(world);
  return makeKickBallOutput(world);
}

void KickBall::checkAndHandleTransitions(const World& world) { return; }

bool KickBall::shouldStayInKickBall(const World& world) const { return true; }

bool KickBall::shouldTransitionToAlign(const World& world) const { return true; }

bool KickBall::shouldTransitionToGoToBall(const World& world) const { return true; }

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
