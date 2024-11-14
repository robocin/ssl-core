#include "behavior/processing/analyzer/ally_analyzer.h"

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ball_analyzer.h"
#include "common/robot_id/robot_id.h"
#include "perception/robot/robot_message.h"

#include <robocin/geometry/line.h>
#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

std::optional<RobotMessage> AllyAnalyzer::getAlly(const World& world, int id) {
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

bool AllyAnalyzer::isLookingToTargetAndBall(const World& world,
                                            const int ally_id,
                                            const robocin::Point2Df& target_position,
                                            double angle_tolerance) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();
  float ally_angle = ally->angle.value();

  robocin::Point2Df ally_angle_vector = robocin::Point2Df::fromPolar(1, ally_angle);
  robocin::Point2Df ball_to_target_vector = target_position - ball_position;
  robocin::Point2Df ally_to_ball_vector = ball_position - ally_position;

  float angle_to_target
      = std::abs(mathematics::angleBetween(ball_to_target_vector, ally_to_ball_vector));
  float angle_to_ball
      = std::abs(mathematics::angleBetween(ball_to_target_vector, ally_angle_vector));

  return angle_to_target < angle_tolerance && angle_to_ball < angle_tolerance;
}

bool AllyAnalyzer::isBallInRangeToKick(const World& world,
                                       const int ally_id,
                                       float distance_threshold) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  // TODO(mlv): add ball moving away condition
  return !isTooFarFromBall(world, ally_id, distance_threshold);
}

bool AllyAnalyzer::isTooFarFromBall(const World& world,
                                    const int ally_id,
                                    float distance_threshold) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  return ball_position.distanceTo(ally_position) > distance_threshold;
}

bool AllyAnalyzer::isAllyBehindBall(const World& world,
                                    const int ally_id,
                                    robocin::Point2Df kick_target,
                                    float angle_threshold) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Point2Df ball_to_kick_target_vector = (kick_target - ball_position).normalized();
  robocin::Point2Df ally_to_ball_vector = (ball_position - ally_position).normalized();

  float angle = ball_to_kick_target_vector.angleTo(ally_to_ball_vector);

  return angle < angle_threshold;
}

bool AllyAnalyzer::isBallOnDribblerWithoutCheckingForAlignment(const World& world,
                                                               const int ally_id,
                                                               float angle_threshold,
                                                               float distance_threshold) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  bool is_ball_on_dribbler = std::abs(ally_position.angleTo(ball_position)) < angle_threshold;
  bool is_ball_close_to_ally = isCloseToBall(world, ally_id, distance_threshold);

  return is_ball_on_dribbler && is_ball_close_to_ally;
}

bool AllyAnalyzer::isCloseEnoughToBallToKick(const World& world, const int ally_id) {
  return isCloseToBall(world, ally_id, distanceThresholdForCloseToKick(world, ally_id));
}

bool AllyAnalyzer::isCloseToBall(const World& world, const int ally_id, float distance_threshold) {

  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  return ally_position.distanceTo(ball_position) < distance_threshold;
}

float AllyAnalyzer::distanceThresholdForCloseToKick(const World& world, const int ally_id) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  if (BallAnalyzer::isBallMovingAway(ally_position, world.ball)) {
    return pForwardDistToEnterKickBallWhenMovingAway();
  }

  float distance_threshold
      = pForwardMaxDistToMoveAroundBallWhenIsStoppedAndLookingToBallAndTarget();
  float multiply_factor = 1.1f;

  return distance_threshold * multiply_factor;
}

bool AllyAnalyzer::lostBall(const World& world, const int ally_id) {
  return !isCloseEnoughToBallToKick(world, ally_id);
}

float AllyAnalyzer::getBallCountourMargin(const World& world,
                                          int ally_id,
                                          robocin::Point2Df kick_target_position,
                                          float approach_angle_threshold,
                                          float max_angle_to_rotate) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Point2Df ally_front_position
      = ally_position + robocin::Point2Df::fromPolar(pRobotRadius(), ally->angle.value());

  robocin::Point2Df kick_target_to_ball_position_vector = ball_position - kick_target_position;
  robocin::Point2Df ball_position_to_ally_front_vector = ally_front_position - ball_position;

  bool is_robot_aligned_with_point_target_line
      = std::abs(kick_target_to_ball_position_vector.angleTo(ball_position_to_ally_front_vector))
        < approach_angle_threshold;

  if (is_robot_aligned_with_point_target_line) {
    return std::min(pRobotRadius() * 1.5f, ball_position.distanceTo(ally_front_position));
  }

  float angle_to_rotate
      = std::abs(ball_position_to_ally_front_vector.angleTo(kick_target_to_ball_position_vector));
  angle_to_rotate
      = std::clamp(angle_to_rotate, 0.0f, std::numbers::pi_v<float> - max_angle_to_rotate);

  float suplement_of_angle = std::numbers::pi_v<float> - angle_to_rotate;
  float big_axis_default = 420.0f;
  float small_axis = 210.0f;

  const int degree = 2;

  auto big_axis = [&](float angle) {
    if (std::abs(angle) > std::numbers::pi_v<float> / 2) {
      return big_axis_default * std::sin(angle);
    }
    return big_axis_default;
  };

  auto radius = [suplement_of_angle, big_axis, small_axis, degree]() {
    float first_term
        = std::pow(std::abs(std::cos(suplement_of_angle) / big_axis(suplement_of_angle)), degree);
    float second_term = std::pow(std::abs(std::sin(suplement_of_angle) / small_axis), degree);
    float result = std::pow(first_term + second_term, -1.0f / degree);
    return result;
  }();

  return radius;
}

robocin::Point2Df AllyAnalyzer::getPointContourVector(const World& world,
                                                      int ally_id,
                                                      robocin::Point2Df kick_target_position,
                                                      float max_angle_to_rotate) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return {0.0f, 0.0f};
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Point2Df ally_front_position
      = ally_position + robocin::Point2Df::fromPolar(pRobotRadius(), ally->angle.value());

  robocin::Point2Df kick_target_to_ball_position_vector = ball_position - kick_target_position;
  robocin::Point2Df ball_position_to_ally_front_vector = ally_front_position - ball_position;

  float angle_to_rotate
      = std::clamp(ball_position_to_ally_front_vector.angleTo(kick_target_to_ball_position_vector),
                   -max_angle_to_rotate,
                   max_angle_to_rotate);

  ball_position_to_ally_front_vector.rotateCounterClockWise(angle_to_rotate);

  return ball_position_to_ally_front_vector;
}

robocin::Point2Df
AllyAnalyzer::targetBehindBallLookingToTarget(const World& world,
                                              int ally_id,
                                              robocin::Point2Df kick_target_position,
                                              float angle_threshold) {
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  const float angle_to_clamp_vector = std::numbers::pi_v<float> / 3;
  float contour_margin = getBallCountourMargin(world,
                                               ally_id,
                                               kick_target_position,
                                               angle_threshold,
                                               angle_to_clamp_vector);
  robocin::Point2Df contour_vector
      = getPointContourVector(world, ally_id, kick_target_position, angle_to_clamp_vector);

  return ball_position + contour_vector.resized(contour_margin);
}

robocin::Point2Df
AllyAnalyzer::safeTargetPoint(const World& world, int ally_id, robocin::Point2Df target) {
  std::optional<RobotMessage> ally = AllyAnalyzer::getAlly(world, ally_id);
  if (!ally.has_value()) {
    return robocin::Point2Df{};
  }
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Line ally_to_target_line = {target, ally->position.value()};

  robocin::Line enemy_penalty_area_top_line
      = {world.field.enemyPenaltyAreaGoalCornerTop(), world.field.enemyPenaltyAreaCornerTop()};

  robocin::Line enemy_penalty_area_bottom_line = {world.field.enemyPenaltyAreaGoalCornerBottom(),
                                                  world.field.enemyPenaltyAreaCornerBottom()};

  robocin::Line ally_penalty_area_top_line
      = {world.field.allyPenaltyAreaGoalCornerTop(), world.field.allyPenaltyAreaCornerTop()};

  robocin::Line ally_penalty_area_bottom_line
      = {world.field.allyPenaltyAreaGoalCornerBottom(), world.field.allyPenaltyAreaCornerBottom()};

  bool intersect_top_enemy
      = mathematics::segmentsIntersect(enemy_penalty_area_top_line, ally_to_target_line);
  bool intersect_bottom_enemy
      = mathematics::segmentsIntersect(enemy_penalty_area_bottom_line, ally_to_target_line);

  bool intersect_top_ally
      = mathematics::segmentsIntersect(ally_penalty_area_top_line, ally_to_target_line);
  bool intersect_bottom_ally
      = mathematics::segmentsIntersect(ally_penalty_area_bottom_line, ally_to_target_line);

  if (!(intersect_bottom_ally or intersect_bottom_enemy or intersect_top_ally
        or intersect_top_enemy)) {
    return target;
  }

  if (intersect_top_enemy or intersect_bottom_enemy) {
    robocin::Point2Df corner_point = ally_position.y < 0 ?
                                         world.field.enemyPenaltyAreaCornerBottom() :
                                         world.field.enemyPenaltyAreaCornerTop();

    robocin::Point2Df corner_target = [&]() {
      if (intersect_bottom_enemy && intersect_top_enemy) {
        return corner_point;
      }
      if (intersect_bottom_enemy) {
        return world.field.enemyPenaltyAreaCornerBottom();
      }
      if (intersect_top_enemy) {
        return world.field.enemyPenaltyAreaCornerTop();
      }
      return target;
    }();

    return corner_target
           + (corner_target - world.field.enemyGoalOutsideCenter()).resized(pRobotDiameter() * 2);
  }

  if (intersect_top_ally or intersect_bottom_ally) {
    robocin::Point2Df corner_point = ally_position.y < 0 ?
                                         world.field.allyPenaltyAreaCornerBottom() :
                                         world.field.allyPenaltyAreaCornerTop();

    robocin::Point2Df corner_target = [&]() {
      if (intersect_bottom_ally && intersect_top_ally) {
        return corner_point;
      }
      if (intersect_bottom_ally) {
        return world.field.allyPenaltyAreaCornerBottom();
      }
      if (intersect_top_ally) {
        return world.field.allyPenaltyAreaCornerTop();
      }
      return target;
    }();

    return corner_target
           + (corner_target - world.field.allyGoalOutsideCenter()).resized(pRobotDiameter() * 2);
  }

  return target;
}

} // namespace behavior
