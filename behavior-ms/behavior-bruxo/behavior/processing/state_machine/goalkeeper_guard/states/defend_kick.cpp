#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"

#include "behavior/parameters/parameters.h"
#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_ball_line.h"
#include "common/robot_id/robot_id.h"

#include <robocin/geometry/point2d.h>

namespace behavior {

DefendKick::DefendKick() = default;

OutputMessage DefendKick::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec DefendKick state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  std::cout << " ball position in goalkeeper fsm: " << ball_position.x << " " << ball_position.y
            << std::endl;
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
  robocin::Point2Df goalkeeper_target = GoalkeeperGuardCommon::getGoalkeeperTargetOnGoalLine(world);

  return GoalkeeperGuardCommon::getMotionTarget(world,
                                                ally_id_.number.value(),
                                                (goalkeeper_target - ball_position),
                                                false);
}

float DefendKick::getMotionAngle(const World& world) const {
  return GoalkeeperGuardCommon::getMotionAngle(world,
                                               ally_id_.number.value(),
                                               getMotionTarget(world));
}

KickCommandMessage DefendKick::makeKickCommandMessage(const World& world) {
  return KickCommandMessage{pChipKickStrenght(), false, true, false, false};
}

PeripheralActuationMessage DefendKick::makePeripheralActuation(const World& world) {
  return PeripheralActuationMessage{makeKickCommandMessage(world)};
}

GoToPointMessage::MovingProfile DefendKick::getMotionMovingProfile(const World& world) const {
  if (GoalkeeperGuardCommon::isLateralMove(world,
                                           ally_id_.number.value(),
                                           getMotionTarget(world))) {
    return GoToPointMessage::MovingProfile::GoalkeeperInTopSpeed;
  }
  return GoToPointMessage::MovingProfile::BalancedInMedianSpeed;
}

OutputMessage DefendKick::makeDefendKickOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeDefendKickRobotId(world)},
                       MotionMessage{makeDefendKickMotion(world)},
                       PlanningMessage{makeDefendKickPlanning(world)}};
}

RobotIdMessage DefendKick::makeDefendKickRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage DefendKick::makeDefendKickMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point),
                       std::nullopt,
                       std::nullopt,
                       std::nullopt,
                       makePeripheralActuation(world)};
};

PlanningMessage DefendKick::makeDefendKickPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
