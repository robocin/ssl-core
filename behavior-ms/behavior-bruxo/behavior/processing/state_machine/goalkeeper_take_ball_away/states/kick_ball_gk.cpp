#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/kick_ball_gk.h"

namespace behavior {

KickBallGK::KickBallGK() = default;

OutputMessage KickBallGK::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec KickBallGK state");
  ally_id_ = std::move(ally_id);

  checkAndHandleTransitions(world);
  return makeKickBallGKOutput(world);
}

void KickBallGK::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToSafePosition(world)) {
    state_machine_->transitionTo(new GoToSafePosition);
    return;
  }

  if (shouldTransitionToGoToBall(world)) {
    state_machine_->transitionTo(new GoToBallGK);
    return;
  }
}

bool KickBallGK::shouldTransitionToSafePosition(const World& world) const {
  return GoalkeeperTakeBallAwayCommon::riskOfCollideWithPosts(world, ally_id_.number.value())
         || GoalkeeperTakeBallAwayCommon::robotBallTooClosePosts(world, ally_id_.number.value());
}

bool KickBallGK::shouldTransitionToGoToBall(const World& world) const {
  robocin::Point2Df target_position = GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world);

  bool is_ally_looking_to_target_and_ball
      = AllyAnalyzer::isLookingToTargetAndBall(world,
                                               ally_id_.number.value(),
                                               target_position,
                                               approach_angle_threshold_);

  bool is_ball_in_range_to_kick = AllyAnalyzer::isBallInRangeToKick(world,
                                                                    ally_id_.number.value(),
                                                                    distance_to_consider_kick_);

  return !is_ally_looking_to_target_and_ball || !is_ball_in_range_to_kick;
}

robocin::Point2Df KickBallGK::getMotionTarget(const World& world) const {
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  return ball_position;
}

float KickBallGK::getMotionAngle(const World& world) const {
  return (GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world) - getMotionTarget(world))
      .angle();
}

OutputMessage KickBallGK::makeKickBallGKOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeKickBallGKRobotId(world)},
                       MotionMessage{makeKickBallGKMotion(world)},
                       PlanningMessage{makeKickBallGKPlanning(world)}};
}

RobotIdMessage KickBallGK::makeKickBallGKRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage KickBallGK::makeKickBallGKMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point
      = GoToPointMessage{getMotionTarget(world),
                         getMotionAngle(world),
                         GoToPointMessage::MovingProfile::DirectSafeKickBallSpeed};
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage KickBallGK::makeKickBallGKPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
