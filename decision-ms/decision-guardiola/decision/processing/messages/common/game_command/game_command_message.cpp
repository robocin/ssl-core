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

void fromProto(const protocols::common::GameCommand::BallPlacement& ball_placement_proto) {};

// PrepareKickOff
protocols::common::GameCommand::PrepareKickoff
GameCommandMessage::PrepareKickoffMessage::toProto() const {
  return protocols::common::GameCommand::PrepareKickoff{};
};

void GameCommandMessage::PrepareKickoffMessage::fromProto(
    const protocols::common::GameCommand::PrepareKickoff& prepare_kick_off_proto) {};

} // namespace decision
