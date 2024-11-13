#ifndef BEHAVIOR_STATE_MACHINE_FORWARD_FOLLOW_AND_KICK_BALL_AWAY_STATE_MACHINE_H
#define BEHAVIOR_STATE_MACHINE_FORWARD_FOLLOW_AND_KICK_BALL_AWAY_STATE_MACHINE_H

#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/go_to_ball.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

/**
 * @class ForwardFollowAndKickBallStateMachine
 * @brief A class that holds behaviors for the Goalkeeper to take the ball away.
 */
namespace behavior {

class ForwardFollowAndKickBallStateMachine : IStateMachine {
 private:
  IState* current_state_;
  World world_;

 public:
  explicit ForwardFollowAndKickBallStateMachine();

  OutputMessage output;
  void transitionTo(IState* state) override;
  void run(const World& world, RobotIdMessage& ally_id) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_FORWARD_FOLLOW_AND_KICK_BALL_AWAY_STATE_MACHINE_H
