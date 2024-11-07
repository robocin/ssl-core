#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/kick_ball.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

KickBall::KickBall() = default;

OutputMessage KickBall::exec() {
  robocin::ilog("Exec KickBall state");
  state_machine_->transitionTo(new GoToSafePosition);

  return OutputMessage{};
}
} // namespace behavior
