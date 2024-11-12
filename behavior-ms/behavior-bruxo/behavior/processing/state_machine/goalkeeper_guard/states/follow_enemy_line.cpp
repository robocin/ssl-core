#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_enemy_line.h"

#include "behavior/processing/analyzer/enemy_analyzer.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"

#include <robocin/geometry/point2d.h>

namespace behavior {

FollowEnemyLine::FollowEnemyLine() = default;

OutputMessage FollowEnemyLine::exec(const World& world) {
  robocin::ilog("Exec FollowEnemyLine state");

  checkAndHandleTransitions(world);
  return makeFollowEnemyLineOutput(world);
}

void FollowEnemyLine::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToDefendKick(world)) {
    state_machine_->transitionTo(new DefendKick);
    return;
  }

  if (shouldStayInFollowEnemyLine(world)) {
    return;
  }

  state_machine_->transitionTo(new FollowBallLine);
}

bool FollowEnemyLine::shouldStayInFollowEnemyLine(const World& world) const {
  return EnemyAnalyzer::enemyCanKick(
      world,
      GoalkeeperGuardCommon::DISTANCE_TO_CONSIDER_ENEMY_AS_CLOSE_TO_BALL,
      GoalkeeperGuardCommon::MAX_ENEMY_SPEED_ANGLE_TO_BALL_THRESHOLD);
};

bool FollowEnemyLine::shouldTransitionToDefendKick(const World& world) const {
  bool is_ball_moving_to_our_goal = GoalkeeperGuardCommon::isBallMovingToOurGoal(world);
  bool is_ball_inside_goalkeeper_area = GoalkeeperGuardCommon::isBallInsideGoalkeeperArea(world);
  bool is_ball_going_to_pass_area_line = GoalkeeperGuardCommon::isBallGoingToPassAreaLine(world);

  return is_ball_moving_to_our_goal
         && (is_ball_inside_goalkeeper_area || is_ball_going_to_pass_area_line);
}

robocin::Point2Df FollowEnemyLine::getMotionTarget(const World& world) const {
  const int ally_id = 0;
  return GoalkeeperGuardCommon::getMotionTarget(
      world,
      ally_id,
      GoalkeeperGuardCommon::getEnemyToGoalDisplacedVector(world),
      true);
}

float FollowEnemyLine::getMotionAngle(const World& world) const {
  const int ally_id = 0;
  return GoalkeeperGuardCommon::getMotionAngle(world, ally_id, getMotionTarget(world));
}

GoToPointMessage::MovingProfile FollowEnemyLine::getMotionMovingProfile(const World& world) const {
  const int ally_id = 0;
  if (GoalkeeperGuardCommon::isLateralMove(world, ally_id, getMotionTarget(world))) {
    return GoToPointMessage::MovingProfile::GoalkeeperInTopSpeed;
  }
  return GoToPointMessage::MovingProfile::BalancedInMedianSpeed;
}

OutputMessage FollowEnemyLine::makeFollowEnemyLineOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeFollowEnemyLineRobotId(world)},
                       MotionMessage{makeFollowEnemyLineMotion(world)},
                       PlanningMessage{makeFollowEnemyLinePlanning(world)}};
}

RobotIdMessage FollowEnemyLine::makeFollowEnemyLineRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage FollowEnemyLine::makeFollowEnemyLineMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point)};
}

PlanningMessage FollowEnemyLine::makeFollowEnemyLinePlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}

} // namespace behavior
