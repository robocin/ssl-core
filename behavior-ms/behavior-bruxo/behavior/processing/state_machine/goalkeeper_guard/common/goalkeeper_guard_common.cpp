#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"

#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/analyzer/enemy_analyzer.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

std::optional<RobotMessage> GoalkeeperGuardCommon::getAlly(const World& world, int id) {
  for (const auto& ally : world.allies) {
    if (ally.robot_id.value().number == id) {
      return RobotMessage{
          ally.confidence.value(),
          RobotIdMessage{ally.robot_id->color.value(), ally.robot_id->number.value()},
          ally.position.value(),
          ally.angle.value(),
          ally.velocity.value(),
          ally.angular_velocity.value(),
          ally.radius.value(),
          ally.height.value(),
          ally.dribbler_width.value(),
          std::nullopt /* Feedback */};
    }
  }
  return std::nullopt;
}

bool GoalkeeperGuardCommon::isBallInsideGoalkeeperArea(const World& world) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  return FieldAnalyzer::allyPenaltyAreaContains(ball_position, field);
}

bool GoalkeeperGuardCommon::isBallGoingToPassAreaLine(const World& world) {
  auto&& field = world.field;
  auto&& ball = world.ball;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  std::vector<robocin::Point2Df> goalkeeper_area = {field.allyPenaltyAreaGoalCornerTop(),
                                                    field.allyPenaltyAreaCornerTop(),
                                                    field.allyPenaltyAreaCornerBottom(),
                                                    field.allyPenaltyAreaGoalCornerBottom()};

  robocin::Point2Df stop_ball_position = BallAnalyzer::getProjectedBallPosition(ball, 0);

  robocin::Line ball_to_estimated_ball = {ball_position, stop_ball_position};

  bool ball_is_going_to_pass_area_line = false;
  for (size_t i = 0; i < goalkeeper_area.size() - 1; i++) {
    robocin::Line area_line = {goalkeeper_area[i], goalkeeper_area[i + 1]};
    if (mathematics::segmentsIntersect(ball_to_estimated_ball, area_line)) {
      ball_is_going_to_pass_area_line = true;
      break;
    }
  }

  return ball_is_going_to_pass_area_line;
}

bool GoalkeeperGuardCommon::isBallMovingToOurGoal(const World& world) {
  return BallAnalyzer::isBallMovingToDefensiveGoal(world.field, world.ball);
}

robocin::Point2Df GoalkeeperGuardCommon::getGoalkeeperBisectorVector(const World& world) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  robocin::Point2Df ball_to_upper_post_vector = field.allyGoalOutsideTop() - ball_position;
  robocin::Point2Df ball_to_lower_post_vector = field.allyGoalOutsideBottom() - ball_position;
  robocin::Point2Df bisector_vector
      = ball_to_lower_post_vector.normalized() + ball_to_upper_post_vector.normalized();
  return bisector_vector;
}

float GoalkeeperGuardCommon::getGoalkeeperTargetY(const World& world,
                                                  robocin::Point2Df base_point,
                                                  float angular_coefficient,
                                                  float x_target) {
  float intercept_point_y = base_point.y - angular_coefficient * base_point.x;
  float goalkeeper_target_y = angular_coefficient * x_target + intercept_point_y;
  return goalkeeper_target_y;
}

std::vector<robocin::Point2Df>
GoalkeeperGuardCommon::getCircleLineIntersections(robocin::Point2Df ball_position,
                                                  robocin::Point2Df goalkeeper_target_position,
                                                  robocin::Point2Df goal_center,
                                                  float radius) {
  std::vector<robocin::Point2Df> intersections;
  static constexpr float EPS = 1e-12;

  robocin::Point2Df ball_to_goalkeeper_vector = goalkeeper_target_position - ball_position;
  robocin::Point2Df goal_center_to_ball_vector = ball_position - goal_center;

  float A = ball_to_goalkeeper_vector.dot(ball_to_goalkeeper_vector);
  float B = goal_center_to_ball_vector.dot(ball_to_goalkeeper_vector);
  float C = goal_center_to_ball_vector.dot(goal_center_to_ball_vector) - radius * radius;
  float D = B * B - A * C;

  if (D < -EPS) {
    return intersections;
  }
  intersections.push_back(goal_center + goal_center_to_ball_vector
                          + ball_to_goalkeeper_vector * (-B + std::sqrt(D + EPS)) / A);
  if (D > EPS) {
    intersections.push_back(goal_center + goal_center_to_ball_vector
                            + ball_to_goalkeeper_vector * (-B - std::sqrt(D)) / A);
  }

  return intersections;
}

float GoalkeeperGuardCommon::distanceFromBallToClosestAreaSegment(const World& world) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  std::vector<robocin::Point2Df> goalkeeper_area = {field.allyPenaltyAreaGoalCornerTop(),
                                                    field.allyPenaltyAreaCornerTop(),
                                                    field.allyPenaltyAreaCornerBottom(),
                                                    field.allyPenaltyAreaGoalCornerBottom()};

  float min_distance = std::numeric_limits<float>::max();
  for (size_t i = 0; i < goalkeeper_area.size() - 1; i++) {
    robocin::Line area_segment = {goalkeeper_area[i], goalkeeper_area[i + 1]};
    float distance = ball_position.distanceToSegment(area_segment.p1(), area_segment.p2());
    min_distance = std::min(min_distance, distance);
  }

  return min_distance;
}

bool GoalkeeperGuardCommon::isLateralMove(const World& world,
                                          int ally_id,
                                          robocin::Point2Df target_position) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  auto&& field = world.field;
  robocin::Point2Df ally_position = ally->position.value();

  float ally_to_target_point_dist_x = std::abs(ally_position.x - target_position.x);
  bool is_lateral_move = ally_to_target_point_dist_x < field.penalty_area_depth.value() * 0.25f;

  return is_lateral_move;
}

robocin::Point2Df GoalkeeperGuardCommon::getGoalkeeperTargetOnGoalLine(const World& world) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ball_velocity
      = robocin::Point2Df{world.ball.velocity->x, world.ball.velocity->y};

  float attack_direction = field.attackDirection().x;
  float defensive_goal_point_x = field.allyGoalOutsideCenter().x;
  float angular_coefficient = std::tan(ball_velocity.angle());

  float goalkeeper_target_x
      = defensive_goal_point_x + GoalkeeperGuardCommon::IN_LINE_OFFSET_X * attack_direction;
  float goalkeeper_target_y
      = getGoalkeeperTargetY(world, ball_position, angular_coefficient, goalkeeper_target_x);

  robocin::Point2Df goalkeeper_target_position = {goalkeeper_target_x, goalkeeper_target_y};

  return goalkeeper_target_position;
}

robocin::Point2Df GoalkeeperGuardCommon::projectGoalkeeperTargetOnArc(
    robocin::Point2Df ball_position,
    robocin::Point2Df goalkeeper_target_position_on_line,
    robocin::Point2Df goal_center,
    float radius) {
  std::vector<robocin::Point2Df> intersections
      = getCircleLineIntersections(ball_position,
                                   goalkeeper_target_position_on_line,
                                   goal_center,
                                   radius);
  if (intersections.empty()) {
    return goalkeeper_target_position_on_line;
  }
  if (intersections.size() == 1) {
    return intersections[0];
  }
  if (intersections.size() == 2) {
    if (intersections[0].y * ball_position.y < 0) {
      return intersections[1];
    }
    if (intersections[1].y * ball_position.y < 0) {
      return intersections[0];
    }
    if (std::abs(intersections[0].x) > std::abs(intersections[1].x)) {
      return intersections[1];
    }
  }
  return intersections[0];
}

robocin::Point2Df GoalkeeperGuardCommon::getAndProcessGoalkeeperTargetOnArc(
    const World& world,
    robocin::Point2Df goalkeeper_target_position_on_line,
    robocin::Point2Df goal_center,
    robocin::Point2Df aux_point) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  robocin::Point2Df defensive_goal_point = field.allyGoalOutsideCenter();

  float upper_post_point_y = field.allyGoalOutsideTop().y + GoalkeeperGuardCommon::IN_LINE_OFFSET_Y;
  float bottom_post_point_y
      = field.allyGoalOutsideBottom().y - GoalkeeperGuardCommon::IN_LINE_OFFSET_Y;

  bool is_ball_close_to_goal_line
      = (std::abs(ball_position.x) + GoalkeeperGuardCommon::IN_LINE_OFFSET_X - 10)
        > std::abs(defensive_goal_point.x);

  robocin::Point2Df goalkeeper_target_on_arc = [&]() {
    if (!is_ball_close_to_goal_line) {
      return projectGoalkeeperTargetOnArc(ball_position,
                                          goalkeeper_target_position_on_line,
                                          goal_center,
                                          goal_center.distanceTo(aux_point));
    }
    if (ball_position.y > 0) {
      return robocin::Point2Df{aux_point.x, upper_post_point_y};
    }
    return robocin::Point2Df{aux_point.x, bottom_post_point_y};
  }();

  return goalkeeper_target_on_arc;
}

robocin::Point2Df
GoalkeeperGuardCommon::getKickTargetOfEnemyRobot(const World& world,
                                                 const RobotMessage& closestEnemy) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df enemy_position = closestEnemy.position.value();

  float defensive_goal_point_x = field.allyGoalOutsideCenter().x;
  float upper_post_point
      = field.allyGoalOutsideTop().y - 2 * GoalkeeperGuardCommon::IN_LINE_OFFSET_Y;
  float bottom_post_point
      = field.allyGoalOutsideBottom().y + 2 * GoalkeeperGuardCommon::IN_LINE_OFFSET_Y;

  float attack_direction = field.attackDirection().x;
  robocin::Point2Df goal_center
      = {defensive_goal_point_x
             - attack_direction * GoalkeeperGuardCommon::GOALKEEPER_ARC_CURVE_THRESHOLD,
         0};
  float enemy_angular_coefficient = std::tan(closestEnemy.angle.value());

  float enemy_intercept_point_y = getGoalkeeperTargetY(world,
                                                       enemy_position,
                                                       enemy_angular_coefficient,
                                                       defensive_goal_point_x);
  enemy_intercept_point_y
      = std::clamp(enemy_intercept_point_y, bottom_post_point, upper_post_point);

  //          id = 0
  //        A ------- B
  //                  |
  //    GOAL          |  id = 1
  //                  |
  //                  |
  //        D ------- C
  //          id = 2
  int side_aux = attack_direction > 0 ? 1 : -1;
  float area_factor = 0.5f;
  float goal_width = field.goal_width.value();

  robocin::Point2Df A = {defensive_goal_point_x, goal_width};
  robocin::Point2Df B
      = {defensive_goal_point_x + (side_aux * goal_width * area_factor), goal_width};
  robocin::Point2Df C
      = {defensive_goal_point_x + (side_aux * goal_width * area_factor), -goal_width};
  robocin::Point2Df D = {defensive_goal_point_x, -goal_width};

  robocin::Point2Df enemy_intercept_point = {defensive_goal_point_x, enemy_intercept_point_y};

  if (mathematics::segmentsIntersect(A, B, ball_position, enemy_intercept_point)) {
    enemy_intercept_point_y = upper_post_point;
  } else if (mathematics::segmentsIntersect(C, D, ball_position, enemy_intercept_point)) {
    enemy_intercept_point_y = bottom_post_point;
  }

  enemy_intercept_point
      = {defensive_goal_point_x + (GoalkeeperGuardCommon::IN_LINE_OFFSET_X * attack_direction),
         enemy_intercept_point_y};
  robocin::Point2Df aux_point
      = {defensive_goal_point_x + (GoalkeeperGuardCommon::IN_LINE_OFFSET_X * attack_direction),
         goal_width / 2};

  return getAndProcessGoalkeeperTargetOnArc(world, enemy_intercept_point, goal_center, aux_point);
}

robocin::Point2Df GoalkeeperGuardCommon::getEnemyToGoalDisplacedVector(const World& world) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  // Check if has value has already been made in the condition to enter followEnemyLineOutput
  RobotMessage closest_enemy = EnemyAnalyzer::getClosestEnemyToBall(world).value();

  robocin::Point2Df enemy_kick_target_point = getKickTargetOfEnemyRobot(world, closest_enemy);
  robocin::Point2Df ball_to_enemy_kick_target_vector = enemy_kick_target_point - ball_position;

  float max_distance = (field.length.value() / 2) - field.penalty_area_depth.value();
  float ball_to_area_distance = distanceFromBallToClosestAreaSegment(world);
  ball_to_area_distance = std::clamp(ball_to_area_distance, 0.0f, max_distance);

  float goalkeeper_bisector_weight
      = mathematics::map(ball_to_area_distance, 0.0f, max_distance, 0.0f, 1.0f);
  float ball_to_enemy_line_weight = 1 - goalkeeper_bisector_weight;

  robocin::Point2Df enemy_to_goal_displaced_vector
      = ball_to_enemy_kick_target_vector.normalized() * ball_to_enemy_line_weight
        + getGoalkeeperBisectorVector(world).normalized() * goalkeeper_bisector_weight;

  return enemy_to_goal_displaced_vector;
}

robocin::Point2Df
GoalkeeperGuardCommon::getMotionTarget(const World& world,
                                       const int ally_id,
                                       robocin::Point2Df ball_to_goalkeeper_target_vector,
                                       bool is_in_follow_enemy_line) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ball_velocity
      = robocin::Point2Df{world.ball.velocity->x, world.ball.velocity->y};

  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return field.allyGoalOutsideCenter();
  }
  robocin::Point2Df ally_position = ally->position.value();

  float attack_direction = field.attackDirection().x;
  float exclusion_zone_radius = GoalkeeperGuardCommon::IN_LINE_OFFSET_X * attack_direction;

  robocin::Point2Df guard_line_upper_point
      = field.allyGoalOutsideTop()
        + robocin::Point2Df{exclusion_zone_radius, GoalkeeperGuardCommon::IN_LINE_OFFSET_Y};

  robocin::Point2Df guard_line_bottom_point
      = field.allyGoalOutsideBottom()
        + robocin::Point2Df{exclusion_zone_radius, -GoalkeeperGuardCommon::IN_LINE_OFFSET_Y};

  robocin::Line guard_line = {guard_line_bottom_point, guard_line_upper_point};

  float defensive_goal_x = field.allyGoalOutsideCenter().x;

  robocin::Point2Df goalkeeper_final_target_point = [&]() {
    robocin::Point2Df ball_to_goal_line_target_point
        = ball_position + ball_to_goalkeeper_target_vector.resized(10000);

    robocin::Line ball_to_goal_line_target_line = {ball_position, ball_to_goal_line_target_point};

    std::optional<robocin::Point2Df> goalkeeper_final_target_point
        = mathematics::segmentsIntersection(guard_line, ball_to_goal_line_target_line);

    if (!goalkeeper_final_target_point.has_value() && is_in_follow_enemy_line) {
      ball_to_goal_line_target_point
          = ball_position + getGoalkeeperBisectorVector(world).resized(10000);
      ball_to_goal_line_target_line = {ball_position, ball_to_goal_line_target_point};
      goalkeeper_final_target_point
          = mathematics::segmentsIntersection(guard_line, ball_to_goal_line_target_line);
    }

    if (!goalkeeper_final_target_point.has_value()) {
      robocin::Point2Df defensive_corner_upper = {defensive_goal_x, field.width.value()};
      robocin::Point2Df defensive_corner_bottom = {defensive_goal_x, -field.width.value()};
      robocin::Line defensive_line = {defensive_corner_bottom, defensive_corner_upper};

      goalkeeper_final_target_point
          = mathematics::segmentsIntersection(defensive_line, ball_to_goal_line_target_line);

      if (!goalkeeper_final_target_point.has_value()) {
        return field.allyGoalOutsideCenter();
      }

      return goalkeeper_final_target_point->y > 0 ? guard_line.p1() : guard_line.p2();
    }

    return goalkeeper_final_target_point.value();
  }();

  float goal_width = field.goal_width.value();

  robocin::Point2Df goal_center_with_offset = {
      defensive_goal_x - GoalkeeperGuardCommon::GOALKEEPER_ARC_CURVE_THRESHOLD * attack_direction,
      0};

  robocin::Point2Df aux_point = {goalkeeper_final_target_point.x, goal_width / 2};

  return getAndProcessGoalkeeperTargetOnArc(world,
                                            goalkeeper_final_target_point,
                                            goal_center_with_offset,
                                            aux_point);
}

float GoalkeeperGuardCommon::getMotionAngle(const World& world,
                                            int ally_id,
                                            robocin::Point2Df goalkeeper_target) {
  auto&& field = world.field;
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return 0.0f;
  }
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  robocin::Point2Df delta_vector = ball_position - goalkeeper_target;
  robocin::Point2Df attack_direction = field.attackDirection();
  float attack_direction_weight = GoalkeeperGuardCommon::WEIGHT_FOR_ATK_DIRECTION;
  float delta_weight = 1 - attack_direction_weight;

  float target_angle = (attack_direction.normalized() * attack_direction_weight
                        + delta_vector.normalized() * delta_weight)
                           .angle();

  robocin::Point2Df to_lower_vector = field.allyGoalInsideBottom() - field.allyGoalInsideTop();
  robocin::Point2Df to_high_vector = field.allyGoalInsideTop() - field.allyGoalInsideBottom();

  robocin::Point2Df delta_move_vector = goalkeeper_target - ally_position;
  robocin::Point2Df goalkeeper_target_to_ball_vector = ball_position - goalkeeper_target;

  if (delta_move_vector.length()
      > GoalkeeperGuardCommon::DISTANCE_FROM_TARGET_TO_ADJUST_MOVIMENT_DIRECTION) {
    bool will_robot_move_upwards
        = std::abs(mathematics::angleBetween(to_high_vector, delta_move_vector))
          < mathematics::degreesToRadians(45.0);
    bool will_robot_move_downwards
        = std::abs(mathematics::angleBetween(to_lower_vector, delta_move_vector))
          < mathematics::degreesToRadians(45.0);
    bool target_to_vector_is_upwards
        = std::abs(mathematics::angleBetween(to_high_vector, goalkeeper_target_to_ball_vector))
          < mathematics::degreesToRadians(90.0);
    bool target_to_vector_is_downwards
        = std::abs(mathematics::angleBetween(to_lower_vector, goalkeeper_target_to_ball_vector))
          < mathematics::degreesToRadians(80.0);

    bool should_move_upwards_looking_upwards
        = will_robot_move_upwards && target_to_vector_is_upwards;
    bool should_move_upwards_looking_downward
        = will_robot_move_upwards && target_to_vector_is_downwards;
    bool should_move_downwards_looking_upwards
        = will_robot_move_downwards && target_to_vector_is_upwards;
    bool should_move_downwards_looking_downwards
        = will_robot_move_downwards && target_to_vector_is_downwards;

    if (should_move_upwards_looking_downward || should_move_downwards_looking_downwards) {
      target_angle
          = ((attack_direction.x > 0) ?
                 to_lower_vector.rotatedCounterClockWise(mathematics::degreesToRadians(30.0))
                     .angle() :
                 to_lower_vector.rotatedClockWise(mathematics::degreesToRadians(30.0)).angle());
    } else if (should_move_upwards_looking_upwards || should_move_downwards_looking_upwards) {
      target_angle
          = ((attack_direction.x > 0) ?
                 to_high_vector.rotatedClockWise(mathematics::degreesToRadians(30.0)).angle() :
                 to_high_vector.rotatedCounterClockWise(mathematics::degreesToRadians(30.0))
                     .angle());
    }
  }

  return target_angle;
}

} // namespace behavior
