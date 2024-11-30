#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class GoalkeeperTakeBallAwayCommon {
 public:
  // Common utility functions used across states
  static bool riskOfCollideWithPosts(const World& world, int ally_id);
  static bool robotBallTooClosePosts(const World& world, int ally_id);
  static std::optional<RobotMessage> getAlly(const World& world, int id);
  static robocin::Point2Df getSafePositionToAvoidPosts(const World& world);
  static robocin::Point2Df getKickTargetPosition(const World& world);

  // Constants
  static constexpr float APPROACH_ANGLE_THRESHOLD = 0.26f;
  static constexpr float DISTANCE_TO_CONSIDER_KICK = 300.0f;
  static constexpr float LOWER_POST_THRESHOLD_TO_CONSIDER_POST = 90.0f;
  static constexpr float UPPER_POST_THRESHOLD_TO_CONSIDER_POST = 190.0f;

 private:
  static bool robotMustKickToEnemyGoal(const World& world);
  static bool isBallCloseToAreaFront(const World& world);
  static bool isBallNearTheMiddleOfArea(const World& world);
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H
