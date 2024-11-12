#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_GUARD_STATE_MACHINE_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_GUARD_STATE_MACHINE_H

#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

/**
 * @class GoalkeeperGuardStateMachine
 * @brief A class that holds behaviors for the Goalkeeper to defend the goal.
 */
namespace behavior {

class GoalkeeperGuardStateMachine : IStateMachine {
 private:
  IState* current_state_;
  World world_;

 public:
  explicit GoalkeeperGuardStateMachine();

  OutputMessage output;
  void transitionTo(IState* state) override;
  void run(RobotIdMessage ally_id) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_GUARD_STATE_MACHINE_H
