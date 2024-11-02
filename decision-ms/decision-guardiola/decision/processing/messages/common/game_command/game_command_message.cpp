#include "decision/processing/messages/common/game_command/game_command_message.h"

#include <protocols/common/game_command.pb.h>
#include <protocols/referee/game_status.pb.h>

namespace decision {
// todo(fnap): implement

// Halt
protocols::common::GameCommand::Halt GameCommandMessage::HaltMessage::toProto() const {
  return protocols::common::GameCommand::Halt{};
}

void GameCommandMessage::HaltMessage::fromProto(
    const protocols::common::GameCommand::Halt& halt_proto) {};

// InGame
protocols::common::GameCommand::InGame GameCommandMessage::InGameMessage::toProto() const {
  return protocols::common::GameCommand::InGame{};
};

void GameCommandMessage::InGameMessage::fromProto(
    const protocols::common::GameCommand::InGame& in_game_proto) {};

// Stop
protocols::common::GameCommand::Stop GameCommandMessage::StopMessage::toProto() const {
  return protocols::common::GameCommand::Stop{};
};

void GameCommandMessage::StopMessage::fromProto(
    const protocols::common::GameCommand::Stop& stop_proto) {};

// BallPlacement
protocols::common::GameCommand::BallPlacement
GameCommandMessage::BallPlacementMessage::toProto() const {
  return protocols::common::GameCommand::BallPlacement{};
};

void GameCommandMessage::BallPlacementMessage::fromProto(
    const protocols::common::GameCommand::BallPlacement& ball_placement_proto) {};

// PrepareKickOff
protocols::common::GameCommand::PrepareKickoff
GameCommandMessage::PrepareKickoffMessage::toProto() const {
  return protocols::common::GameCommand::PrepareKickoff{};
};

void GameCommandMessage::PrepareKickoffMessage::fromProto(
    const protocols::common::GameCommand::PrepareKickoff& prepare_kick_off_proto) {};

// KickOffMessage
protocols::common::GameCommand::Kickoff GameCommandMessage::KickoffMessage::toProto() const {
  return protocols::common::GameCommand::Kickoff{};
}

void GameCommandMessage::KickoffMessage::fromProto(
    const protocols::common::GameCommand::Kickoff& kick_off_proto) {};

// PreparePenalty
protocols::common::GameCommand::PreparePenalty
GameCommandMessage::PreparePenaltyMessage::toProto() const {
  return protocols::common::GameCommand::PreparePenalty{};
};

void GameCommandMessage::PreparePenaltyMessage::fromProto(
    const protocols::common::GameCommand::PreparePenalty& prepare_penalty_proto) {};

// Penalty
protocols::common::GameCommand::Penalty GameCommandMessage::PenaltyMessage::toProto() const {
  return protocols::common::GameCommand::Penalty{};
};

void GameCommandMessage::PenaltyMessage::fromProto(
    const protocols::common::GameCommand::Penalty& penalty_proto) {};

// PrepareDirectFreeKick
protocols::common::GameCommand::PrepareDirectFreeKick
GameCommandMessage::PrepareDirectFreeKickMessage::toProto() const {
  return protocols::common::GameCommand::PrepareDirectFreeKick{};
};

void GameCommandMessage::PrepareDirectFreeKickMessage::fromProto(
    const protocols::common::GameCommand::PrepareDirectFreeKick& penalty_proto) {};

// DirectFreeKick
protocols::common::GameCommand::DirectFreeKick
GameCommandMessage::DirectFreeKickMessage::toProto() const {
  return protocols::common::GameCommand::DirectFreeKick{};
};

void GameCommandMessage::DirectFreeKickMessage::fromProto(
    const protocols::common::GameCommand::DirectFreeKick& direct_free_kick_proto) {};

// Timeout
protocols::common::GameCommand::Timeout GameCommandMessage::TimeoutMessage::toProto() const {
  return protocols::common::GameCommand::Timeout{};
};

void GameCommandMessage::TimeoutMessage::fromProto(
    const protocols::common::GameCommand::Timeout& timeout_proto) {};

// Interval
protocols::common::GameCommand::Interval GameCommandMessage::IntervalMessage::toProto() const {
  return protocols::common::GameCommand::Interval{};
};

void GameCommandMessage::IntervalMessage::fromProto(
    const protocols::common::GameCommand::Interval& timeout_proto) {};

// GameCommand
protocols::common::GameCommand GameCommandMessage::toProto() const {
  return protocols::common::GameCommand{};
};

void GameCommandMessage::fromProto(const protocols::common::GameCommand& game_command_proto) {};

}; // namespace decision
