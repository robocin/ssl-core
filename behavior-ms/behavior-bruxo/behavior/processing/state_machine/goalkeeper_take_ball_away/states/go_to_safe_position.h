#ifndef BEHAVIOR_STATE_MACHINE_GO_TO_SAFE_POSITION_H
#define BEHAVIOR_STATE_MACHINE_GO_TO_SAFE_POSITION_H

#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/kick_ball.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/output/log.h>

namespace behavior {

class GoToSafePosition : public IState {
 private:
  OutputMessage makeGoToSafePositionOutput(const World& world);
  RobotIdMessage makeGoToSafePositionRobotId(const World& world);
  MotionMessage makeGoToSafePositionMotion(const World& world);
  PlanningMessage makeGoToSafePositionPlanning(const World& world);

 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit GoToSafePosition();

  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; };
  OutputMessage exec(const World& world) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GO_TO_SAFE_POSITION_H
