#ifndef BEHAVIOR_STATE_MACHINE_GO_TO_BALL_H
#define BEHAVIOR_STATE_MACHINE_GO_TO_BALL_H

#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/kick_ball.h"
#include "behavior/processing/state_machine/istate_machine.h"

namespace behavior {

class GoToBall : public IState {
 private:
  // Output generation
  OutputMessage makeGoToBallOutput(const World& world);
  RobotIdMessage makeGoToBallRobotId(const World& world);
  MotionMessage makeGoToBallMotion(const World& world);
  PlanningMessage makeGoToBallPlanning(const World& world);

  // Transition logic
  void checkAndHandleTransitions(const World& world);
  [[nodiscard]] bool shouldTransitionToGoToSafePosition(const World& world) const;
  [[nodiscard]] bool shouldTransitionToKickBall(const World& world) const;

 protected:
  IStateMachine* state_machine_{}; // back reference

  // state parameters
  float approach_angle_threshold = 0.13f * 1.5f;
  float distance_to_consider_kick = 250.0f;

 public:
  explicit GoToBall();
  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; }
  OutputMessage exec(const World& world) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GO_TO_BALL_H
