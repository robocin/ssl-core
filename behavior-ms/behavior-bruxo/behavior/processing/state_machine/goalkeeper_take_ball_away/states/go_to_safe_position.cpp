#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

GoToSafePosition::GoToSafePosition() = default;

OutputMessage GoToSafePosition::exec(const World& world) {
  robocin::ilog("Exec GoToSafePosition state");
  state_machine_->transitionTo(new GoToBall);

  return makeGoToSafePositionOutput(world);
}

OutputMessage GoToSafePosition::makeGoToSafePositionOutput(const World& world) {
  return OutputMessage{RobotIdMessage{GoToSafePosition::makeGoToSafePositionRobotId(world)},
                       MotionMessage{GoToSafePosition::makeGoToSafePositionMotion(world)},
                       PlanningMessage{GoToSafePosition::makeGoToSafePositionPlanning(world)}};
}

RobotIdMessage GoToSafePosition::makeGoToSafePositionRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return RobotIdMessage{};
}

MotionMessage GoToSafePosition::makeGoToSafePositionMotion(const World& world) {
  // TODO(mlv): Create the motion message
  return MotionMessage{};
}

PlanningMessage GoToSafePosition::makeGoToSafePositionPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
} // namespace behavior
