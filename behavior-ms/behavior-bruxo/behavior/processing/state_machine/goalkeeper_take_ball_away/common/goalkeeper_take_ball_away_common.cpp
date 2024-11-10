#include "behavior/processing/state_machine/goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h"

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

bool GoalkeeperCommon::riskOfCollideWithPosts(const World& world, const int ally_id) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  bool is_ally_to_ball_crossing_bottom_post
      = mathematics::segmentsIntersect(ball_position,
                                       ally_position,
                                       world.field.allyGoalOutsideBottom(),
                                       world.field.allyGoalInsideBottom());

  bool is_ally_to_close_to_inside_bottom_post
      = world.field.allyGoalInsideBottom().distanceToSegment(ally_position, ball_position)
        < pRobotRadius() * 1.5;

  bool is_ally_to_close_to_outside_bottom_post
      = world.field.allyGoalOutsideBottom().distanceToSegment(ally_position, ball_position)
        < pRobotRadius() * 1.5;

  if (is_ally_to_ball_crossing_bottom_post || is_ally_to_close_to_inside_bottom_post
      || is_ally_to_close_to_outside_bottom_post) {
    return true;
  }

  bool is_ally_to_ball_crossing_upper_post
      = mathematics::segmentsIntersect(ball_position,
                                       ally_position,
                                       world.field.allyGoalOutsideTop(),
                                       world.field.allyGoalInsideTop());

  bool is_ally_to_close_to_inside_upper_post
      = world.field.allyGoalInsideTop().distanceToSegment(ally_position, ball_position)
        < pRobotRadius() * 1.5;

  bool is_ally_to_close_to_outside_upper_post
      = world.field.allyGoalOutsideTop().distanceToSegment(ally_position, ball_position)
        < pRobotRadius() * 1.5;

  if (is_ally_to_ball_crossing_upper_post || is_ally_to_close_to_inside_upper_post
      || is_ally_to_close_to_outside_upper_post) {
    return true;
  }

  bool is_ally_crossing_back_post
      = mathematics::segmentsIntersect(ball_position,
                                       ally_position,
                                       world.field.allyGoalInsideBottom(),
                                       world.field.allyGoalInsideTop());

  return is_ally_crossing_back_post;
}

bool GoalkeeperCommon::robotBallTooClosePosts(const World& world, int ally_id) {
  std::optional<RobotMessage> ally = getAlly(world, ally_id);
  auto&& field = world.field;
  if (!ally.has_value()) {
    return false;
  }
  robocin::Point2Df ally_position = ally->position.value();

  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};

  robocin::Point2Df safe_position_to_avoid_posts = getSafePositionToAvoidPosts(world);

  bool robotBallTooClosePosts
      = (std::abs(ball_position.y)
         > field.goal_width.value() / 2 + LOWER_POST_THRESHOLD_TO_CONSIDER_POST)
        && (std::abs(ball_position.y)
            < field.goal_width.value() / 2 + UPPER_POST_THRESHOLD_TO_CONSIDER_POST)
        && ally_position.distanceTo(ball_position) > pRobotRadius()
        && std::abs(ball_position.x) > std::abs(field.allyGoalOutsideCenter().x) - pRobotDiameter();

  return robotBallTooClosePosts;
}

robocin::Point2Df GoalkeeperCommon::getSafePositionToAvoidPosts(const World& world) {
  auto&& field = world.field;
  auto&& ball = world.ball;

  robocin::Point2Df ball_position = robocin::Point2Df{ball.position->x, ball.position->y};

  robocin::Point2Df safe_position = [&]() {
    bool is_ball_after_goal_post_y
        = std::abs(ball_position.y)
          > field.goal_width.value() / 2 + LOWER_POST_THRESHOLD_TO_CONSIDER_POST;
    if (ball_position.y > 0) {
      if (is_ball_after_goal_post_y) {
        return ball_position
               + (field.allyGoalOutsideTop() - field.allyGoalInsideCenter())
                         .resized(pRobotRadius() * 1.3)
                         .rotatedCounterClockWise90()
                     * field.attackDirection().x;
      }

      return ball_position
             - (field.allyGoalOutsideTop() - field.allyGoalInsideCenter())
                   .resized(pRobotRadius() * 1.3);
    }

    if (is_ball_after_goal_post_y) {
      return ball_position
             + (field.allyGoalOutsideBottom() - field.allyGoalInsideCenter())
                       .resized(pRobotRadius() * 1.3)
                       .rotatedClockWise90()
                   * field.attackDirection().x;
    }

    return ball_position
           - (field.allyGoalOutsideBottom() - field.allyGoalInsideCenter())
                 .resized(pRobotRadius() * 1.3);
  }();

  return safe_position;
}

} // namespace behavior
