#ifndef DECISION_PROCESSING_MESSAGES_COMMON_GAME_EVENT_GAME_EVENT_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_COMMON_GAME_EVENT_GAME_EVENT_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id_message.h"

#include <cstdint>
#include <google/protobuf/duration.pb.h>
#include <google/protobuf/timestamp.pb.h>
#include <optional>
#include <protocols/common/game_event.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <robocin/geometry/point2d.h>
#include <string>
#include <sys/types.h>
#include <vector>

namespace decision {

enum Team {
  TEAM_UNSPECIFIED = 0,
  TEAM_HOME = 1,
  TEAM_AWAY = 2,
};

class BallLeftFieldMessage : public IProtoConvertible<protocols::common::GameEvent::BallLeftField> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> left_field_position;

  explicit BallLeftFieldMessage(std::optional<Team> by_team = std::nullopt,
                                std::optional<RobotIdMessage> by_robot = std::nullopt,
                                std::optional<robocin::Point2Df> left_field_position
                                = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::BallLeftField toProto() const override {
    return protocols::common::GameEvent::BallLeftField{};
  };

  void fromProto(const protocols::common::GameEvent::BallLeftField& ball_left_field_proto);
};

class BallLeftFieldBoundaryMessage
    : public IProtoConvertible<protocols::common::GameEvent::BallLeftFieldBoundary> {
 public:
  std::optional<Team> by_team;
  std::optional<robocin::Point2Df> left_field_boundary_position;

  explicit BallLeftFieldBoundaryMessage(
      std::optional<Team> by_team = std::nullopt,
      std::optional<robocin::Point2Df> left_field_boundary_position = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::BallLeftFieldBoundary toProto() const override {
    return protocols::common::GameEvent::BallLeftFieldBoundary{};
  };

  void fromProto(
      const protocols::common::GameEvent::BallLeftFieldBoundary& ball_left_field_boundary_proto);
};

class AimlessKickMessage : public IProtoConvertible<protocols::common::GameEvent::AimlessKick> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> left_field_position;
  std::optional<robocin::Point2Df> kick_position;

  explicit AimlessKickMessage(std::optional<Team> by_team = std::nullopt,
                              std::optional<RobotIdMessage> by_robot = std::nullopt,
                              std::optional<robocin::Point2Df> left_field_position = std::nullopt,
                              std::optional<robocin::Point2Df> kick_position = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::AimlessKick toProto() const override {
    return protocols::common::GameEvent::AimlessKick{};
  };

  void fromProto(const protocols::common::GameEvent::AimlessKick& aimless_kick_proto);
};

class GoalkeeperHeldBallMessage
    : public IProtoConvertible<protocols::common::GameEvent::GoalkeeperHeldBall> {
 public:
  std::optional<Team> by_team;
  std::optional<robocin::Point2Df> ball_position;
  std::optional<uint32_t> duration; // todo(fnap): discuss what to use with duration

  explicit GoalkeeperHeldBallMessage(std::optional<Team> by_team = std::nullopt,
                                     std::optional<robocin::Point2Df> ball_position = std::nullopt,
                                     std::optional<uint32_t> duration = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::GoalkeeperHeldBall toProto() const override {
    return protocols::common::GameEvent::GoalkeeperHeldBall{};
  };

  void
  fromProto(const protocols::common::GameEvent::GoalkeeperHeldBall& goalkeeper_held_ball_proto);
};

class RobotTooCloseToDefenseAreaMessage
    : public IProtoConvertible<protocols::common::GameEvent::RobotTooCloseToDefenseArea> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> robot_position;
  std::optional<float> distance_to_defense_area;
  std::optional<robocin::Point2Df> ball_position;

  explicit RobotTooCloseToDefenseAreaMessage(
      std::optional<Team> by_team = std::nullopt,
      std::optional<RobotIdMessage> by_robot = std::nullopt,
      std::optional<robocin::Point2Df> robot_position = std::nullopt,
      std::optional<float> distance_to_defense_area = std::nullopt,
      std::optional<robocin::Point2Df> ball_position = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::RobotTooCloseToDefenseArea toProto() const override {
    return protocols::common::GameEvent::RobotTooCloseToDefenseArea{};
  };

  void fromProto(const protocols::common::GameEvent::RobotTooCloseToDefenseArea&
                     robot_too_close_to_defense_area_proto);
};

class RobotInDefenseAreaMessage
    : public IProtoConvertible<protocols::common::GameEvent::RobotInDefenseArea> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> robot_position;
  std::optional<float> distance_to_nearest_point_outside_area;

  explicit RobotInDefenseAreaMessage(std::optional<Team> by_team,
                                     std::optional<RobotIdMessage> by_robot,
                                     std::optional<robocin::Point2Df> robot_position,
                                     std::optional<float> distance_to_nearest_point_outside_area);

  [[nodiscard]] protocols::common::GameEvent::RobotInDefenseArea toProto() const override {
    return protocols::common::GameEvent::RobotInDefenseArea{};
  };

  void
  fromProto(const protocols::common::GameEvent::RobotInDefenseArea& robot_in_defense_area_proto);
};

class RobotPushedRobotMessage
    : public IProtoConvertible<protocols::common::GameEvent::RobotPushedRobot> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> violator_robot;
  std::optional<RobotIdMessage> victim_robot;
  std::optional<robocin::Point2Df> position;
  std::optional<float> pushed_distance;

  explicit RobotPushedRobotMessage(std::optional<Team> by_team = std::nullopt,
                                   std::optional<RobotIdMessage> violator_robot = std::nullopt,
                                   std::optional<RobotIdMessage> victim_robot = std::nullopt,
                                   std::optional<robocin::Point2Df> position = std::nullopt,
                                   std::optional<float> pushed_distance = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::RobotPushedRobot toProto() const override {
    return protocols::common::GameEvent::RobotPushedRobot{};
  };

  void fromProto(const protocols::common::GameEvent::RobotPushedRobot& robot_pushed_robot_proto);
};

class RobotHeldBallDeliberatelyMessage
    : public IProtoConvertible<protocols::common::GameEvent::RobotHeldBallDeliberately> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> ball_position;
  std::optional<uint32_t> duration; // todo(fnap): discuss what to use with duration

  explicit RobotHeldBallDeliberatelyMessage(std::optional<Team> by_team = std::nullopt,
                                            std::optional<RobotIdMessage> by_robot = std::nullopt,
                                            std::optional<robocin::Point2Df> ball_position
                                            = std::nullopt,
                                            std::optional<uint32_t> duration = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::RobotHeldBallDeliberately toProto() const override {
    return protocols::common::GameEvent::RobotHeldBallDeliberately{};
  };

  void fromProto(const protocols::common::GameEvent::RobotHeldBallDeliberately&
                     robot_held_ball_deliberately_proto);
};

class RobotDribbledBallTooFarMessage
    : public IProtoConvertible<protocols::common::GameEvent::RobotDribbledBallTooFar> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> start_position;
  std::optional<robocin::Point2Df> end_position;

  explicit RobotDribbledBallTooFarMessage(std::optional<Team> by_team = std::nullopt,
                                          std::optional<RobotIdMessage> by_robot = std::nullopt,
                                          std::optional<robocin::Point2Df> start_position
                                          = std::nullopt,
                                          std::optional<robocin::Point2Df> end_position
                                          = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::RobotDribbledBallTooFar toProto() const override {
    return protocols::common::GameEvent::RobotDribbledBallTooFar{};
  };

  void fromProto(const protocols::common::GameEvent::RobotDribbledBallTooFar&
                     robot_dribbled_ball_too_far_proto);
};

class RobotTippedOverMessage
    : public IProtoConvertible<protocols::common::GameEvent::RobotTippedOver> {
 public:
  std::optional<Team> by_team;
  std::optional<RobotIdMessage> by_robot;
  std::optional<robocin::Point2Df> robot_position;
  std::optional<robocin::Point2Df> ball_position;

  explicit RobotTippedOverMessage(std::optional<Team> by_team,
                                  std::optional<RobotIdMessage> by_robot,
                                  std::optional<robocin::Point2Df> robot_position,
                                  std::optional<robocin::Point2Df> ball_position);

  [[nodiscard]] protocols::common::GameEvent::RobotTippedOver toProto() const override {
    return protocols::common::GameEvent::RobotTippedOver{};
  };

  void fromProto(const protocols::common::GameEvent::RobotTippedOver& robot_tipped_over_proto);
};

class GoalMessage : public IProtoConvertible<protocols::common::GameEvent::Goal> {
 public:
  std::optional<Team> by_team;
  std::optional<Team> kicking_team;
  std::optional<RobotIdMessage> kicking_robot;
  std::optional<robocin::Point2Df> ball_position_when_scored;
  std::optional<robocin::Point2Df> kick_position;
  std::optional<float> max_ball_height;
  std::optional<uint32_t> num_of_robots_of_scoring_team;
  std::optional<uint32_t>
      last_touch_by_scoring_team_timestamp; // todo(fnap): discuss how to use timestamp
  std::optional<std::string> message;

  explicit GoalMessage(std::optional<Team> by_team = std::nullopt,
                       std::optional<Team> kicking_team = std::nullopt,
                       std::optional<RobotIdMessage> kicking_robot = std::nullopt,
                       std::optional<robocin::Point2Df> ball_position_when_scored = std::nullopt,
                       std::optional<robocin::Point2Df> kick_position = std::nullopt,
                       std::optional<float> max_ball_height = std::nullopt,
                       std::optional<uint32_t> num_of_robots_of_scoring_team = std::nullopt,
                       std::optional<uint32_t> last_touch_by_scoring_team_timestamp = std::nullopt,
                       std::optional<std::string> message = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent::Goal toProto() const override {
    return protocols::common::GameEvent::Goal{};
  };

  void fromProto(const protocols::common::GameEvent::Goal& goal_proto);
};

class GameEventMessage : public IProtoConvertible<protocols::common::GameEvent> {
 public:
  std::vector<std::string> sources;
  std::optional<uint32_t> timestamp; // todo(fnap): discuss how to use timestamp

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

  explicit GameEventMessage(
      std::vector<std::string> sources = {},
      std::optional<uint32_t> timestamp = std::nullopt,
      std::optional<BallLeftFieldMessage> ball_left_field = std::nullopt,
      std::optional<BallLeftFieldBoundaryMessage> ball_left_field_boundary = std::nullopt,
      std::optional<AimlessKickMessage> aimless_kick = std::nullopt,
      std::optional<GoalkeeperHeldBallMessage> goalkeeper_held_ball = std::nullopt,
      std::optional<RobotTooCloseToDefenseAreaMessage> robot_too_close_to_defense_area
      = std::nullopt,
      std::optional<RobotInDefenseAreaMessage> robot_in_defense_area = std::nullopt,
      std::optional<RobotPushedRobotMessage> robot_pushed_robot = std::nullopt,
      std::optional<RobotHeldBallDeliberatelyMessage> robot_held_ball_deliberately = std::nullopt,
      std::optional<RobotDribbledBallTooFarMessage> robot_dribbled_ball_too_far = std::nullopt,
      std::optional<RobotTippedOverMessage> robot_tipped_over = std::nullopt,
      std::optional<GoalMessage> goal = std::nullopt);

  [[nodiscard]] protocols::common::GameEvent toProto() const override {
    return protocols::common::GameEvent{};
  };

  void fromProto(const protocols::common::GameEvent& goal_proto);
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_GAME_EVENT_GAME_EVENT_MESSAGE_H
