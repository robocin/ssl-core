#include "behavior/processing/messages/common/game_command/game_command_message.h"

#include "behavior/processing/messages/common/robot_kick/kick_command.h"

#include <protocols/common/game_command.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <robocin/geometry/point2d.h>

namespace behavior {
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

GameCommandMessage::BallPlacementMessage::BallPlacementMessage(
    std::optional<robocin::Point2Df> position,
    std::optional<uint32_t> remaining_time) :
    position(std::move(position)),
    remaining_time(std::move(remaining_time)) {}

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

GameCommandMessage::KickoffMessage::KickoffMessage(const uint32_t& time) : remaining_time(time) {}

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
    const protocols::common::GameCommand::Penalty& penalty_proto) {
  if (penalty_proto.has_remaining_time()) {
    if (!remaining_time.has_value()) {
      remaining_time.emplace();
    }

    remaining_time = penalty_proto.remaining_time().seconds();
  }
};

GameCommandMessage::PenaltyMessage::PenaltyMessage(const uint32_t& time) : remaining_time(time) {}

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

GameCommandMessage::DirectFreeKickMessage::DirectFreeKickMessage(const uint32_t& time) :
    remaining_time(time) {}

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

void GameCommandMessage::fromProto(const protocols::common::GameCommand& game_command_proto) {
  if (game_command_proto.has_halt()) {
    halt = HaltMessage();
  }

  if (game_command_proto.has_in_game()) {
    in_game = InGameMessage();
  }

  if (game_command_proto.has_stop()) {
    stop = StopMessage();
  }

  if (game_command_proto.has_home_ball_placement()) {
    home_ball_placement = BallPlacementMessage(
        robocin::Point2Df(game_command_proto.home_ball_placement().position().x(),
                          game_command_proto.home_ball_placement().position().y()),
        game_command_proto.home_ball_placement().remaining_time().seconds());
  }

  if (game_command_proto.has_away_ball_placement()) {
    away_ball_placement = BallPlacementMessage(
        robocin::Point2Df(game_command_proto.away_ball_placement().position().x(),
                          game_command_proto.away_ball_placement().position().y()),
        game_command_proto.away_ball_placement().remaining_time().seconds());
  }

  if (game_command_proto.has_home_kickoff()) {
    home_kickoff = KickoffMessage(game_command_proto.home_kickoff().remaining_time().seconds());
  }

  if (game_command_proto.has_away_kickoff()) {
    away_kickoff = KickoffMessage(game_command_proto.home_kickoff().remaining_time().seconds());
  }

  if (game_command_proto.has_home_prepare_penalty()) {
    home_prepare_penalty = PreparePenaltyMessage();
  }

  if (game_command_proto.has_away_prepare_penalty()) {
    away_prepare_penalty = PreparePenaltyMessage();
  }

  if (game_command_proto.has_home_penalty()) {
    home_penalty = PenaltyMessage(game_command_proto.home_penalty().remaining_time().seconds());
  }

  if (game_command_proto.has_away_penalty()) {
    away_penalty = PenaltyMessage(game_command_proto.home_penalty().remaining_time().seconds());
  }

  if (game_command_proto.has_home_prepare_direct_free_kick()) {
    home_prepare_direct_free_kick = PrepareDirectFreeKickMessage();
  }

  if (game_command_proto.has_away_prepare_direct_free_kick()) {
    away_prepare_direct_free_kick = PrepareDirectFreeKickMessage();
  }

  if (game_command_proto.has_home_direct_free_kick()) {
    home_direct_free_kick = DirectFreeKickMessage(
        game_command_proto.home_direct_free_kick().remaining_time().seconds());
  }

  if (game_command_proto.has_away_direct_free_kick()) {
    away_direct_free_kick = DirectFreeKickMessage(
        game_command_proto.home_direct_free_kick().remaining_time().seconds());
  }
};

}; // namespace behavior
