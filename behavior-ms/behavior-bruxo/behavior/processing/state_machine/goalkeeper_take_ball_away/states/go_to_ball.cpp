#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"

namespace behavior {

GoToBall::GoToBall() = default;

OutputMessage GoToBall::exec(const World& world) {
  robocin::ilog("Exec GoToBall state");

  // Handle state transitions
  checkAndHandleTransitions(world);

  // Generate and return output
  return makeGoToBallOutput(world);
}

void GoToBall::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToGoToSafePosition(world)) {
    state_machine_->transitionTo(new GoToSafePosition);
    return;
  }

  if (shouldTransitionToKickBall(world)) {
    state_machine_->transitionTo(new KickBall);
  }
}

bool GoToBall::shouldTransitionToGoToSafePosition(const World& world) const {
  // TODO(mlv): get ally id
  const int ally_id = 0;
  return GoalkeeperCommon::riskOfCollideWithPosts(world, ally_id)
         || GoalkeeperCommon::robotBallTooClosePosts(world, ally_id);
}

bool GoToBall::shouldTransitionToKickBall(const World& world) const {
  // TODO(mlv): get ally id and kick target position
  const int ally_id = 0;
  robocin::Point2Df target_position = world.field.enemyGoalInsideCenter();

  bool is_ally_looking_to_target_and_ball
      = behavior::AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                             ally_id,
                                                             target_position,
                                                             approach_angle_threshold);

  bool is_ball_in_range_to_kick
      = behavior::AllyAnalyzer::isBallInRangeToKick(world, ally_id, distance_to_consider_kick);

  return is_ally_looking_to_target_and_ball && is_ball_in_range_to_kick;
}

OutputMessage GoToBall::makeGoToBallOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeGoToBallRobotId(world)},
                       MotionMessage{makeGoToBallMotion(world)},
                       PlanningMessage{makeGoToBallPlanning(world)}};
}

RobotIdMessage GoToBall::makeGoToBallRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage GoToBall::makeGoToBallMotion(const World& world) {
  // TODO(mlv): Create the motion message
  return MotionMessage{};
}

PlanningMessage GoToBall::makeGoToBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}

} // namespace behavior
