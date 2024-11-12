#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_ball_line.h"

#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_enemy_line.h"

namespace behavior {

FollowBallLine::FollowBallLine() = default;

OutputMessage FollowBallLine::exec(const World& world, RobotIdMessage ally_id) {
  robocin::ilog("Exec FollowBallLine state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  std::cout << " ball position in goalkeeper fsm: " << ball_position.x << " " << ball_position.y
            << std::endl;
  // Handle state transitions
  checkAndHandleTransitions(world);

  // Generate and return output
  return makeFollowBallLineOutput(world);
}

void FollowBallLine::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToDefendKick(world)) {
    state_machine_->transitionTo(new DefendKick);
    return;
  }

  if (shouldTransitionToFollowEnemyLine(world)) {
    state_machine_->transitionTo(new FollowEnemyLine);
    return;
  }
}

bool FollowBallLine::shouldTransitionToDefendKick(const World& world) const {
  bool is_ball_moving_to_our_goal = GoalkeeperGuardCommon::isBallMovingToOurGoal(world);
  bool is_ball_inside_goalkeeper_area = GoalkeeperGuardCommon::isBallInsideGoalkeeperArea(world);
  bool is_ball_going_to_pass_area_line = GoalkeeperGuardCommon::isBallGoingToPassAreaLine(world);

  return is_ball_moving_to_our_goal
         && (is_ball_inside_goalkeeper_area || is_ball_going_to_pass_area_line);
}

bool FollowBallLine::shouldTransitionToFollowEnemyLine(const World& world) const {
  return EnemyAnalyzer::enemyCanKick(
      world,
      GoalkeeperGuardCommon::DISTANCE_TO_CONSIDER_ENEMY_AS_CLOSE_TO_BALL,
      GoalkeeperGuardCommon::MAX_ENEMY_SPEED_ANGLE_TO_BALL_THRESHOLD);
}

robocin::Point2Df FollowBallLine::getMotionTarget(const World& world) const {
  return GoalkeeperGuardCommon::getMotionTarget(
      world,
      ally_id_.number.value(),
      GoalkeeperGuardCommon::getGoalkeeperBisectorVector(world),
      false);
}

float FollowBallLine::getMotionAngle(const World& world) const {
  return GoalkeeperGuardCommon::getMotionAngle(world,
                                               ally_id_.number.value(),
                                               getMotionTarget(world));
}

GoToPointMessage::MovingProfile FollowBallLine::getMotionMovingProfile(const World& world) const {
  if (GoalkeeperGuardCommon::isLateralMove(world,
                                           ally_id_.number.value(),
                                           getMotionTarget(world))) {
    return GoToPointMessage::MovingProfile::GoalkeeperInTopSpeed;
  }
  return GoToPointMessage::MovingProfile::BalancedInMedianSpeed;
}

OutputMessage FollowBallLine::makeFollowBallLineOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeFollowBallLineRobotId(world)},
                       MotionMessage{makeFollowBallLineMotion(world)},
                       PlanningMessage{makeFollowBallLinePlanning(world)}};
}

RobotIdMessage FollowBallLine::makeFollowBallLineRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage FollowBallLine::makeFollowBallLineMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point)};
}

PlanningMessage FollowBallLine::makeFollowBallLinePlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}

} // namespace behavior
