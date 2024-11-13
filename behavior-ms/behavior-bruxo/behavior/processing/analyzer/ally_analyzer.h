#ifndef BEHAVIOR_PROCESSING_ANALYZER_ALLY_ANALYZER_H
#define BEHAVIOR_PROCESSING_ANALYZER_ALLY_ANALYZER_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class AllyAnalyzer {
 public:
  AllyAnalyzer();

  static bool isLookingToTargetAndBall(const World& world,
                                       int ally_id,
                                       const robocin::Point2Df& target_position,
                                       double angle_tolerance);

  static bool isBallInRangeToKick(const World& world, int ally_id, float distance_threshold);

  static bool isTooFarFromBall(const World& world, int ally_id, float distance_threshold);

  static bool isAllyBehindBall(const World& world,
                               const int ally_id,
                               robocin::Point2Df kick_target,
                               float angle_threshold);

  static bool isBallOnDribblerWithoutCheckingForAlignment(const World& world,
                                                          const int ally_id,
                                                          float angle_threshold,
                                                          float distance_threshold);

  static bool isCloseEnoughToBallToKick(const World& world, const int ally_id);

  static bool lostBall(const World& world, int ally_id, float distance_threshold);

  static float distanceThresholdForCloseToKick(const World& world, int ally_id);

  static bool isCloseToBall(const World& world, int ally_id, float distance_threshold);

  static bool lostBall(const World& world, int ally_id);

 private:
  static std::optional<RobotMessage> getAlly(const World& world, int id);
};

} // namespace behavior

#endif /* BEHAVIOR_PROCESSING_ANALYZER_ALLY_ANALYZER_H */
