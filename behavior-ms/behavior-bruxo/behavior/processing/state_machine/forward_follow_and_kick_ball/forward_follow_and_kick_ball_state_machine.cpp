#include "behavior/processing/state_machine/forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.h"

#include "ally_analyzer.h"
#include "behavior/processing/analyzer/shooter_analyzer.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"
#include "perception/robot/robot_message.h"

#include <chrono>
#include <optional>
#include <robocin/detection_util/duration.h>
#include <robocin/geometry/point2d.h>
#include <stdio.h>

namespace behavior {

ForwardFollowAndKickBallStateMachine::ForwardFollowAndKickBallStateMachine() :
    current_state_(nullptr),
    target_kick_(std::nullopt) {
  ForwardFollowAndKickBallStateMachine::transitionTo(new GoToBall);
  timer_.start();
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
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  if (target_kick_.has_value()) {
    if (timer_.elapsed().ms() > 3000) {
      timer_.restart();
      target_kick_ = ShooterAnalyzer::findBestPlaceToKickOnGoal(world.field,
                                                                world.ball,
                                                                world.enemies,
                                                                ball_position,
                                                                true);
      ForwardFollowAndKickBallCommon::setKickTarget(target_kick_.value());
    }
  } else {
    target_kick_ = ShooterAnalyzer::findBestPlaceToKickOnGoal(world.field,
                                                              world.ball,
                                                              world.enemies,
                                                              ball_position,
                                                              /*consider_enemy_velocity=*/true);
    ForwardFollowAndKickBallCommon::setKickTarget(target_kick_.value());
  }
  output = current_state_->exec(world, ally_id);
}
} // namespace behavior
