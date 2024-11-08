#include "behavior/processing/state_machine/goalkeeper/goalkeeper_state_machine.h"

#include "behavior/processing/state_machine/goalkeeper/states/guard.h"

#include <stdio.h>

namespace behavior {

GoalkeeperStateMachine::GoalkeeperStateMachine() : current_state_(nullptr) {
  GoalkeeperStateMachine::transitionTo(new Guard);
};

void GoalkeeperStateMachine::transitionTo(IState* state) {
  if (current_state_ != nullptr) {
    delete current_state_;
  }

  current_state_ = state;
  current_state_->setStateMachine(this);
}

void GoalkeeperStateMachine::run() {
  robocin::ilog("GoalkeeperStateMachine running!");
  output = current_state_->exec(world_);
}
} // namespace behavior
