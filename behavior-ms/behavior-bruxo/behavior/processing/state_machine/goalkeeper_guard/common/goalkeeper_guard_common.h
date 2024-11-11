#ifndef BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H
#define BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/analyzer/field_analyzer.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <cctype>
#include <robocin/geometry/line.h>
#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

class GoalkeeperGuardCommon {
 public:
  // Common utility functions used across states
  static std::optional<RobotMessage> getAlly(const World& world, int id);
  static bool isBallInsideGoalkeeperArea(const World& world);
  static bool isBallGoingToPassAreaLine(const World& world);
  static bool isBallMovingToOurGoal(const World& world);
  static robocin::Point2Df getGoalkeeperBisectorVector(const World& world);
  static float getGoalkeeperTargetY(const World& world,
                                    robocin::Point2Df base_point,
                                    float angular_coefficient,
                                    float x_target);
  static std::vector<robocin::Point2Df>
  getCircleLineIntersections(robocin::Point2Df ball_position,
                             robocin::Point2Df goalkeeper_target_position,
                             robocin::Point2Df goal_center,
                             float radius);
  static float distanceFromBallToClosestAreaSegment(const World& world);
  static bool isLateralMove(const World& world, int ally_id, robocin::Point2Df target_position);
  static robocin::Point2Df getGoalkeeperTargetOnGoalLine(const World& world);
  static robocin::Point2Df
  projectGoalkeeperTargetOnArc(robocin::Point2Df ball_position,
                               robocin::Point2Df goalkeeper_target_position_on_line,
                               robocin::Point2Df goal_center,
                               float radius);
  static robocin::Point2Df
  getAndProcessGoalkeeperTargetOnArc(const World& world,
                                     robocin::Point2Df goalkeeper_target_position_on_line,
                                     robocin::Point2Df goal_center,
                                     robocin::Point2Df aux_point);
  static robocin::Point2Df getKickTargetOfEnemyRobot(const World& world,
                                                     const RobotMessage& closestEnemy);
  static robocin::Point2Df getEnemyToGoalDisplacedVector(const World& world);

  // Constants
  static constexpr float APPROACH_ANGLE_THRESHOLD = 0.26f;
  static constexpr float MAX_ENEMY_SPEED_ANGLE_TO_BALL_THRESHOLD = 0.3f;
  static constexpr float DISTANCE_TO_CONSIDER_ENEMY_AS_CLOSE_TO_BALL = 230.0f;
  static constexpr float IN_LINE_OFFSET_X = 140.0f;
  static constexpr float IN_LINE_OFFSET_Y = 10.0f;
  static constexpr float GOALKEEPER_ARC_CURVE_THRESHOLD = 1200.0f;

 private:
};

} // namespace behavior

#endif // BEHAVIOR_STATE_MACHINE_GOALKEEPER_COMMON_H
