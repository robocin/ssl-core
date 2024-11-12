#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/kick_ball.h"

namespace behavior {

KickBall::KickBall() = default;

OutputMessage KickBall::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec KickBall state");
  ally_id_ = std::move(ally_id);

  checkAndHandleTransitions(world);
  return makeKickBallOutput(world);
}

void KickBall::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToSafePosition(world)) {
    state_machine_->transitionTo(new GoToSafePosition);
    return;
  }

  if (shouldTransitionToGoToBall(world)) {
    state_machine_->transitionTo(new GoToBall);
    return;
  }
}

bool KickBall::shouldTransitionToSafePosition(const World& world) const {
  return GoalkeeperTakeBallAwayCommon::riskOfCollideWithPosts(world, ally_id_.number.value())
         || GoalkeeperTakeBallAwayCommon::robotBallTooClosePosts(world, ally_id_.number.value());
}

bool KickBall::shouldTransitionToGoToBall(const World& world) const {
  robocin::Point2Df target_position = GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world);

  bool is_ally_looking_to_target_and_ball
      = AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                   ally_id_.number.value(),
                                                   target_position,
                                                   approach_angle_threshold_);

  bool is_ball_in_range_to_kick = AllyAnalyzer::isBallInRangeToKick(world,
                                                                    ally_id_.number.value(),
                                                                    distance_to_consider_kick_);

  return !is_ally_looking_to_target_and_ball || !is_ball_in_range_to_kick;
}

robocin::Point2Df KickBall::getMotionTarget(const World& world) const {
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  return ball_position;
}

float KickBall::getMotionAngle(const World& world) const {
  return (GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world) - getMotionTarget(world))
      .angle();
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
  GoToPointMessage go_to_point
      = GoToPointMessage{getMotionTarget(world),
                         getMotionAngle(world),
                         GoToPointMessage::MovingProfile::DirectSafeKickBallSpeed};
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage KickBall::makeKickBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
