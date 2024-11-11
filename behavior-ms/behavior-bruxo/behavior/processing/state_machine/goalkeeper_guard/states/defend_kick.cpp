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
  return GoalkeeperCommon::riskOfCollideWithPosts(world, ally_id)
         || GoalkeeperCommon::robotBallTooClosePosts(world, ally_id);
}

bool DefendKick::shouldTransitionToFollowEnemyLine(const World& world) const {
  const int ally_id = 0;
  robocin::Point2Df target_position = GoalkeeperCommon::getKickTargetPosition(world);

  bool is_ally_looking_to_target_and_ball
      = AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                   ally_id,
                                                   target_position,
                                                   approach_angle_threshold_);

  bool is_ball_in_range_to_kick
      = AllyAnalyzer::isBallInRangeToKick(world, ally_id, distance_to_consider_kick_);

  return !is_ally_looking_to_target_and_ball || !is_ball_in_range_to_kick;
}

robocin::Point2Df DefendKick::getMotionTarget(const World& world) const {
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  return ball_position;
}

float DefendKick::getMotionAngle(const World& world) const {
  return (GoalkeeperCommon::getKickTargetPosition(world) - getMotionTarget(world)).angle();
}

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
