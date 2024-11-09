#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/kick_ball.h"

#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"

#include <cstring>
#include <robocin/geometry/point2d.h>
#include <stdio.h>

namespace behavior {

KickBall::KickBall() = default;

OutputMessage KickBall::exec(const World& world) {
  robocin::ilog("Exec KickBall state");

  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  // TODO(mlv): get ally id
  const int ally_id = 0;

  bool is_ally_looking_to_target_and_ball
      = behavior::AllyAnalyzer::isAllyLookingToTargetAndBall(world,
                                                             0,
                                                             ball_position,
                                                             approach_angle_threshold);

  bool is_ball_in_range_to_kick
      = behavior::AllyAnalyzer::isBallInRangeToKick(world, 0, distance_to_consider_kick);

  if (!is_ally_looking_to_target_and_ball || !is_ball_in_range_to_kick) {
    state_machine_->transitionTo(new GoToBall);
  }

  return makeKickBallOutput(world);
}

OutputMessage KickBall::makeKickBallOutput(const World& world) {
  return OutputMessage{RobotIdMessage{KickBall::makeKickBallRobotId(world)},
                       MotionMessage{KickBall::makeKickBallMotion(world)},
                       PlanningMessage{KickBall::makeKickBallPlanning(world)}};
}

RobotIdMessage KickBall::makeKickBallRobotId(const World& world) {
  // TODO(ersaraujo): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage KickBall::makeKickBallMotion(const World& world) {
  // TODO(ersaraujo): Create the motion message
  return MotionMessage{};
}

PlanningMessage KickBall::makeKickBallPlanning(const World& world) {
  // TODO(ersaraujo): Create the planning message
  return PlanningMessage{};
}
} // namespace behavior
