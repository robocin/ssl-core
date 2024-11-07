#include "behavior/processing/analyzer/ally_analyzer.h"

#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

namespace behavior {

std::optional<RobotMessage> AllyAnalyzer::getAlly(const World& world, int id) {
  for (const auto& ally : world.allies) {
    if (ally.robot_id.value().number == id) {
      return ally;
    }
  }

  return std::nullopt;
}

bool AllyAnalyzer::isAllyLookingToTargetAndBall(const World& world,
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

} // namespace behavior
