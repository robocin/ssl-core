#include "behavior/processing/analyzer/enemy_analyzer.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

std::optional<RobotMessage> EnemyAnalyzer::getClosestEnemyToBall(const World& world) {
  float min_distance = std::numeric_limits<float>::max();
  std::optional<RobotMessage> closest_enemy = std::nullopt;

  for (const auto& enemy : world.enemies) {
    robocin::Point2Df ball_position
        = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
    robocin::Point2Df enemy_position = enemy.position.value();

    float distance = ball_position.distanceTo(enemy_position);
    if (distance < min_distance) {
      min_distance = distance;
      closest_enemy = RobotMessage{
          enemy.confidence.value(),
          RobotIdMessage{enemy.robot_id->color.value(), enemy.robot_id->number.value()},
          enemy.position.value(),
          enemy.angle.value(),
          enemy.velocity.value(),
          enemy.angular_velocity.value(),
          enemy.radius.value(),
          enemy.height.value(),
          enemy.dribbler_width.value(),
          std::nullopt /* Feedback */};
    }
  }

  return closest_enemy;
}

bool EnemyAnalyzer::enemyCanKick(const World& world,
                                 float distance_threshold,
                                 float angle_threshold) {
  std::optional<RobotMessage> closest_enemy = getClosestEnemyToBall(world);
  if (!closest_enemy.has_value()) {
    return false;
  }

  auto&& field = world.field;

  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df enemy_position = closest_enemy->position.value();
  float enemy_angle = closest_enemy->angle.value();

  float enemy_to_ball_distance = enemy_position.distanceTo(ball_position);
  float enemy_to_ball_angle = enemy_position.angleTo(ball_position);

  bool is_enemy_close_to_ball = enemy_to_ball_distance < distance_threshold;
  bool is_enemy_looking_to_ball = enemy_to_ball_angle < angle_threshold;

  robocin::Line ally_penalty_goal
      = {field.allyPenaltyAreaGoalCornerBottom(), field.allyPenaltyAreaGoalCornerTop()};

  robocin::Line enemy_angle_segment
      = {enemy_position, enemy_position + robocin::Point2Df::fromPolar(10000, enemy_angle)};

  bool is_enemy_looking_to_our_goal
      = mathematics::segmentsIntersect(ally_penalty_goal, enemy_angle_segment);

  return is_enemy_close_to_ball && is_enemy_looking_to_ball && is_enemy_looking_to_our_goal;
}

} // namespace behavior
