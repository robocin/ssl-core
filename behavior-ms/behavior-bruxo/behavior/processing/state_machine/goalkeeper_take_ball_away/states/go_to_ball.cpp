#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

GoToBall::GoToBall() = default;

OutputMessage GoToBall::exec(const World& world) {
  robocin::ilog("Exec GoToBall state");

  bool is_ally_looking_to_target_and_ball
      = behavior::AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                             0,
                                                             robocin::Point2Df(0, 0),
                                                             approach_angle_threshold);

  bool is_ball_in_range_to_kick
      = behavior::AllyAnalyzer::isBallInRangeToKick(world, 0, distance_to_consider_kick);

  if (is_ally_looking_to_target_and_ball && is_ball_in_range_to_kick) {
    state_machine_->transitionTo(new KickBall);
  }

  return makeGoToBallOutput(world);
}

OutputMessage GoToBall::makeGoToBallOutput(const World& world) {
  return OutputMessage{RobotIdMessage{GoToBall::makeGoToBallRobotId(world)},
                       MotionMessage{GoToBall::makeGoToBallMotion(world)},
                       PlanningMessage{GoToBall::makeGoToBallPlanning(world)}};
}

RobotIdMessage GoToBall::makeGoToBallRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage GoToBall::makeGoToBallMotion(const World& world) {
  // TODO(mlv): Create the motion message
  return MotionMessage{};
}

PlanningMessage GoToBall::makeGoToBallPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
} // namespace behavior
