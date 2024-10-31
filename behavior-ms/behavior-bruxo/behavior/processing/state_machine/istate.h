#ifndef BEHAVIOR_STATE_MACHINE_ISTATE_H
#define BEHAVIOR_STATE_MACHINE_ISTATE_H

#include "behavior/processing/state_machine/context.h"

namespace decision {

class IContext;

/**
 * @class IState
 * @brief An interface for state classes in the behavior service.
 *
 * This base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. Context objects are by design Role classes.
 */
class IState {
 protected:
  IContext* context_{};

 public:
  IState() = default;

  IState(const IState&) = delete;
  IState& operator=(const IState&) = delete;
  IState(IState&&) noexcept = default;
  IState& operator=(IState&&) noexcept = default;

  virtual ~IState() = default;

  void setContext(IContext* context) { context_ = context; }

  virtual void run() = 0;
};

} // namespace decision

#endif // BEHAVIOR_STATE_MACHINE_ISTATE_H
