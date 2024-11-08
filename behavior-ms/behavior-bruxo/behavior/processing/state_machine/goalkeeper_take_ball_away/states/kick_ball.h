#ifndef BEHAVIOR_STATE_MACHINE_KICK_BALL_H
#define BEHAVIOR_STATE_MACHINE_KICK_BALL_H

#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

namespace behavior {

class KickBall : public IState {
 protected:
  IStateMachine* state_machine_{}; // back reference

  // state parameters
  float approach_angle_threshold = 0.13 * 2;
  float distance_to_consider_kick = 250 * 1.2;

 public:
  explicit KickBall();

  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; };
  OutputMessage exec(const World& world) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_KICK_BALL_H
