#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"

#include "behavior/processing/state_machine/goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h"

namespace behavior {

GoToBall::GoToBall() = default;

OutputMessage GoToBall::exec(const World& world, RobotIdMessage ally_id) {
  robocin::ilog("Exec GoToBall state");
  ally_id_ = std::move(ally_id);

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
    return;
  }
}

bool GoToBall::shouldTransitionToGoToSafePosition(const World& world) const {
  // TODO(mlv): get ally id
  return GoalkeeperTakeBallAwayCommon::riskOfCollideWithPosts(world, ally_id_.number.value())
         || GoalkeeperTakeBallAwayCommon::robotBallTooClosePosts(world, ally_id_.number.value());
}

bool GoToBall::shouldTransitionToKickBall(const World& world) const {
  // TODO(mlv): get ally id and kick target position
  robocin::Point2Df kick_target_position
      = GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world);

  bool is_ally_looking_to_target_and_ball
      = AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                   ally_id_.number.value(),
                                                   kick_target_position,
                                                   approach_angle_threshold_);

  bool is_ball_in_range_to_kick = AllyAnalyzer::isBallInRangeToKick(world,
                                                                    ally_id_.number.value(),
                                                                    distance_to_consider_kick_);

  return is_ally_looking_to_target_and_ball && is_ball_in_range_to_kick;
}

bool GoToBall::isBallCloseToGoalLine(const World& world) const {
  auto&& field = world.field;
  std::optional<RobotMessage> ally
      = GoalkeeperTakeBallAwayCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return false;
  }

  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  float threshold = is_ball_close_to_goal_line_ ? pRobotRadius() * 0.25f : pRobotRadius() * 0.35f;

  bool is_goalkeeper_behind_ball
      = std::abs(ally_position.x) > std::abs(ball_position.x) + threshold;
  bool is_goalkeeper_close_to_ball = ally_position.distanceTo(ball_position) < 140.0f;
  bool is_ball_close_to_goal_line
      = ball_position.distanceToLine(field.allyGoalOutsideBottom(), field.allyGoalOutsideTop())
        <= pRobotRadius() * 1.3f;

  return is_ball_close_to_goal_line && is_goalkeeper_close_to_ball && is_goalkeeper_behind_ball;
}

robocin::Point2Df GoToBall::getMotionTarget(const World& world) const {
  std::optional<RobotMessage> ally
      = GoalkeeperTakeBallAwayCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return robocin::Point2Df{0, 0};
  }

  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  if (!isBallCloseToGoalLine(world)) {
    is_ball_close_to_goal_line_ = false;
    robocin::Point2Df kick_target_position
        = GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world);
    return ball_position
           + (ball_position - kick_target_position).resized(rotate_in_point_dist_threshold_);
  }
  is_ball_close_to_goal_line_ = true;
  return ball_position;
}

float GoToBall::getMotionAngle(const World& world) const {
  std::optional<RobotMessage> ally
      = GoalkeeperTakeBallAwayCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return 0.0f;
  }

  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df kick_target_position
      = GoalkeeperTakeBallAwayCommon::getKickTargetPosition(world);

  return (kick_target_position - ally_position).angle();
}

GoToPointMessage::MovingProfile GoToBall::getMotionMovingProfile(const World& world) const {
  std::optional<RobotMessage> ally
      = GoalkeeperTakeBallAwayCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return GoToPointMessage::MovingProfile::BalancedInDefaultSpeed;
  }

  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  return ally_position.distanceTo(ball_position) < pRobotDiameter() * 2.2f ?
             GoToPointMessage::MovingProfile::BalancedInSlowSpeed :
             GoToPointMessage::MovingProfile::BalancedInDefaultSpeed;
}

OutputMessage GoToBall::makeGoToBallOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeGoToBallRobotId(world)},
                       MotionMessage{makeGoToBallMotion(world)},
                       PlanningMessage{makeGoToBallPlanning(world)}};
}

RobotIdMessage GoToBall::makeGoToBallRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage GoToBall::makeGoToBallMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point)};
}

PlanningMessage GoToBall::makeGoToBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}

} // namespace behavior
