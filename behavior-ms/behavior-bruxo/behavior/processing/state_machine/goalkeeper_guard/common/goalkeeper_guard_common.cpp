#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"

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

float GoalkeeperGuardCommon::distance_from_ball_to_closest_area_segment(const World& world) {
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

} // namespace behavior
