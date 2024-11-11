#include "behavior/processing/state_machine/goalkeeper_guard/common/goalkeeper_guard_common.h"

namespace behavior {

std::optional<RobotMessage> GoalkeeperCommon::getAlly(const World& world, int id) {
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

bool GoalkeeperCommon::isBallInsideGoalkeeperArea(const World& world) {
  auto&& field = world.field;
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  return FieldAnalyzer::allyPenaltyAreaContains(ball_position, field);
}

bool GoalkeeperCommon::isBallGoingToPassAreaLine(const World& world) {
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

} // namespace behavior
