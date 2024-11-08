#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

GoToSafePosition::GoToSafePosition() = default;

OutputMessage GoToSafePosition::exec(const World& world) {
  robocin::ilog("Exec GoToSafePosition state");
  state_machine_->transitionTo(new GoToBall);

  return OutputMessage{};
}
} // namespace behavior
