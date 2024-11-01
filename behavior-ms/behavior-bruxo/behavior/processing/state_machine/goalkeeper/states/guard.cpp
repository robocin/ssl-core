#include "behavior/processing/state_machine/goalkeeper/states/guard.h"

#include <cstring>
#include <stdio.h>

namespace behavior {

Guard::Guard() = default;

void Guard::exec() {
  robocin::ilog("Exec guard state");
  state_machine_->transitionTo(new Other);
}
} // namespace behavior
