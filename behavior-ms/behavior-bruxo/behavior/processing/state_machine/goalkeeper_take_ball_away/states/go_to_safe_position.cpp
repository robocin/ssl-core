#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"

#include "common/robot_id/robot_id.h"

namespace behavior {

GoToSafePosition::GoToSafePosition() = default;

OutputMessage GoToSafePosition::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec GoToSafePosition state");
  ally_id_ = std::move(ally_id);

  checkAndHandleTransitions(world);
  return makeGoToSafePositionOutput(world);
}

void GoToSafePosition::checkAndHandleTransitions(const World& world) {
  if (shouldStayInSafePosition(world)) {
    return;
  }

  if (shouldTransitionToKickBall(world)) {
    state_machine_->transitionTo(new KickBallGK);
    return;
  }

  state_machine_->transitionTo(new GoToBallGK);
}

KickCommandMessage GoToSafePosition::makeKickCommandMessage(const World& world) {
  return KickCommandMessage{pChipKickStrenght(), false, false, true, false};
}

PeripheralActuationMessage GoToSafePosition::makePeripheralActuation(const World& world) {
  return PeripheralActuationMessage{makeKickCommandMessage(world)};
}

bool GoToSafePosition::shouldStayInSafePosition(const World& world) const {
  return GoalkeeperTakeBallAwayCommon::riskOfCollideWithPosts(world, ally_id_.number.value())
         || GoalkeeperTakeBallAwayCommon::robotBallTooClosePosts(world, ally_id_.number.value());
}

bool GoToSafePosition::shouldTransitionToKickBall(const World& world) const {
  robocin::Point2Df kick_target_position
      = GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world);

  bool is_ally_looking_to_target_and_ball
      = AllyAnalyzer::isLookingToTargetAndBall(world,
                                               ally_id_.number.value(),
                                               kick_target_position,
                                               approach_angle_threshold_);

  bool is_ball_in_range_to_kick = AllyAnalyzer::isBallInRangeToKick(world,
                                                                    ally_id_.number.value(),
                                                                    distance_to_consider_kick_);

  return is_ally_looking_to_target_and_ball && is_ball_in_range_to_kick;
}

robocin::Point2Df GoToSafePosition::getMotionTarget(const World& world) const {
  return GoalkeeperTakeBallAwayCommon::getSafePositionToAvoidPosts(world);
}

float GoToSafePosition::getMotionAngle(const World& world) const {
  std::optional<RobotMessage> ally
      = GoalkeeperTakeBallAwayCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return 0.0f;
  }

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
  return std::move(ally_id_);
}

MotionMessage GoToSafePosition::makeGoToSafePositionMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world), getMotionAngle(world)};
  
  return MotionMessage{std::move(go_to_point),
                      std::nullopt,
                      std::nullopt,
                      std::nullopt, 
                      makePeripheralActuation(world)};
}

PlanningMessage GoToSafePosition::makeGoToSafePositionPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}

} // namespace behavior
