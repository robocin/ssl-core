#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"

#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_ball_line.h"

namespace behavior {

DefendKick::DefendKick() = default;

OutputMessage DefendKick::exec(const World& world) {
  robocin::ilog("Exec DefendKick state");

  checkAndHandleTransitions(world);
  return makeDefendKickOutput(world);
}

void DefendKick::checkAndHandleTransitions(const World& world) {
  if (shouldStayInDefendKick(world)) {
    return;
  }
  if (shouldTransitionToFollowEnemyLine(world)) {
    state_machine_->transitionTo(new FollowEnemyLine);
    return;
  }
  state_machine_->transitionTo(new FollowBallLine);
}

bool DefendKick::shouldStayInDefendKick(const World& world) const {
  bool is_ball_moving_to_our_goal = GoalkeeperGuardCommon::isBallMovingToOurGoal(world);
  bool is_ball_inside_goalkeeper_area = GoalkeeperGuardCommon::isBallInsideGoalkeeperArea(world);
  bool is_ball_going_to_pass_area_line = GoalkeeperGuardCommon::isBallGoingToPassAreaLine(world);

  return is_ball_moving_to_our_goal
         && (is_ball_inside_goalkeeper_area || is_ball_going_to_pass_area_line);
}

bool DefendKick::shouldTransitionToFollowEnemyLine(const World& world) const {
  return EnemyAnalyzer::enemyCanKick(
      world,
      GoalkeeperGuardCommon::DISTANCE_TO_CONSIDER_ENEMY_AS_CLOSE_TO_BALL,
      GoalkeeperGuardCommon::MAX_ENEMY_SPEED_ANGLE_TO_BALL_THRESHOLD);
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
