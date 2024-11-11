#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"

namespace behavior {

GoToSafePosition::GoToSafePosition() = default;

OutputMessage GoToSafePosition::exec(const World& world) {
  robocin::ilog("Exec GoToSafePosition state");

  checkAndHandleTransitions(world);
  return makeGoToSafePositionOutput(world);
}

void GoToSafePosition::checkAndHandleTransitions(const World& world) {
  if (shouldStayInSafePosition(world)) {
    return;
  }

  if (shouldTransitionToKickBall(world)) {
    state_machine_->transitionTo(new KickBall);
    return;
  }

  state_machine_->transitionTo(new GoToBall);
}

bool GoToSafePosition::shouldStayInSafePosition(const World& world) const {
  const int ally_id = 0;
  return GoalkeeperCommon::riskOfCollideWithPosts(world, ally_id)
         || GoalkeeperCommon::robotBallTooClosePosts(world, ally_id);
}

bool GoToSafePosition::shouldTransitionToKickBall(const World& world) const {
  const int ally_id = 0;
  robocin::Point2Df kick_target_position = GoalkeeperCommon::getKickTargetPosition(world);

  bool is_ally_looking_to_target_and_ball
      = AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                   ally_id,
                                                   kick_target_position,
                                                   approach_angle_threshold_);

  bool is_ball_in_range_to_kick
      = AllyAnalyzer::isBallInRangeToKick(world, ally_id, distance_to_consider_kick_);

  return is_ally_looking_to_target_and_ball && is_ball_in_range_to_kick;
}

robocin::Point2Df GoToSafePosition::getMotionTarget(const World& world) const {
  return GoalkeeperCommon::getSafePositionToAvoidPosts(world);
}

float GoToSafePosition::getMotionAngle(const World& world) const {
  const int ally_id = 0;
  std::optional<RobotMessage> ally = GoalkeeperCommon::getAlly(world, ally_id);

  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  return (ball_position - ally_position).angle();
}

OutputMessage GoToSafePosition::makeGoToSafePositionOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeGoToSafePositionRobotId(world)},
                       MotionMessage{makeGoToSafePositionMotion(world)},
                       PlanningMessage{makeGoToSafePositionPlanning(world)}};
}

RobotIdMessage GoToSafePosition::makeGoToSafePositionRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage GoToSafePosition::makeGoToSafePositionMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world), getMotionAngle(world)};
  return MotionMessage{std::move(go_to_point)};
}

PlanningMessage GoToSafePosition::makeGoToSafePositionPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}

} // namespace behavior
