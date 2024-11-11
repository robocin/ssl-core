#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"

namespace behavior {

DefendKick::DefendKick() = default;

OutputMessage DefendKick::exec(const World& world) {
  robocin::ilog("Exec DefendKick state");

  checkAndHandleTransitions(world);
  return makeDefendKickOutput(world);
}

void DefendKick::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToFollowBallLine(world)) {
    state_machine_->transitionTo(new FollowBallLine);
    return;
  }

  if (shouldTransitionToFollowEnemyLine(world)) {
    state_machine_->transitionTo(new FollowEnemyLine);
  }
}

bool DefendKick::shouldTransitionToFollowBallLine(const World& world) const {
  const int ally_id = 0;
  return true;
}

bool DefendKick::shouldTransitionToFollowEnemyLine(const World& world) const {
  const int ally_id = 0;
  return true;
}

robocin::Point2Df DefendKick::getMotionTarget(const World& world) const {
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  return ball_position;
}

float DefendKick::getMotionAngle(const World& world) const { return 0.0f; }

OutputMessage DefendKick::makeDefendKickOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeDefendKickRobotId(world)},
                       MotionMessage{makeDefendKickMotion(world)},
                       PlanningMessage{makeDefendKickPlanning(world)}};
}

RobotIdMessage DefendKick::makeDefendKickRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage DefendKick::makeDefendKickMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world), getMotionAngle(world)};
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage DefendKick::makeDefendKickPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
