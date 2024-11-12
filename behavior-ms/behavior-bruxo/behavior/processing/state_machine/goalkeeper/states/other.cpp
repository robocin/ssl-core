#include "behavior/processing/state_machine/goalkeeper/states/other.h"

#include <stdio.h>

namespace behavior {

Other::Other() = default;

OutputMessage Other::exec(const World& world, RobotIdMessage ally_id) {
  robocin::ilog("Exec other state and go back");
  state_machine_->transitionTo(new Guard);

  return OutputMessage{};
}
} // namespace behavior
