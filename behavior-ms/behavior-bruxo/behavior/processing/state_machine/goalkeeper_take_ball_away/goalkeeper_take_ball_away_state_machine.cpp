#include "behavior/processing/state_machine/goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"

#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball_gk.h"

#include <stdio.h>

namespace behavior {

GoalkeeperTakeBallAwayStateMachine::GoalkeeperTakeBallAwayStateMachine() : current_state_(nullptr) {
  GoalkeeperTakeBallAwayStateMachine::transitionTo(new GoToBallGK);
};

void GoalkeeperTakeBallAwayStateMachine::transitionTo(IState* state) {
  if (current_state_ != nullptr) {
    delete current_state_;
  }

  current_state_ = state;
  current_state_->setStateMachine(this);
}

void GoalkeeperTakeBallAwayStateMachine::run(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("GoalkeeperTakeBallAwayStateMachine running!");
  output = current_state_->exec(world, ally_id);
}
} // namespace behavior
