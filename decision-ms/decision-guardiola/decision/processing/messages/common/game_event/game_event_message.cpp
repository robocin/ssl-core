#include "decision/processing/messages/common/game_event/game_event_message.h"

#include <utility>

namespace decision {
// BallLeftFieldMessage
protocols::common::GameEvent::BallLeftField BallLeftFieldMessage::toProto() const {
  return protocols::common::GameEvent::BallLeftField{};
};

void BallLeftFieldMessage::fromProto(
    const protocols::common::GameEvent::BallLeftField& ball_left_field_proto) {};

BallLeftFieldMessage::BallLeftFieldMessage(std::optional<Team> by_team,
                                           std::optional<RobotIdMessage> by_robot,
                                           std::optional<robocin::Point2Df> left_field_position) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    left_field_position(std::move(left_field_position)) {}

// BallLefFieldBoundaryMessage
protocols::common::GameEvent::BallLeftFieldBoundary BallLeftFieldBoundaryMessage::toProto() const {
  return protocols::common::GameEvent::BallLeftFieldBoundary{};
};

void BallLeftFieldBoundaryMessage::fromProto(
    const protocols::common::GameEvent::BallLeftFieldBoundary& ball_left_field_boundary_proto) {};

BallLeftFieldBoundaryMessage::BallLeftFieldBoundaryMessage(
    std::optional<Team> by_team,
    std::optional<robocin::Point2Df> left_field_boundary_position) :
    by_team(std::move(by_team)),
    left_field_boundary_position(std::move(left_field_boundary_position)) {}

// AimlessKickMessage
protocols::common::GameEvent::AimlessKick AimlessKickMessage::toProto() const {
  return protocols::common::GameEvent::AimlessKick{};
};

void AimlessKickMessage::fromProto(
    const protocols::common::GameEvent::AimlessKick& aimless_kick_proto) {};

AimlessKickMessage::AimlessKickMessage(std::optional<Team> by_team,
                                       std::optional<RobotIdMessage> by_robot,
                                       std::optional<robocin::Point2Df> left_field_position,
                                       std::optional<robocin::Point2Df> kick_position) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    left_field_position(std::move(left_field_position)),
    kick_position(std::move(kick_position)) {}

// GoalkeeperHeldBallMessage
protocols::common::GameEvent::GoalkeeperHeldBall GoalkeeperHeldBallMessage::toProto() const {
  return protocols::common::GameEvent::GoalkeeperHeldBall{};
};

void GoalkeeperHeldBallMessage::fromProto(
    const protocols::common::GameEvent::GoalkeeperHeldBall& goalkeeper_held_ball_proto) {};

GoalkeeperHeldBallMessage::GoalkeeperHeldBallMessage(std::optional<Team> by_team,
                                                     std::optional<robocin::Point2Df> ball_position,
                                                     std::optional<uint32_t> duration) :
    by_team(std::move(by_team)),
    ball_position(std::move(ball_position)),
    duration(std::move(duration)) {}

// RobotTooCloseToDefenseAreaMessage
protocols::common::GameEvent::RobotTooCloseToDefenseArea
RobotTooCloseToDefenseAreaMessage::toProto() const {
  return protocols::common::GameEvent::RobotTooCloseToDefenseArea{};
}

void RobotTooCloseToDefenseAreaMessage::fromProto(
    const protocols::common::GameEvent::RobotTooCloseToDefenseArea&
        robot_too_close_to_defense_area_proto) {};

RobotTooCloseToDefenseAreaMessage::RobotTooCloseToDefenseAreaMessage(
    std::optional<Team> by_team,
    std::optional<RobotIdMessage> by_robot,
    std::optional<robocin::Point2Df> robot_position,
    std::optional<float> distance_to_defense_area,
    std::optional<robocin::Point2Df> ball_position) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    robot_position(std::move(robot_position)),
    distance_to_defense_area(std::move(distance_to_defense_area)),
    ball_position(std::move(ball_position)) {}

// RobotInDefenseAreaMessage
protocols::common::GameEvent::RobotInDefenseArea RobotInDefenseAreaMessage::toProto() const {
  return protocols::common::GameEvent::RobotInDefenseArea{};
};

void RobotInDefenseAreaMessage::fromProto(
    const protocols::common::GameEvent::RobotInDefenseArea& robot_in_defense_area_proto) {};

RobotInDefenseAreaMessage::RobotInDefenseAreaMessage(
    std::optional<Team> by_team,
    std::optional<RobotIdMessage> by_robot,
    std::optional<robocin::Point2Df> robot_position,
    std::optional<float> distance_to_nearest_point_outside_area) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    robot_position(std::move(robot_position)),
    distance_to_nearest_point_outside_area(std::move(distance_to_nearest_point_outside_area)) {}

// RobotPushedRobotMessage
protocols::common::GameEvent::RobotPushedRobot RobotPushedRobotMessage::toProto() const {
  return protocols::common::GameEvent::RobotPushedRobot{};
};

void RobotPushedRobotMessage::fromProto(
    const protocols::common::GameEvent::RobotPushedRobot& robot_pushed_robot_proto) {};

RobotPushedRobotMessage::RobotPushedRobotMessage(std::optional<Team> by_team,
                                                 std::optional<RobotIdMessage> violator_robot,
                                                 std::optional<RobotIdMessage> victim_robot,
                                                 std::optional<robocin::Point2Df> position,
                                                 std::optional<float> pushed_distance) :
    by_team(std::move(by_team)),
    violator_robot(std::move(violator_robot)),
    victim_robot(std::move(victim_robot)),
    position(std::move(position)),
    pushed_distance(std::move(pushed_distance)) {}

// RobotHeldBallDeliberatelyMessage
protocols::common::GameEvent::RobotHeldBallDeliberately
RobotHeldBallDeliberatelyMessage::toProto() const {
  return protocols::common::GameEvent::RobotHeldBallDeliberately{};
};

void RobotHeldBallDeliberatelyMessage::fromProto(
    const protocols::common::GameEvent::RobotHeldBallDeliberately&
        robot_held_ball_deliberately_proto) {};

RobotHeldBallDeliberatelyMessage::RobotHeldBallDeliberatelyMessage(
    std::optional<Team> by_team,
    std::optional<RobotIdMessage> by_robot,
    std::optional<robocin::Point2Df> ball_position,
    std::optional<uint32_t> duration) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    ball_position(std::move(ball_position)),
    duration(std::move(duration)) {}

// RobotDribbledBallTooFarMessage
protocols::common::GameEvent::RobotDribbledBallTooFar
RobotDribbledBallTooFarMessage::toProto() const {
  return protocols::common::GameEvent::RobotDribbledBallTooFar{};
};

void RobotDribbledBallTooFarMessage::fromProto(
    const protocols::common::GameEvent::RobotDribbledBallTooFar&
        robot_dribbled_ball_too_far_proto) {};

RobotDribbledBallTooFarMessage::RobotDribbledBallTooFarMessage(
    std::optional<Team> by_team,
    std::optional<RobotIdMessage> by_robot,
    std::optional<robocin::Point2Df> start_position,
    std::optional<robocin::Point2Df> end_position) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    start_position(std::move(start_position)),
    end_position(std::move(end_position)) {}

// RobotTippedOverMessage
protocols::common::GameEvent::RobotTippedOver RobotTippedOverMessage::toProto() const {
  return protocols::common::GameEvent::RobotTippedOver{};
};

void RobotTippedOverMessage::fromProto(
    const protocols::common::GameEvent::RobotTippedOver& robot_tipped_over_proto) {};

RobotTippedOverMessage::RobotTippedOverMessage(std::optional<Team> by_team,
                                               std::optional<RobotIdMessage> by_robot,
                                               std::optional<robocin::Point2Df> robot_position,
                                               std::optional<robocin::Point2Df> ball_position) :
    by_team(std::move(by_team)),
    by_robot(std::move(by_robot)),
    robot_position(std::move(robot_position)),
    ball_position(std::move(ball_position)) {}

// GoalMessage
protocols::common::GameEvent::Goal GoalMessage::toProto() const {
  return protocols::common::GameEvent::Goal{};
};

void GoalMessage::fromProto(const protocols::common::GameEvent::Goal& goal_proto) {};

GoalMessage::GoalMessage(std::optional<Team> by_team,
                         std::optional<Team> kicking_team,
                         std::optional<RobotIdMessage> kicking_robot,
                         std::optional<robocin::Point2Df> ball_position_when_scored,
                         std::optional<robocin::Point2Df> kick_position,
                         std::optional<float> max_ball_height,
                         std::optional<uint32_t> num_of_robots_of_scoring_team,
                         std::optional<uint32_t> last_touch_by_scoring_team_timestamp,
                         std::optional<std::string> message) :
    by_team(std::move(by_team)),
    kicking_team(std::move(kicking_team)),
    kicking_robot(std::move(kicking_robot)),
    ball_position_when_scored(std::move(ball_position_when_scored)),
    kick_position(std::move(kick_position)),
    max_ball_height(std::move(max_ball_height)),
    num_of_robots_of_scoring_team(std::move(num_of_robots_of_scoring_team)),
    last_touch_by_scoring_team_timestamp(std::move(last_touch_by_scoring_team_timestamp)),
    message(std::move(message)) {}

// GameEventMessage
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
