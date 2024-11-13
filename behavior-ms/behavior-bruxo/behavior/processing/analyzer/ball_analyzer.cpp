#include "behavior/processing/analyzer/ball_analyzer.h"

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/field_analyzer.h"
#include "perception/field/field_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

bool BallAnalyzer::isBallStopped(const BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() < pBallIsMovingVelocity();
}

bool BallAnalyzer::isBallMovingFast(const BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > pBallIsMovingFastVelocity();
}

bool BallAnalyzer::isBallMoving(const BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > pBallIsMovingVelocity();
}

bool BallAnalyzer::isBallMovingSlowly(const BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > pBallIsMovingVelocity()
         && ball_velocity.length() < pBallIsMovingFastVelocity();
}

bool BallAnalyzer::isBallMovingWithVelocity(double min_velocity, const BallMessage& ball) {
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};
  return ball_velocity.length() > min_velocity;
}

bool BallAnalyzer::isBallMovingTowards(const robocin::Point2Df& target,
                                       const BallMessage& ball,
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

bool BallAnalyzer::isBallMovingAway(const robocin::Point2Df& target, const BallMessage& ball) {
  bool is_ball_moving_away_from_target = isBallMoving(ball) && !isBallMovingTowards(target, ball);
  return is_ball_moving_away_from_target;
}

bool BallAnalyzer::isBallMovingAwayWithVelocity(const robocin::Point2Df& target,
                                                double velocity,
                                                const BallMessage& ball) {
  bool is_ball_moving_away_with_velocity
      = isBallMovingWithVelocity(velocity, ball) && !isBallMovingTowards(target, ball);
  return is_ball_moving_away_with_velocity;
}

bool BallAnalyzer::isBallMovingToOffensiveGoal(const FieldMessage& field, const BallMessage& ball) {
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

bool BallAnalyzer::isBallMovingToDefensiveGoal(const FieldMessage& field, const BallMessage& ball) {
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

bool BallAnalyzer::isBallMovingToEnemySide(const FieldMessage& field, const BallMessage& ball) {
  if (isBallStopped(ball)) {
    return false;
  }

  bool is_moving_to_enemy_side = (ball.velocity->x * field.attackDirection().x) > 0;
  return is_moving_to_enemy_side;
}

robocin::Point2Df BallAnalyzer::getProjectedBallPosition(const BallMessage& ball,
                                                         double target_speed) {
  // TODO(mlv): turn into parameter
  const float ball_deceleration = -328.0f;
  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};

  float ball_velocity_norm = ball_velocity.norm();

  float ball_displacement_until_reach_target_speed
      = torricelli(target_speed, ball_velocity_norm, ball_deceleration);

  robocin::Point2Df result
      = ball_position + ball_velocity.resized(ball_displacement_until_reach_target_speed);

  return result;
}

float BallAnalyzer::torricelli(float v, float v0, float a) {
  return (v * v - v0 * v0) / (2.0f * a);
}

bool BallAnalyzer::isMovingToDefensiveGoal(const FieldMessage& field, const BallMessage& ball) {
  if (isBallStopped(ball)) {
    return false;
  }
  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};
  robocin::Point2Df ball_velocity = robocin::Point2Df{ball.velocity->x, ball.velocity->y};

  robocin::Point2Df offset_from_goal_center
      = {0, static_cast<float>(field.penalty_area_width.value() * std::sqrt(2) / 2)};
  bool is_ball_moving_to_defensive_goal
      = mathematics::segmentsIntersect(field.allyGoalOutsideCenter() + offset_from_goal_center,
                                       field.allyGoalInsideCenter() - offset_from_goal_center,
                                       ball_position,
                                       ball_position + ball_velocity.resized(field.length.value()));

  return is_ball_moving_to_defensive_goal;
}

bool BallAnalyzer::isBallInsideEnemyArea(const FieldMessage& field, const BallMessage& ball) {
  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};
  return FieldAnalyzer::enemyPenaltyAreaContains(ball_position, field);
}

} // namespace behavior
