#include "behavior/processing/state_machine/goalkeeper/states/other.h"

#include <stdio.h>

namespace behavior {

Other::Other() = default;

void Other::exec() { robocin::ilog("Exec other state"); }
} // namespace behavior