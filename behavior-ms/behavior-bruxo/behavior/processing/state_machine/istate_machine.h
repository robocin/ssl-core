#ifndef BEHAVIOR_STATE_MACHINE_ISTATE_MACHINE_H
#define BEHAVIOR_STATE_MACHINE_ISTATE_MACHINE_H

#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"

namespace behavior {

class IState;

/**
 * @class IStateMachine
 * @brief An interface for state machine classes in the behavior service.
 *
 * The context class declares methods that all Concrete state machines should
 * implement and also provides a reference to state object, associated
 * with the State Machine.
 */
class IStateMachine {

 public:
  IStateMachine() = default;

  IStateMachine(const IStateMachine&) = delete;
  IStateMachine& operator=(const IStateMachine&) = delete;
  IStateMachine(IStateMachine&&) noexcept = default;
  IStateMachine& operator=(IStateMachine&&) noexcept = default;

  virtual ~IStateMachine() = default;

  virtual void transitionTo(IState* state) = 0;
  virtual void run(const World& world, RobotIdMessage& ally_id) = 0;
};

class IState {
 protected:
  IStateMachine* state_machine_{};

 public:
  IState() = default;

  IState(const IState&) = delete;
  IState& operator=(const IState&) = delete;
  IState(IState&&) noexcept = default;
  IState& operator=(IState&&) noexcept = default;

  virtual ~IState() = default;

  virtual void setStateMachine(IStateMachine* state_machine) = 0;
  virtual OutputMessage exec(const World& world, RobotIdMessage& ally_id) = 0;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_ISTATE_MACHINE_H
