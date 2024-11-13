#include "behavior/processing/analyzer/ally_analyzer.h"

#include "behavior/processing/analyzer/ball_analyzer.h"

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
} // namespace behavior
