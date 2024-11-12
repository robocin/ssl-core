#include "behavior/processing/state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"

#include <stdio.h>

namespace behavior {

GoalkeeperGuardStateMachine::GoalkeeperGuardStateMachine() : current_state_(nullptr) {
  GoalkeeperGuardStateMachine::transitionTo(new DefendKick);
};

void GoalkeeperGuardStateMachine::transitionTo(IState* state) {
  if (current_state_ != nullptr) {
    delete current_state_;
  }

  current_state_ = state;
  current_state_->setStateMachine(this);
}

void GoalkeeperGuardStateMachine::run(RobotIdMessage ally_id) {
  robocin::ilog("GoalkeeperGuardStateMachine running!");
  output = current_state_->exec(world_, std::move(ally_id));
}
} // namespace behavior
