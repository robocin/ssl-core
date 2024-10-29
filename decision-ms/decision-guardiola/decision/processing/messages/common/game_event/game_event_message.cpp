#include "decision/processing/messages/common/game_event/game_event_message.h"

#include <utility>

namespace decision {
GameEventMessage::GameEventMessage(
    std::vector<std::string> sources,
    std::optional<uint32_t> timestamp,
    std::optional<BallLeftFieldMessage> ball_left_field_touch_line,
    std::optional<BallLeftFieldMessage> ball_left_field_goal_line,
    std::optional<BallLeftFieldBoundaryMessage> ball_left_field_boundary,
    std::optional<AimlessKickMessage> aimless_kick,
    std::optional<GoalkeeperHeldBallMessage> goalkeeper_held_ball,
    std::optional<RobotTooCloseToDefenseAreaMessage> robot_too_close_to_defense_area,
    std::optional<RobotInDefenseAreaMessage> robot_in_defense_area,
    std::optional<RobotPushedRobotMessage> robot_pushed_robot,
    std::optional<RobotHeldBallDeliberatelyMessage> robot_held_ball_deliberately,
    std::optional<RobotDribbledBallTooFarMessage> robot_dribbled_ball_too_far,
    std::optional<RobotTippedOverMessage> robot_tipped_over,
    std::optional<GoalMessage> goal) :
    sources(std::move(sources)),
    timestamp(timestamp),
    ball_left_field_touch_line(std::move(ball_left_field_touch_line)),
    ball_left_field_goal_line(std::move(ball_left_field_goal_line)),
    ball_left_field_boundary(std::move(ball_left_field_boundary)),
    aimless_kick(std::move(aimless_kick)),
    goalkeeper_held_ball(std::move(goalkeeper_held_ball)),
    robot_too_close_to_defense_area(std::move(robot_too_close_to_defense_area)),
    robot_in_defense_area(std::move(robot_in_defense_area)),
    robot_pushed_robot(std::move(robot_pushed_robot)),
    robot_held_ball_deliberately(std::move(robot_held_ball_deliberately)),
    robot_dribbled_ball_too_far(std::move(robot_dribbled_ball_too_far)),
    robot_tipped_over(std::move(robot_tipped_over)),
    goal(std::move(goal)) {};

void GameEventMessage::fromProto(const protocols::common::GameEvent& goal_proto) {}

GameEventMessage::GameEventMessage(const protocols::common::GameEvent& game_event_proto) {
  timestamp = game_event_proto.timestamp().seconds();

  for (const auto& source : game_event_proto.sources()) {
    sources.emplace_back(source);
  }

  if (game_event_proto.has_ball_left_field_touch_line()) {
    if (!ball_left_field_touch_line.has_value()) {
      ball_left_field_touch_line.emplace();
    }

    ball_left_field_touch_line->fromProto(game_event_proto.ball_left_field_touch_line());
  }

  if (game_event_proto.has_ball_left_field_touch_line()) {
    if (!ball_left_field_touch_line.has_value()) {
      ball_left_field_touch_line.emplace();
    }
    ball_left_field_touch_line->fromProto(game_event_proto.ball_left_field_touch_line());
  }

  if (game_event_proto.has_ball_left_field_goal_line()) {
    if (!ball_left_field_goal_line.has_value()) {
      ball_left_field_goal_line.emplace();
    }
    ball_left_field_goal_line->fromProto(game_event_proto.ball_left_field_goal_line());
  }

  if (game_event_proto.has_ball_left_field_boundary()) {
    if (!ball_left_field_boundary.has_value()) {
      ball_left_field_boundary.emplace();
    }
    ball_left_field_boundary->fromProto(game_event_proto.ball_left_field_boundary());
  }

  if (game_event_proto.has_aimless_kick()) {
    if (!aimless_kick.has_value()) {
      aimless_kick.emplace();
    }
    aimless_kick->fromProto(game_event_proto.aimless_kick());
  }

  if (game_event_proto.has_goalkeeper_held_ball()) {
    if (!goalkeeper_held_ball.has_value()) {
      goalkeeper_held_ball.emplace();
    }
    goalkeeper_held_ball->fromProto(game_event_proto.goalkeeper_held_ball());
  }

  if (game_event_proto.has_robot_too_close_to_defense_area()) {
    if (!robot_too_close_to_defense_area.has_value()) {
      robot_too_close_to_defense_area.emplace();
    }
    robot_too_close_to_defense_area->fromProto(game_event_proto.robot_too_close_to_defense_area());
  }

  if (game_event_proto.has_robot_in_defense_area()) {
    if (!robot_in_defense_area.has_value()) {
      robot_in_defense_area.emplace();
    }
    robot_in_defense_area->fromProto(game_event_proto.robot_in_defense_area());
  }

  if (game_event_proto.has_robot_pushed_robot()) {
    if (!robot_pushed_robot.has_value()) {
      robot_pushed_robot.emplace();
    }
    robot_pushed_robot->fromProto(game_event_proto.robot_pushed_robot());
  }

  if (game_event_proto.has_robot_held_ball_deliberately()) {
    if (!robot_held_ball_deliberately.has_value()) {
      robot_held_ball_deliberately.emplace();
    }
    robot_held_ball_deliberately->fromProto(game_event_proto.robot_held_ball_deliberately());
  }

  if (game_event_proto.has_robot_dribbled_ball_too_far()) {
    if (!robot_dribbled_ball_too_far.has_value()) {
      robot_dribbled_ball_too_far.emplace();
    }
    robot_dribbled_ball_too_far->fromProto(game_event_proto.robot_dribbled_ball_too_far());
  }

  if (game_event_proto.has_robot_tipped_over()) {
    if (!robot_tipped_over.has_value()) {
      robot_tipped_over.emplace();
    }
    robot_tipped_over->fromProto(game_event_proto.robot_tipped_over());
  }

  if (game_event_proto.has_goal()) {
    if (!goal.has_value()) {
      goal.emplace();
    }
    goal->fromProto(game_event_proto.goal());
  }
};

} // namespace decision
