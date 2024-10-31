#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_STATE_MACHINE_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_STATE_MACHINE_H

#include "behavior/processing/state_machine/goalkeeper/states/guard.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

/**
 * @class GoalkeeperStateMachine
 * @brief An class that holds behaviors for the Goalkeeper role.
 */
namespace behavior {

class GoalkeeperStateMachine : IStateMachine {
 private:
  IState* current_state_;
  Guard guard_state_;

 public:
  explicit GoalkeeperStateMachine();

  void transitionTo(IState* state) override { current_state_ = state; }
  void run() override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_STATE_MACHINE_H
