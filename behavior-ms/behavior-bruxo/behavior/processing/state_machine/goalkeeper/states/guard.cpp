#include "behavior/processing/state_machine/goalkeeper/states/guard.h"

#include <stdio.h>

namespace behavior {

Guard::Guard() = default;

void Guard::exec() { robocin::ilog("Exec guard state"); }
} // namespace behavior
