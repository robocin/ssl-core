#ifndef BEHAVIOR_STATE_MACHINE_FOLLOW_ENEMY_LINE_H
#define BEHAVIOR_STATE_MACHINE_FOLLOW_ENEMY_LINE_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/enemy_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_ball_line.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <robocin/geometry/point2d.h>
#include <robocin/output/log.h>

namespace behavior {

class FollowEnemyLine : public IState {
 private:
  // Output generation
  OutputMessage makeFollowEnemyLineOutput(const World& world);
  RobotIdMessage makeFollowEnemyLineRobotId(const World& world);
  MotionMessage makeFollowEnemyLineMotion(const World& world);
  PlanningMessage makeFollowEnemyLinePlanning(const World& world);

  // Transition logic
  void checkAndHandleTransitions(const World& world);
  [[nodiscard]] bool shouldStayInFollowEnemyLine(const World& world) const;
  [[nodiscard]] bool shouldTransitionToDefendKick(const World& world) const;

  // Utility methods
  [[nodiscard]] robocin::Point2Df getMotionTarget(const World& world) const;
  [[nodiscard]] float getMotionAngle(const World& world) const;

  // State parameters

 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit FollowEnemyLine();
  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; }
  OutputMessage exec(const World& world) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_FOLLOW_ENEMY_LINE_H
