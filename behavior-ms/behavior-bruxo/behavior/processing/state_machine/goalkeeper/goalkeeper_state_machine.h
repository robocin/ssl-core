#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_STATE_MACHINE_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_STATE_MACHINE_H

#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

/**
 * @class GoalkeeperStateMachine
 * @brief A class that holds behaviors for the Goalkeeper role.
 */
namespace behavior {

class GoalkeeperStateMachine : IStateMachine {
 private:
  IState* current_state_;
  OutputMessage output;
  World world_;

 public:
  explicit GoalkeeperStateMachine();

  void transitionTo(IState* state) override;
  void run() override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_STATE_MACHINE_H
