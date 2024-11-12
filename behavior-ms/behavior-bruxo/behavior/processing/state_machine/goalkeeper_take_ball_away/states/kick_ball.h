
#ifndef BEHAVIOR_STATE_MACHINE_KICK_BALL_H
#define BEHAVIOR_STATE_MACHINE_KICK_BALL_H

#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_ball.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/states/go_to_safe_position.h"
#include "behavior/processing/state_machine/istate_machine.h"

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
  [[nodiscard]] bool shouldTransitionToSafePosition(const World& world) const;
  [[nodiscard]] bool shouldTransitionToGoToBall(const World& world) const;

  // Utility methods
  [[nodiscard]] robocin::Point2Df getMotionTarget(const World& world) const;
  [[nodiscard]] float getMotionAngle(const World& world) const;

  // State parameters
  float approach_angle_threshold_ = GoalkeeperTakeBallAwayCommon::APPROACH_ANGLE_THRESHOLD * 2.0f;
  float distance_to_consider_kick_ = GoalkeeperTakeBallAwayCommon::DISTANCE_TO_CONSIDER_KICK * 1.2f;

  RobotIdMessage ally_id_;

 protected:
  IStateMachine* state_machine_{}; // back reference

 public:
  explicit KickBall();
  void setStateMachine(IStateMachine* state_machine) override { state_machine_ = state_machine; }
  OutputMessage exec(const World& world, RobotIdMessage ally_id) override;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_KICK_BALL_H
