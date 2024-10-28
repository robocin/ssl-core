#ifndef DECISION_PROCESSING_MESSAGES_COMMON_GAME_EVENT_GAME_EVENT_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_COMMON_GAME_EVENT_GAME_EVENT_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id_message.h"

#include <cstdint>
#include <google/protobuf/duration.pb.h>
#include <google/protobuf/timestamp.pb.h>
#include <optional>
#include <robocin/geometry/point2d.h>
#include <string>
#include <vector>

namespace decision {

enum Team {
  TEAM_UNSPECIFIED = 0,
  TEAM_HOME = 1,
  TEAM_AWAY = 2,
};

class BallLeftFieldMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> left_field_position;
};

class BallLeftFieldBoundaryMessage {
 public:
  std::optional<Team> by_team;
  std::optional<robocin::Point2Df> left_field_boundary_position;
};

class AimlessKickMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> left_field_position;
  std::optional<robocin::Point2Df> kick_position;
};

class GoalkeeperHeldBallMessage {
 public:
  std::optional<Team> by_team;
  std::optional<robocin::Point2Df> ball_position;
  std::optional<uint32_t> duration; // todo(fnap): discuss what to use with duration
};

class RobotTooCloseToDefenseAreaMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> robot_position;
  std::optional<float> distance_to_defense_area;
  std::optional<robocin::Point2Df> ball_position;
};

class RobotInDefenseAreaMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> robot_position;
  std::optional<float> distance_to_nearest_point_outside_area;
};

class RobotPushedRobotMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> violator_robot;
  std::optional<RobotIdMessage> victim_robot;
  std::optional<robocin::Point2Df> position;
  std::optional<float> pushed_distance;
};

class RobotHeldBallDeliberatelyMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> ball_position;
  std::optional<uint32_t> duration; // todo(fnap): discuss what to use with duration
};

class RobotDribbledBallTooFarMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> start_position;
  std::optional<robocin::Point2Df> end_position;
};

class RobotTippedOverMessage {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> robot_position;
  std::optional<robocin::Point2Df> ball_position;
};

class GoalMessage {
 public:
  std::optional<Team> by_team;
  std::optional<Team> kicking_team;
  std::optional<RobotIdMessage> kicking_robot;
  std::optional<robocin::Point2Df> ball_position_when_scored;
  std::optional<robocin::Point2Df> kick_position;
  std::optional<float> max_ball_height;
  std::optional<uint32_t> num_of_robots_of_scoring_team;
  std::optional<google::protobuf::Timestamp> last_touch_by_scoring_team_timestamp;
  std::optional<std::string> message;
};

class GameEventMessage {
 public:
  std::vector<std::string> sources;
  std::optional<google::protobuf::Timestamp> timestamp;

  // Oneof event fields as separate optionals
  std::optional<BallLeftFieldMessage> ball_left_field;
  std::optional<BallLeftFieldBoundaryMessage> ball_left_field_boundary;
  std::optional<AimlessKickMessage> aimless_kick;
  std::optional<GoalkeeperHeldBallMessage> goalkeeper_held_ball;
  std::optional<RobotTooCloseToDefenseAreaMessage> robot_too_close_to_defense_area;
  std::optional<RobotInDefenseAreaMessage> robot_in_defense_area;
  std::optional<RobotPushedRobotMessage> robot_pushed_robot;
  std::optional<RobotHeldBallDeliberatelyMessage> robot_held_ball_deliberately;
  std::optional<RobotDribbledBallTooFarMessage> robot_dribbled_ball_too_far;
  std::optional<RobotTippedOverMessage> robot_tipped_over;
  std::optional<GoalMessage> goal;
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_GAME_EVENT_GAME_EVENT_MESSAGE_H
