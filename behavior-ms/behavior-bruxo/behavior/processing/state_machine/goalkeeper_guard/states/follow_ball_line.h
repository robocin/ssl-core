#ifndef BEHAVIOR_STATE_MACHINE_FOLLOW_BALL_LINE_H
#define BEHAVIOR_STATE_MACHINE_FOLLOW_BALL_LINE_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/analyzer/enemy_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"
#include "behavior/processing/state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/defend_kick.h"
#include "behavior/processing/state_machine/goalkeeper_guard/states/follow_enemy_line.h"
#include "behavior/processing/state_machine/istate_machine.h"

#include <protocols/behavior/motion.pb.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class FollowBallLine : public IState {
 private:
  // Output generation
  OutputMessage makeFollowBallLineOutput(const World& world);
  RobotIdMessage makeFollowBallLineRobotId(const World& world);
  MotionMessage makeFollowBallLineMotion(const World& world);
  PlanningMessage makeFollowBallLinePlanning(const World& world);

  // Transition logic
  void checkAndHandleTransitions(const World& world);
  [[nodiscard]] bool shouldTransitionToDefendKick(const World& world) const;
  [[nodiscard]] bool shouldTransitionToFollowEnemyLine(const World& world) const;
  [[nodiscard]] robocin::Point2Df getMotionTarget(const World& world) const;
  [[nodiscard]] float getMotionAngle(const World& world) const;
  [[nodiscard]] GoToPointMessage::MovingProfile getMotionMovingProfile(const World& world) const;

  RobotIdMessage ally_id_;

  // state parameters

 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit FollowBallLine();
  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; }
  OutputMessage exec(const World& world, RobotIdMessage& ally_id) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_FOLLOW_BALL_LINE_H
