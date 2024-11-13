#ifndef BEHAVIOR_STATE_MACHINE_FORWARD_FOLLOW_AND_KICK_BALL_COMMON_H
#define BEHAVIOR_STATE_MACHINE_FORWARD_FOLLOW_AND_KICK_BALL_COMMON_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ally_analyzer.h"
#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class ForwardFollowAndKickBallCommon {
 public:
  // Common utility functions used across states
  static std::optional<RobotMessage> getAlly(const World& world, int id);
  static void setKickTarget(robocin::Point2Df kick_target);
  static robocin::Point2Df getKickTarget();
  static bool isAllyBehindBall(const World& world, const int ally_id);
  static bool allyLostBall(const World& world, int ally_id);
  static bool isBallInsideEnemyArea(const World& world);
  static bool isAllyNotLookingToTargetAndBall(const World& world, const int ally_id);
  static bool isBallOnDribblerWithoutCheckingForAlignment(const World& world, const int ally_id);
  static bool isBallInRangeToKick(const World& world, const int ally_id);
  static bool isAllyLookingToTargetAndBall(const World& world, const int ally_id);

  // Constants
  static constexpr float APPROACH_ANGLE_THRESHOLD = 0.26f;
  static constexpr float ANGLE_FAR_TO_KICK_LINE = 1.3f;
  static constexpr float ANGLE_CLOSE_TO_KICK_LINE_UPPER = 0.42f;
  static constexpr float ANGLE_CLOSE_TO_KICK_LINE_LOWER = 0.32f;
  static constexpr float DISTANCE_TO_CONSIDER_IN_RANGE_TO_KICK_BALL = 320.0f;
  static constexpr float ANGLE_TO_DRIBBLER_SIDE = 20.55;
  static constexpr float DISTANCE_TO_CONSIDER_TOO_CLOSE_TO_BALL = 140.0f;

 private:
  static robocin::Point2Df kick_target_;
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_FORWARD_FOLLOW_AND_KICK_BALL_COMMON_H
