
#ifndef BEHAVIOR_STATE_MACHINE_KICK_BALL_H
#define BEHAVIOR_STATE_MACHINE_KICK_BALL_H

#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/analyzer/enemy_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/align.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/go_to_ball.h"
#include "behavior/processing/state_machine/istate_machine.h"
#include "common/robot_id/robot_id.h"

#include <robocin/geometry/point2d.h>
#include <robocin/output/log.h>

namespace behavior {

class KickBall : public IState {
 private:
  // Output generation
  OutputMessage makeKickBallOutput(const World& world);
  RobotIdMessage makeKickBallRobotId(const World& world);
  MotionMessage makeKickBallMotion(const World& world);
  PlanningMessage makeKickBallPlanning(const World& world);

  // Transition logic
  void checkAndHandleTransitions(const World& world);
  [[nodiscard]] bool shouldStayInKickBall(const World& world) const;
  [[nodiscard]] bool shouldTransitionToAlign(const World& world) const;
  [[nodiscard]] bool shouldTransitionToGoToBall(const World& world) const;

  // Utility methods
  [[nodiscard]] robocin::Point2Df getMotionTarget(const World& world) const;
  [[nodiscard]] float getMotionAngle(const World& world) const;
  [[nodiscard]] GoToPointMessage::MovingProfile getMotionMovingProfile(const World& world) const;

  RobotIdMessage ally_id_;

  // State parameters

 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit KickBall();
  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; }
  OutputMessage exec(const World& world, RobotIdMessage& ally_id) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_KICK_BALL_H
