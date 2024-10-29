#ifndef DECISION_PROCESSING_MESSAGES_REFEREE_GAME_STATUS_H
#define DECISION_PROCESSING_MESSAGES_REFEREE_GAME_STATUS_H

#include "decision/processing/messages/common/game_command/game_command_message.h"
#include "decision/processing/messages/common/game_event/game_event_message.h"
#include "decision/processing/messages/common/robot_id/robot_id_message.h"

#include <cstdint>
#include <optional>
#include <protocols/referee/game_status.pb.h>
#include <robocin/utility/iproto_convertible.h>
#include <utility>

namespace decision {

class GameEventsProposalMessage
    : public robocin::IProtoConvertible<protocols::referee::GameStatus::GameEventsProposal> {
 public:
  std::optional<std::string> proposal_id;
  std::vector<GameEventMessage> game_events;
  std::optional<bool> was_accepted;

  explicit GameEventsProposalMessage(std::optional<std::string> proposal_id,
                                     std::vector<GameEventMessage> game_events,
                                     std::optional<bool> was_accepted);

  explicit GameEventsProposalMessage(
      const protocols::referee::GameStatus::GameEventsProposal& game_events_proposal_proto);

  [[nodiscard]] protocols::referee::GameStatus::GameEventsProposal toProto() const override {
    return protocols::referee::GameStatus::GameEventsProposal{};
  };

  void fromProto(const protocols::referee::GameStatus::GameEventsProposal&
                     game_events_proposal_proto) override;
};

class TeamMessage : public robocin::IProtoConvertible<protocols::referee::GameStatus::Team> {
 public:
  std::optional<std::string> name;
  std::optional<uint32_t> score;

  std::vector<RobotIdMessage> robot_ids;
  std::optional<RobotIdMessage> goalkeeper_id;

  std::optional<uint32_t> yellow_cards;
  std::vector<uint32_t> time_to_expire_active_yellow_cards;

  std::optional<uint32_t> red_cards;

  std::optional<uint32_t> timeouts_left;
  std::optional<google::protobuf::Duration> total_timeout_time_left;

  std::optional<uint32_t> total_fouls_committed;

  std::optional<uint32_t> consecutive_ball_placement_failures;
  std::optional<bool> is_ball_placement_enabled;
  std::optional<bool> has_ball_placement_failures_reached_maximum;

  std::optional<uint32_t> maximum_allowed_robots;

  std::optional<bool> is_robot_substitution_requested;
  std::optional<bool> is_robot_substitution_allowed;

  std::optional<uint32_t> robot_substitutions_left;
  std::optional<uint32_t>
      robot_substitution_time_left; // todo(fnap): discuss what to do with proto duration

  explicit TeamMessage(std::optional<std::string> name = std::nullopt,
                       std::optional<uint32_t> score = std::nullopt,
                       std::vector<RobotIdMessage> robot_ids = {},
                       std::optional<RobotIdMessage> goalkeeper_id = std::nullopt,
                       std::optional<uint32_t> yellow_cards = std::nullopt,
                       std::vector<uint32_t> time_to_expire_active_yellow_cards = {},
                       std::optional<uint32_t> red_cards = std::nullopt,
                       std::optional<uint32_t> timeouts_left = std::nullopt,
                       std::optional<google::protobuf::Duration> total_timeout_time_left
                       = std::nullopt,
                       std::optional<uint32_t> total_fouls_committed = std::nullopt,
                       std::optional<uint32_t> consecutive_ball_placement_failures = std::nullopt,
                       std::optional<bool> is_ball_placement_enabled = std::nullopt,
                       std::optional<bool> has_ball_placement_failures_reached_maximum
                       = std::nullopt,
                       std::optional<uint32_t> maximum_allowed_robots = std::nullopt,
                       std::optional<bool> is_robot_substitution_requested = std::nullopt,
                       std::optional<bool> is_robot_substitution_allowed = std::nullopt,
                       std::optional<uint32_t> robot_substitutions_left = std::nullopt,
                       std::optional<uint32_t> robot_substitution_time_left = std::nullopt);

  explicit TeamMessage(const protocols::referee::GameStatus::Team& team_proto);

  [[nodiscard]] protocols::referee::GameStatus::Team toProto() const override {
    return protocols::referee::GameStatus::Team{};
  };

  void fromProto(const protocols::referee::GameStatus::Team& team_proto) override;
};

class GameStatusMessage : public robocin::IProtoConvertible<protocols::referee::GameStatus> {
 public:
  enum GameStage {
    GAME_STAGE_UNSPECIFIED = 0,
    GAME_STAGE_NORMAL_FIRST_HALF_PRE = 1,
    GAME_STAGE_NORMAL_FIRST_HALF = 2,
    GAME_STAGE_NORMAL_HALF_TIME = 3,
    GAME_STAGE_NORMAL_SECOND_HALF_PRE = 4,
    GAME_STAGE_NORMAL_SECOND_HALF = 5,
    GAME_STAGE_EXTRA_TIME_BREAK = 6,
    GAME_STAGE_EXTRA_FIRST_HALF_PRE = 7,
    GAME_STAGE_EXTRA_FIRST_HALF = 8,
    GAME_STAGE_EXTRA_HALF_TIME = 9,
    GAME_STAGE_EXTRA_SECOND_HALF_PRE = 10,
    GAME_STAGE_EXTRA_SECOND_HALF = 11,
    GAME_STAGE_PENALTY_SHOOTOUT_BREAK = 12,
    GAME_STAGE_PENALTY_SHOOTOUT = 13,
    GAME_STAGE_POST_GAME = 14
  };

  enum MatchType {
    MATCH_TYPE_UNSPECIFIED = 0,
    MATCH_TYPE_GROUP_PHASE = 1,
    MATCH_TYPE_ELIMINATION_PHASE = 2,
    MATCH_TYPE_FRIENDLY = 3,
  };

  std::optional<std::string> source_id;
  std::optional<std::string> description;
  std::optional<uint32_t> timestamp; // todo(fnap): discuss how to use timestamp
  std::optional<MatchType> match_type;

  std::optional<TeamMessage> home_team;
  std::optional<TeamMessage> away_team;

  std::optional<GameStage> game_stage;
  std::optional<uint32_t> game_stage_time_left; // todo(fnap): discuss how to use duration

  std::optional<uint64_t> total_commands_issued;
  std::optional<uint32_t> command_issued_timestamp; // todo(fnap): discuss how to use timestamp
  std::optional<GameCommandMessage> command;
  std::optional<GameCommandMessage> next_command;

  std::vector<GameEventMessage> game_events;
  std::vector<GameEventsProposalMessage> game_events_proposals;

  explicit GameStatusMessage(std::optional<std::string> source_id = std::nullopt,
                             std::optional<std::string> description = std::nullopt,
                             std::optional<uint32_t> timestamp = std::nullopt,
                             std::optional<MatchType> match_type = std::nullopt,
                             std::optional<TeamMessage> home_team = std::nullopt,
                             std::optional<TeamMessage> away_team = std::nullopt,
                             std::optional<GameStage> game_stage = std::nullopt,
                             std::optional<uint32_t> game_stage_time_left = std::nullopt,
                             std::optional<uint64_t> total_commands_issued = std::nullopt,
                             std::optional<uint32_t> command_issued_timestamp = std::nullopt,
                             std::optional<GameCommandMessage> command = std::nullopt,
                             std::optional<GameCommandMessage> next_command = std::nullopt,
                             std::vector<GameEventMessage> game_events = {},
                             std::vector<GameEventsProposalMessage> game_events_proposals = {});

  explicit GameStatusMessage(const protocols::referee::GameStatus& game_status_proto);

  [[nodiscard]] protocols::referee::GameStatus toProto() const override {
    return protocols::referee::GameStatus{};
  };

  void fromProto(const protocols::referee::GameStatus& game_status_proto) override;
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_REFEREE_GAME_STATUS_H
