#include "behavior/processing/state_machine/forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.h"

#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"

#include <stdio.h>

namespace behavior {

ForwardFollowAndKickBallStateMachine::ForwardFollowAndKickBallStateMachine() :
    current_state_(nullptr) {
  ForwardFollowAndKickBallStateMachine::transitionTo(new GoToBall);
};

void ForwardFollowAndKickBallStateMachine::transitionTo(IState* state) {
  if (current_state_ != nullptr) {
    delete current_state_;
  }

  current_state_ = state;
  current_state_->setStateMachine(this);
}

void ForwardFollowAndKickBallStateMachine::run(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("ForwardFollowAndKickBallStateMachine running!");
  ForwardFollowAndKickBallCommon::setKickTarget(world.field.allyGoalOutsideCenter());
  output = current_state_->exec(world, ally_id);
}
} // namespace behavior
