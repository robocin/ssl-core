#include "decision/processing/analyzer/ball_analyzer.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace decision {

bool BallAnalyzer::isBallStopped(BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() < 300;
}

bool BallAnalyzer::isBallMovingFast(BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > 850;
}

bool BallAnalyzer::isBallMoving(BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > 300;
}

bool BallAnalyzer::isBallMovingSlowly(BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > 300 && ball_velocity.length() < 850;
}

bool BallAnalyzer::isBallMovingWithVelocity(double min_velocity, BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > min_velocity;
}

bool BallAnalyzer::isBallMovingTowards(const robocin::Point2Df& target,
                                       BallMessage& ball,
                                       double max_angle_difference) {
  if (!isBallMoving(ball)) {
    return false;
  }

  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  robocin::Point2Df ball_to_target_vector_direction = (target - ball_position).normalized();

  double angle_difference
      = std::abs(ball_to_target_vector_direction.angleTo(ball_velocity.normalized()));
  return angle_difference < max_angle_difference;
}

bool BallAnalyzer::isBallMovingAway(const robocin::Point2Df& target, BallMessage& ball) {
  bool is_ball_moving_away_from_target = isBallMoving(ball) && !isBallMovingTowards(target, ball);
  return is_ball_moving_away_from_target;
}

bool BallAnalyzer::isBallMovingAwayWithVelocity(const robocin::Point2Df& target,
                                                double velocity,
                                                BallMessage& ball) {
  bool is_ball_moving_away_with_velocity
      = isBallMovingWithVelocity(velocity, ball) && !isBallMovingTowards(target, ball);
  return is_ball_moving_away_with_velocity;
}

bool BallAnalyzer::isBallMovingToOffensiveGoal(const FieldMessage& field, BallMessage& ball) {
  if (isBallStopped(ball)) {
    return false;
  }

  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  robocin::Point2Df offset_from_goal_center = robocin::Point2Df{0.0, *(field.width) / 2};

  bool moving_to_field_bottom_line
      = mathematics::segmentsIntersect(field.enemyGoalOutsideCenter() + offset_from_goal_center,
                                       field.enemyGoalOutsideCenter() - offset_from_goal_center,
                                       ball_position,
                                       ball_position + ball_velocity.resized(*(field.length)));
  return moving_to_field_bottom_line;
}

bool BallAnalyzer::isBallMovingToDefensiveGoal(const FieldMessage& field, BallMessage& ball) {
  if (isBallStopped(ball)) {
    return false;
  }

  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  float offset_y = (*field.penalty_area_width) * sqrt(2) / 2;
  robocin::Point2Df offset_from_goal_center = {0, offset_y};
  bool is_moving_to_defensive_goal
      = mathematics::segmentsIntersect(field.allyGoalOutsideCenter() + offset_from_goal_center,
                                       field.allyGoalOutsideCenter() - offset_from_goal_center,
                                       ball_position,
                                       ball_position + ball_velocity.resized(*(field.length)));
  return is_moving_to_defensive_goal;
}

bool BallAnalyzer::isBallMovingToEnemySide(const FieldMessage& field, BallMessage& ball) {
  if (isBallStopped(ball)) {
    return false;
  }

  bool is_moving_to_enemy_side = (ball.velocity->x * field.attackDirection().x) > 0;
  return is_moving_to_enemy_side;
}

} // namespace decision
