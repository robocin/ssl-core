#ifndef BEHAVIOR_PROCESSING_ANALYZER_BALL_ANALYZER_H
#define BEHAVIOR_PROCESSING_ANALYZER_BALL_ANALYZER_H

#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/field/field_message.h"

#include <robocin/geometry/point2d.h>

namespace behavior {

class BallAnalyzer {
 public:
  BallAnalyzer();

  static bool isBallStopped(BallMessage& ball);
  static bool isBallMovingFast(BallMessage& ball);
  static bool isBallMoving(BallMessage& ball);
  static bool isBallMovingSlowly(BallMessage& ball);
  static bool isBallMovingWithVelocity(double min_velocity, BallMessage& ball);
  static bool isBallMovingTowards(const robocin::Point2Df& target,
                                  BallMessage& ball,
                                  double max_angle_difference = 1.047);
  static bool isBallMovingAway(const robocin::Point2Df& target, BallMessage& ball);
  static bool
  isBallMovingAwayWithVelocity(const robocin::Point2Df& target, double velocity, BallMessage& ball);
  static bool isBallMovingToOffensiveGoal(const FieldMessage& field, BallMessage& ball);
  static bool isBallMovingToDefensiveGoal(const FieldMessage& field, BallMessage& ball);
  static bool isBallMovingToEnemySide(const FieldMessage& field, BallMessage& ball);
  static robocin::Point2Df getProjectedBallPosition(const BallMessage& ball, double target_speed);
  static bool isMovingToDefensiveGoal(const FieldMessage& field, BallMessage& ball);

 private:
  static float torricelli(float v, float v0, float a);
};

} // namespace behavior

#endif /* BEHAVIOR_PROCESSING_ANALYZER_BALL_ANALYZER_H */
