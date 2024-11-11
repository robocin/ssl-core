#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"
#include "behavior/processing/analyzer/field_analyzer.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class GoalkeeperCommon {
 public:
  // Common utility functions used across states
  static std::optional<RobotMessage> getAlly(const World& world, int id);
  static bool isBallInsideGoalkeeperArea(const World& world);
  static bool isBallGoingToPassAreaLine(const World& world);
  static bool isBallMovingToOurGoal(const World& world);

  // Constants
  static constexpr float APPROACH_ANGLE_THRESHOLD = 0.26f;


 private:

};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H
