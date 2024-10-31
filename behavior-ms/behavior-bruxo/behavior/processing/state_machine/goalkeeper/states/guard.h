#ifndef BEHAVIOR_STATE_MACHINE_ISTATE_H
#define BEHAVIOR_STATE_MACHINE_ISTATE_H

#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

namespace behavior {

class Guard : public IState {
 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit Guard();

  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; };
  void exec() override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_ISTATE_H
