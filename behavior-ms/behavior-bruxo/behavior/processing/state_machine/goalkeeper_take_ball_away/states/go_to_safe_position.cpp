#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

GoToSafePosition::GoToSafePosition() = default;

OutputMessage GoToSafePosition::exec(const World& world) {
  robocin::ilog("Exec GoToSafePosition state");

  // TODO(mlv): get ally id and kick target position
  robocin::Point2Df target_position = world.field.enemyGoalInsideCenter();
  const int ally_id = 0;

  if (GoalkeeperCommon::riskOfCollideWithPosts(world, ally_id)
      || GoalkeeperCommon::robotBallTooClosePosts(world, ally_id)) {
    return makeGoToSafePositionOutput(world);
  }

  bool is_ally_looking_to_target_and_ball
      = behavior::AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                             ally_id,
                                                             target_position,
                                                             approach_angle_threshold);

  bool is_ball_in_range_to_kick
      = behavior::AllyAnalyzer::isBallInRangeToKick(world, ally_id, distance_to_consider_kick);

  if (is_ally_looking_to_target_and_ball && is_ball_in_range_to_kick) {
    state_machine_->transitionTo(new KickBall);
  }

  state_machine_->transitionTo(new GoToBall);
}

OutputMessage GoToSafePosition::makeGoToSafePositionOutput(const World& world) {
  return OutputMessage{RobotIdMessage{GoToSafePosition::makeGoToSafePositionRobotId(world)},
                       MotionMessage{GoToSafePosition::makeGoToSafePositionMotion(world)},
                       PlanningMessage{GoToSafePosition::makeGoToSafePositionPlanning(world)}};
}

RobotIdMessage GoToSafePosition::makeGoToSafePositionRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage GoToSafePosition::makeGoToSafePositionMotion(const World& world) {
  // TODO(mlv): Create the motion message
  return MotionMessage{};
}

PlanningMessage GoToSafePosition::makeGoToSafePositionPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
} // namespace behavior
