#ifndef DECISION_PROCESSING_ANALYZER_BALL_ANALYZER_H
#define DECISION_PROCESSING_ANALYZER_BALL_ANALYZER_H

#include "decision/processing/messages/perception/ball/ball_message.h"
#include "decision/processing/messages/perception/field/field_message.h"

#include <robocin/geometry/point2d.h>

namespace decision {

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
};

} // namespace decision

#endif /* DECISION_PROCESSING_ANALYZER_BALL_ANALYZER_H */
