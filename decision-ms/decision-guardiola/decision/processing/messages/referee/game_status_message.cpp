#include "decision/processing/messages/referee/game_status_message.h"

#include <protocols/common/game_stage.pb.h>
#include <protocols/common/match_type.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <sys/types.h>
#include <utility>

namespace decision {
namespace {
namespace rc {
using ::protocols::common::GameStage;
using ::protocols::common::MatchType;
} // namespace rc
} // namespace

/////////////////////////////////// GameEventsProposalMessage ///////////////////////////////////
GameEventsProposalMessage::GameEventsProposalMessage(std::optional<std::string> proposal_id,
                                                     std::vector<GameEventMessage> game_events,
                                                     std::optional<bool> was_accepted) :
    proposal_id(std::move(proposal_id)),
    was_accepted(was_accepted) {};

void GameEventsProposalMessage::fromProto(
    const protocols::referee::GameStatus::GameEventsProposal& game_events_proposal_proto) {
  proposal_id = game_events_proposal_proto.proposal_id();
  was_accepted = game_events_proposal_proto.was_accepted();

  for (const auto& game_event : game_events_proposal_proto.game_events()) {
    game_events.emplace_back(game_event);
  }
}

GameEventsProposalMessage::GameEventsProposalMessage(
    const protocols::referee::GameStatus::GameEventsProposal& game_events_proposal_proto) {
  GameEventsProposalMessage::fromProto(game_events_proposal_proto);
}

/////////////////////////////////// TeamMessage ///////////////////////////////////

TeamMessage::TeamMessage(std::optional<std::string> name,
                         std::optional<uint32_t> score,
                         std::vector<RobotIdMessage> robot_ids,
                         std::optional<RobotIdMessage> goalkeeper_id,
                         std::optional<uint32_t> yellow_cards,
                         std::vector<uint32_t> time_to_expire_active_yellow_cards,
                         std::optional<uint32_t> red_cards,
                         std::optional<uint32_t> timeouts_left,
                         std::optional<google::protobuf::Duration> total_timeout_time_left,
                         std::optional<uint32_t> total_fouls_committed,
                         std::optional<uint32_t> consecutive_ball_placement_failures,
                         std::optional<bool> is_ball_placement_enabled,
                         std::optional<bool> has_ball_placement_failures_reached_maximum,
                         std::optional<uint32_t> maximum_allowed_robots,
                         std::optional<bool> is_robot_substitution_requested,
                         std::optional<bool> is_robot_substitution_allowed,
                         std::optional<uint32_t> robot_substitutions_left,
                         std::optional<uint32_t> robot_substitution_time_left) :
    name(std::move(name)),
    score(score),
    robot_ids(std::move(robot_ids)),
    goalkeeper_id(std::move(goalkeeper_id)),
    yellow_cards(yellow_cards),
    time_to_expire_active_yellow_cards(std::move(time_to_expire_active_yellow_cards)),
    red_cards(red_cards),
    timeouts_left(timeouts_left),
    total_timeout_time_left(std::move(total_timeout_time_left)),
    total_fouls_committed(total_fouls_committed),
    consecutive_ball_placement_failures(consecutive_ball_placement_failures),
    is_ball_placement_enabled(is_ball_placement_enabled),
    has_ball_placement_failures_reached_maximum(has_ball_placement_failures_reached_maximum),
    maximum_allowed_robots(maximum_allowed_robots),
    is_robot_substitution_requested(is_robot_substitution_requested),
    is_robot_substitution_allowed(is_robot_substitution_allowed),
    robot_substitutions_left(robot_substitutions_left),
    robot_substitution_time_left(robot_substitution_time_left) {}

TeamMessage::TeamMessage(const protocols::referee::GameStatus::Team& team_proto) {
  TeamMessage::fromProto(team_proto);
}

void TeamMessage::fromProto(const protocols::referee::GameStatus::Team& team_proto) {
  name = team_proto.name();
  score = team_proto.score();

  for (const auto& robot_id : team_proto.robot_ids()) {
    robot_ids.emplace_back(robot_id);
  }

  if (team_proto.has_goalkeeper_id()) {
    if (!goalkeeper_id.has_value()) {
      goalkeeper_id.emplace();
    }

    goalkeeper_id->fromProto(team_proto.goalkeeper_id());
  }

  yellow_cards = team_proto.yellow_cards();

  // time_to_expire_active_yellow_cards
  for (const auto& time_to_expire_active_yellow_card :
       team_proto.time_to_expire_active_yellow_cards()) {
    // todo(fnap): discuss how to use duration
    time_to_expire_active_yellow_cards.emplace_back(time_to_expire_active_yellow_card.seconds());
  }

  red_cards = team_proto.red_cards();
  timeouts_left = team_proto.timeouts_left();
  total_timeout_time_left = team_proto.total_timeout_time_left();
  total_fouls_committed = team_proto.total_fouls_committed();
  consecutive_ball_placement_failures = team_proto.consecutive_ball_placement_failures();
  is_ball_placement_enabled = team_proto.is_ball_placement_enabled();
  has_ball_placement_failures_reached_maximum
      = team_proto.has_ball_placement_failures_reached_maximum();
  maximum_allowed_robots = team_proto.maximum_allowed_robots();
  is_robot_substitution_requested = team_proto.is_robot_substitution_requested();
  is_robot_substitution_allowed = team_proto.is_robot_substitution_allowed();
  robot_substitutions_left = team_proto.robot_substitutions_left();
  robot_substitution_time_left = team_proto.robot_substitution_time_left()
                                     .seconds(); // todo(fnap): discuss how to use duration
}

/////////////////////////////////// GameStatusMessage ///////////////////////////////////

GameStatusMessage::GameStatusMessage(std::optional<std::string> source_id,
                                     std::optional<std::string> description,
                                     std::optional<uint32_t> timestamp,
                                     std::optional<MatchType> match_type,
                                     std::optional<TeamMessage> home_team,
                                     std::optional<TeamMessage> away_team,
                                     std::optional<GameStage> game_stage,
                                     std::optional<uint32_t> game_stage_time_left,
                                     std::optional<uint64_t> total_commands_issued,
                                     std::optional<uint32_t> command_issued_timestamp,
                                     std::optional<GameCommandMessage> command,
                                     std::optional<GameCommandMessage> next_command,
                                     std::vector<GameEventMessage> game_events,
                                     std::vector<GameEventsProposalMessage> game_events_proposals) :
    source_id(std::move(source_id)),
    description(std::move(description)),
    timestamp(timestamp),
    match_type(match_type),
    home_team(std::move(home_team)),
    away_team(std::move(away_team)),
    game_stage(game_stage),
    game_stage_time_left(game_stage_time_left),
    total_commands_issued(total_commands_issued),
    command_issued_timestamp(command_issued_timestamp),
    command(std::move(command)),
    next_command(std::move(next_command)),
    game_events(std::move(game_events)),
    game_events_proposals(std::move(game_events_proposals)) {}

GameStatusMessage::GameStatusMessage(const protocols::referee::GameStatus& game_status_proto) {
  GameStatusMessage::fromProto(game_status_proto);
}

GameStatusMessage::MatchType getMatchType(rc::MatchType match_type_proto) {
  switch (match_type_proto) {
    case protocols::common::MATCH_TYPE_GROUP_PHASE:
      return GameStatusMessage::MatchType::MATCH_TYPE_GROUP_PHASE;
    case protocols::common::MATCH_TYPE_ELIMINATION_PHASE:
      return GameStatusMessage::MatchType::MATCH_TYPE_ELIMINATION_PHASE;
    case protocols::common::MATCH_TYPE_FRIENDLY:
      return GameStatusMessage::MatchType::MATCH_TYPE_FRIENDLY;
    default: return GameStatusMessage::MatchType::MATCH_TYPE_UNSPECIFIED;
  }
}

GameStatusMessage::GameStage getGameStage(rc::GameStage game_stage_proto) {
  switch (game_stage_proto) {
    case protocols::common::GameStage::GAME_STAGE_NORMAL_FIRST_HALF_PRE:
      return GameStatusMessage::GAME_STAGE_NORMAL_FIRST_HALF_PRE;
    case protocols::common::GameStage::GAME_STAGE_NORMAL_FIRST_HALF:
      return GameStatusMessage::GAME_STAGE_NORMAL_FIRST_HALF;
    case protocols::common::GameStage::GAME_STAGE_NORMAL_HALF_TIME:
      return GameStatusMessage::GAME_STAGE_NORMAL_HALF_TIME;
    case protocols::common::GameStage::GAME_STAGE_NORMAL_SECOND_HALF_PRE:
      return GameStatusMessage::GAME_STAGE_NORMAL_SECOND_HALF_PRE;
    case protocols::common::GameStage::GAME_STAGE_NORMAL_SECOND_HALF:
      return GameStatusMessage::GAME_STAGE_NORMAL_SECOND_HALF;
    case protocols::common::GameStage::GAME_STAGE_EXTRA_TIME_BREAK:
      return GameStatusMessage::GAME_STAGE_EXTRA_TIME_BREAK;
    case protocols::common::GameStage::GAME_STAGE_EXTRA_FIRST_HALF_PRE:
      return GameStatusMessage::GAME_STAGE_EXTRA_FIRST_HALF_PRE;
    case protocols::common::GameStage::GAME_STAGE_EXTRA_FIRST_HALF:
      return GameStatusMessage::GAME_STAGE_EXTRA_FIRST_HALF;
    case protocols::common::GameStage::GAME_STAGE_EXTRA_HALF_TIME:
      return GameStatusMessage::GAME_STAGE_EXTRA_HALF_TIME;
    case protocols::common::GameStage::GAME_STAGE_EXTRA_SECOND_HALF_PRE:
      return GameStatusMessage::GAME_STAGE_EXTRA_SECOND_HALF_PRE;
    case protocols::common::GameStage::GAME_STAGE_EXTRA_SECOND_HALF:
      return GameStatusMessage::GAME_STAGE_EXTRA_SECOND_HALF;
    case protocols::common::GameStage::GAME_STAGE_PENALTY_SHOOTOUT_BREAK:
      return GameStatusMessage::GAME_STAGE_PENALTY_SHOOTOUT_BREAK;
    case protocols::common::GameStage::GAME_STAGE_PENALTY_SHOOTOUT:
      return GameStatusMessage::GAME_STAGE_PENALTY_SHOOTOUT;
    case protocols::common::GameStage::GAME_STAGE_POST_GAME:
      return GameStatusMessage::GAME_STAGE_POST_GAME;
    default: return GameStatusMessage::GameStage::GAME_STAGE_UNSPECIFIED;
  }
}

void GameStatusMessage::fromProto(const protocols::referee::GameStatus& game_status_proto) {
  source_id = game_status_proto.source_id();
  description = game_status_proto.description();
  timestamp = game_status_proto.timestamp().seconds(); // todo(fnap): discuss how to use this field
  match_type = getMatchType(game_status_proto.match_type());

  if (game_status_proto.has_home_team()) {
    if (!home_team.has_value()) {
      home_team.emplace();
    }

    home_team->fromProto(game_status_proto.home_team());
  }

  if (game_status_proto.has_away_team()) {
    if (!away_team.has_value()) {
      away_team.emplace();
    }

    away_team->fromProto(game_status_proto.away_team());
  }

  game_stage = getGameStage(game_status_proto.game_stage());

  if (game_status_proto.has_game_stage_time_left()) {
    game_stage_time_left = game_status_proto.game_stage_time_left()
                               .seconds(); // todo(fnap): discuss how to use duration
  }

  total_commands_issued = game_status_proto.total_commands_issued();
  command_issued_timestamp = game_status_proto.command_issued_timestamp()
                                 .seconds(); // todo(fnap): discuss how to use timestamp

  if (game_status_proto.has_command()) {
    if (!command.has_value()) {
      command.emplace();
    }

    // implement, always returns empty command
    command->fromProto(game_status_proto.command());
  }

  if (game_status_proto.has_next_command()) {
    if (!next_command.has_value()) {
      next_command.emplace();
    }

    // implement
    next_command->fromProto(game_status_proto.next_command());
  }

  for (const auto& game_event : game_status_proto.game_events()) {
    game_events.emplace_back(game_event);
  }

  for (const auto& game_events_proposal : game_status_proto.game_events_proposals()) {
    game_events_proposals.emplace_back(game_events_proposal);
  }
}

} // namespace decision
