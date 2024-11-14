#ifndef BEHAVIOR_PROCESSING_ANALYZER_SHOOTER_ANALYZER_H
#define BEHAVIOR_PROCESSING_ANALYZER_SHOOTER_ANALYZER_H

#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/field/field_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <behavior/parameters/parameters.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/angular.h>
#include <utility>
#include <vector>

namespace behavior {

class ShooterAnalyzer {
  std::vector<RobotMessage> setEnemies(const std::vector<RobotMessage>& robots) {
    std::vector<RobotMessage> enemies;
    for (const auto& robot : robots) {
      if (!(robot.robot_id->color == pAllyColor)) {
        enemies.emplace_back(RobotMessage{
            robot.confidence.value(),
            RobotIdMessage{robot.robot_id->color.value(), robot.robot_id->number.value()},
            robot.position.value(),
            robot.angle.value(),
            robot.velocity.value(),
            robot.angular_velocity.value(),
            robot.radius.value(),
            robot.height.value(),
            robot.dribbler_width.value(),
            std::nullopt /* Feedback */});
      }
    }

    return enemies;
  }

  inline float getAngularCoefficient(robocin::Point2Df sourcePoint,
                                     robocin::Point2Df destinationPoint) {
    float a;
    float angle = robocin::Point2Df{sourcePoint - destinationPoint}.angle();
    float eps = 0.001;

    if (std::abs(angle - M_PI_2) <= eps) {
      a = HUGE_VALF;
    } else {
      a = tan(angle);
    }
    return a;
  }

  robocin::Point2Df findBestPlaceToKickOnGoal(const FieldMessage& field,
                                              const BallMessage& ball,
                                              const std::vector<RobotMessage>& robots,
                                              robocin::Point2Df kick_start_position,
                                              bool consider_enemy_velocity) {
    auto enemies = setEnemies(robots);
    robocin::Point2Df decrease_goal_size_by = robocin::Point2Df(0, pRobotRadius() * 1.2);
    robocin::Point2Df upper_post = field.enemyGoalOutsideTop() - decrease_goal_size_by;
    robocin::Point2Df bottom_post = field.enemyGoalOutsideBottom() + decrease_goal_size_by;

    double ball_line_bottom_post_angle
        = robocin::Point2Df{kick_start_position - bottom_post}.angle();
    double ball_line_upper_post_angle = robocin::Point2Df{kick_start_position - upper_post}.angle();

    std::vector<std::pair<robocin::Point2Df, double>> obstacles_to_kick;

    // Upper and Bottom posts as enemies/obstacles in the shoot sector
    // Shoot Sector = Polygon composed of the Ball, Upper post and Bottom post
    obstacles_to_kick.emplace_back(upper_post, upper_post.y - bottom_post.y);
    obstacles_to_kick.emplace_back(bottom_post, 0);

    for (const auto& enemy : enemies) {
      robocin::Point2Df enemy_obstacle = enemy.position.value();

      if (consider_enemy_velocity) {
        double enemy_distance_to_ball = enemy.position.value().distanceTo(kick_start_position);
        double kick_time = (enemy_distance_to_ball / 1000) / pFrontKickStrenght();
        robocin::Point2Df enemy_velocity = enemy.velocity.value();

        enemy_obstacle += kick_time * enemy_velocity;
      }

      double ball_enemy_angle = robocin::Point2Df{kick_start_position - enemy_obstacle}.angle();

      // Check if enemy obstacle is in shoot sector
      robocin::Point2Df enemy_ball_vector = enemy_obstacle - kick_start_position;
      robocin::Point2Df vect = enemy_ball_vector.resized(2 * pRobotRadius());

      robocin::Point2Df enemy_obstacle_top = enemy_obstacle + vect.rotatedCounterClockWise90();
      robocin::Point2Df enemy_obstacle_bottom = enemy_obstacle + vect.rotatedClockWise90();

      // Enemy upper side
      if (enemy_obstacle_top.pointInPolygon({kick_start_position, upper_post, bottom_post})) {
        double enemy_perpendicular_distance_to_bottom_post
            = enemy_obstacle_top.distanceToSegment(kick_start_position, bottom_post);

        enemy_perpendicular_distance_to_bottom_post
            *= cos(robocin::smallestAngleDiff(ball_line_bottom_post_angle, ball_enemy_angle));

        obstacles_to_kick.emplace_back(enemy_obstacle, enemy_perpendicular_distance_to_bottom_post);
      }

      // Enemy bottom side
      if (enemy_obstacle_bottom.pointInPolygon({kick_start_position, upper_post, bottom_post})) {
        double enemy_perpendicular_distance_to_bottom_post
            = enemy_obstacle_bottom.distanceToSegment(kick_start_position, bottom_post);

        enemy_perpendicular_distance_to_bottom_post
            *= cos(robocin::smallestAngleDiff(ball_line_bottom_post_angle, ball_enemy_angle));

        obstacles_to_kick.emplace_back(enemy_obstacle, enemy_perpendicular_distance_to_bottom_post);
      }
    }

    // Ordering the obstacles by perpendicular distance to Bottom Post
    std::sort(obstacles_to_kick.begin(),
              obstacles_to_kick.end(),
              [](std::pair<robocin::Point2Df, double> first_sector,
                 std::pair<robocin::Point2Df, double> second_sector) {
                if (first_sector.second != second_sector.second) {
                  return first_sector.second > second_sector.second;
                }

                return false;
              });

    double best_sector_angle = -100000;
    robocin::Point2Df best_place_to_kick = field.enemyGoalOutsideCenter();
    int obstacles_count = obstacles_to_kick.size();

    if (shoot::ONLY_KICK_IN_GOAL_CENTER) {
      return best_place_to_kick;
    }

    // 2 obstacles = upper and bottom posts.
    bool have_enemy_ahead = obstacles_count != 2;
    for (int i = 0; i < obstacles_count - 1; i++) {
      std::pair<robocin::Point2Df, double> current_obstacle = obstacles_to_kick[i];
      std::pair<robocin::Point2Df, double> next_obstacle = obstacles_to_kick[i + 1];

      double ball_current_obstacle_angle
          = robocin::Point2Df{kick_start_position - current_obstacle.first}.angle();
      double ball_next_obstacle_angle
          = robocin::Point2Df{kick_start_position - next_obstacle.first}.angle();
      double angle_diff_between_obstacles = std::abs(
          robocin::smallestAngleDiff(ball_current_obstacle_angle, ball_next_obstacle_angle));

      if (angle_diff_between_obstacles > best_sector_angle) {
        best_sector_angle = angle_diff_between_obstacles;
        if (i == 0 && have_enemy_ahead) {
          best_place_to_kick = 0.75 * current_obstacle.first + 0.25 * next_obstacle.first;
        } else if (i + 1 == obstacles_count - 1 && have_enemy_ahead) {
          best_place_to_kick = 0.25 * current_obstacle.first + 0.75 * next_obstacle.first;
        } else {
          best_place_to_kick = 0.5 * current_obstacle.first + 0.5 * next_obstacle.first;
        }
      }
    }

    double m = (kick_start_position.x != best_place_to_kick.x) ?
                   (getAngularCoefficient(best_place_to_kick, kick_start_position)) :
                   kick_start_position.y - best_place_to_kick.y;
    double k = kick_start_position.y - (m * kick_start_position.x);
    double best_y_to_kick = m * upper_post.x + k;

    best_place_to_kick.x = upper_post.x;
    if (std::isnan(best_y_to_kick)) {
      best_place_to_kick.y = 0;
    } else {
      best_place_to_kick.y = best_y_to_kick;
    }
    double angle_diff_posts = std::abs(
        robocin::smallestAngleDiff(ball_line_bottom_post_angle, ball_line_upper_post_angle));

    // If don't have space enough between EnemyGK and the near post, then kick on opposite post
    if (angle_diff_posts < shoot::DONT_HAVE_ANGLE_TO_KICK_THRESHOLD
        && shoot::ALLOWED_KICK_ON_POST) {
      double distance_ball_to_goal_line_axis_x
          = abs(ball.position.value().x - field.enemyGoalOutsideCenter().x);
      double offset_out_ball_line = std::max<double>(
          shoot::HOW_MANY_DIAMETERS_DISCOUNT_OUT_GOAL_LINE_WHEN_KICK_ON_CORNER * pRobotRadius()
              - distance_ball_to_goal_line_axis_x,
          0);

      if (kick_start_position.y < 0) {
        if (distance_ball_to_goal_line_axis_x < shoot::MAX_DIFF_TO_CHANGE_TO_POST
            && std::abs(ball.position.value().y)
                   > shoot::MIN_Y_DISTANCE_TO_CHANGE_TO_KICK_TO_POST) {
          best_place_to_kick
              = field.enemyGoalOutsideTop() - field.attackDirection() * offset_out_ball_line;
        } else {
          best_place_to_kick = field.enemyGoalOutsideCenter();
        }

      } else {
        if (distance_ball_to_goal_line_axis_x < shoot::MAX_DIFF_TO_CHANGE_TO_POST
            && std::abs(ball.position.value().y)
                   > shoot::MIN_Y_DISTANCE_TO_CHANGE_TO_KICK_TO_POST) {
          best_place_to_kick
              = field.enemyGoalOutsideBottom() - field.attackDirection() * offset_out_ball_line;
        } else {
          best_place_to_kick = field.enemyGoalOutsideCenter();
        }
      }
    }

    return best_place_to_kick;
  }
};
} // namespace behavior

#endif // BEHAVIOR_PROCESSING_ANALYZER_SHOOTER_ANALYZER_H
