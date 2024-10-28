#include "decision/processing/messages/referee/game_status_message.h"

#include <utility>

namespace decision {
GameEventsProposalMessage::GameEventsProposalMessage(std::optional<std::string> proposal_id,
                                                     std::vector<GameEventMessage> game_events,
                                                     std::optional<bool> was_accepted) :
    proposal_id(std::move(proposal_id)),
    was_accepted(was_accepted) {};

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

GameStatusMessage::GameStatusMessage(
    std::optional<std::string> source_id,
    std::optional<std::string> description,
    std::optional<google::protobuf::Timestamp> timestamp,
    std::optional<MatchType> match_type,
    std::optional<Team> home_team,
    std::optional<Team> away_team,
    std::optional<GameStage> game_stage,
    std::optional<google::protobuf::Duration> game_stage_time_left,
    std::optional<uint64_t> total_commands_issued,
    std::optional<google::protobuf::Timestamp> command_issued_timestamp,
    std::optional<GameCommandMessage> command,
    std::optional<GameCommandMessage> next_command,
    std::vector<GameEventMessage> game_events,
    std::vector<GameEventsProposalMessage> game_events_proposals) :
    source_id(std::move(source_id)),
    description(std::move(description)),
    timestamp(std::move(timestamp)),
    match_type(match_type),
    home_team(home_team),
    away_team(away_team),
    game_stage(game_stage),
    game_stage_time_left(std::move(game_stage_time_left)),
    total_commands_issued(total_commands_issued),
    command_issued_timestamp(std::move(command_issued_timestamp)),
    command(std::move(command)),
    next_command(std::move(next_command)),
    game_events(std::move(game_events)),
    game_events_proposals(std::move(game_events_proposals)) {}

} // namespace decision
