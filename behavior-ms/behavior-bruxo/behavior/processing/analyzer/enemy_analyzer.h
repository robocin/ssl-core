#ifndef BEHAVIOR_PROCESSING_ANALYZER_ENEMY_ANALYZER_H
#define BEHAVIOR_PROCESSING_ANALYZER_ENEMY_ANALYZER_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class EnemyAnalyzer {
 public:
  EnemyAnalyzer();
  static bool enemyCanKick(const World& world, float distance_threshold, float angle_threshold);

 private:
  static std::optional<RobotMessage> getClosestEnemyToBall(const World& world);
};

} // namespace behavior

#endif /* BEHAVIOR_PROCESSING_ANALYZER_ALLY_ANALYZER_H */
