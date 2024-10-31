#include "behavior/processing/state_machine/goalkeeper/goalkeeper_state_machine.h"

#include <stdio.h>

namespace behavior {
GoalkeeperStateMachine::GoalkeeperStateMachine() : current_state_(&guard_state_) {
  current_state_->setStateMachine(this);
};

void GoalkeeperStateMachine::run() {
  robocin::ilog("GoalkeeperStateMachine running!");
  current_state_->exec();
}
} // namespace behavior
