#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_TAKE_BALL_AWAY_STATE_MACHINE_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_TAKE_BALL_AWAY_STATE_MACHINE_H

#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

/**
 * @class GoalkeeperTakeBallAwayStateMachine
 * @brief A class that holds behaviors for the Goalkeeper to take the ball away.
 */
namespace behavior {

class GoalkeeperTakeBallAwayStateMachine : IStateMachine {
 private:
  IState* current_state_;
  OutputMessage output;
  World world_;

 public:
  explicit GoalkeeperTakeBallAwayStateMachine();

  void transitionTo(IState* state) override;
  void run() override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_TAKE_BALL_AWAY_STATE_MACHINE_H
