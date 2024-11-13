
#ifndef BEHAVIOR_STATE_MACHINE_DEFEND_KICK_H
#define BEHAVIOR_STATE_MACHINE_DEFEND_KICK_H

#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/analyzer/enemy_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"
#include "behavior/processing/state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_ball_line.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_enemy_line.h"
#include "behavior/processing/state_machine/istate_machine.h"
#include "common/robot_id/robot_id.h"

#include <robocin/geometry/point2d.h>
#include <robocin/output/log.h>

namespace behavior {

class DefendKick : public IState {
 private:
  // Output generation
  OutputMessage makeDefendKickOutput(const World& world);
  RobotIdMessage makeDefendKickRobotId(const World& world);
  MotionMessage makeDefendKickMotion(const World& world);
  PlanningMessage makeDefendKickPlanning(const World& world);

  // Transition logic
  void checkAndHandleTransitions(const World& world);
  [[nodiscard]] bool shouldStayInDefendKick(const World& world) const;
  [[nodiscard]] bool shouldTransitionToFollowEnemyLine(const World& world) const;

  // Utility methods
  [[nodiscard]] robocin::Point2Df getMotionTarget(const World& world) const;
  [[nodiscard]] float getMotionAngle(const World& world) const;
  [[nodiscard]] GoToPointMessage::MovingProfile getMotionMovingProfile(const World& world) const;

  RobotIdMessage ally_id_;

  // State parameters

 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit DefendKick();
  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; }
  OutputMessage exec(const World& world, RobotIdMessage& ally_id) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_DEFEND_KICK_H
