#ifndef BEHAVIOR_STATE_MACHINE_CONTEXT_H
#define BEHAVIOR_STATE_MACHINE_CONTEXT_H

#include "behavior/processing/state_machine/istate.h"

namespace decision {

class IState;

/**
 * @class IContext
 * @brief An interface for state machine classes in the behavior service.
 *
 * The context class declares methods that all Concrete state machines should
 * implement and also provides a reference to state object, associated
 * with the State Machine.
 */
class IContext {

 public:
  IContext() = default;

  IContext(const IContext&) = delete;
  IContext& operator=(const IContext&) = delete;
  IContext(IContext&&) noexcept = default;
  IContext& operator=(IContext&&) noexcept = default;

  virtual ~IContext() = default;

  virtual void transitionTo(IState* state) = 0;
};

} // namespace decision

#endif // BEHAVIOR_STATE_MACHINE_CONTEXT_H
