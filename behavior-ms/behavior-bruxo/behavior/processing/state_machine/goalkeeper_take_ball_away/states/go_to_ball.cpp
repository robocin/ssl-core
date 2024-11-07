#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

GoToBall::GoToBall() = default;

OutputMessage GoToBall::exec() {
  robocin::ilog("Exec GoToBall state");
  state_machine_->transitionTo(new KickBall);

  return OutputMessage{};
}
} // namespace behavior
