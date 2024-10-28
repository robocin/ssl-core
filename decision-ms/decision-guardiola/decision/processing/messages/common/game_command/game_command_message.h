#ifndef DECISION_PROCESSING_MESSAGES_COMMON_GAME_COMMAND_GAME_COMMAND_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_COMMON_GAME_COMMAND_GAME_COMMAND_MESSAGE_H

#include <cstdint>
#include <google/protobuf/duration.pb.h>
#include <optional>
#include <robocin/geometry/point2d.h>

namespace decision {

class GameCommandMessage {
 public:
  // Inner command classes
  class HaltMessage {
   public:
    HaltMessage() = default;
  };

  class InGameMessage {
   public:
    InGameMessage() = default;
  };

  class StopMessage {
   public:
    StopMessage() = default;
  };

  class BallPlacementMessage {
   public:
    std::optional<robocin::Point2Df> position;
    std::optional<uint32_t> remaining_time; // todo(fnap): discuss what to use with duration

    BallPlacementMessage() = default;
    BallPlacementMessage(const robocin::Point2Df& position, const uint32_t& time) :
        position(position),
        remaining_time(time) {}
  };

  class PrepareKickoffMessage {
   public:
    PrepareKickoffMessage() = default;
  };

  class KickoffMessage {
   public:
    std::optional<google::protobuf::Duration> remaining_time;

    explicit KickoffMessage(const google::protobuf::Duration& time) : remaining_time(time) {}
  };

  class PreparePenaltyMessage {
   public:
    PreparePenaltyMessage() = default;
  };

  class PenaltyMessage {
   public:
    std::optional<google::protobuf::Duration> remaining_time;

    PenaltyMessage() = default;
    explicit PenaltyMessage(const google::protobuf::Duration& time) : remaining_time(time) {}
  };

  class PrepareDirectFreeKickMessage {
   public:
    PrepareDirectFreeKickMessage() = default;
  };

  class DirectFreeKickMessage {
   public:
    std::optional<google::protobuf::Duration> remaining_time;

    DirectFreeKickMessage() = default;
    explicit DirectFreeKickMessage(const google::protobuf::Duration& time) : remaining_time(time) {}
  };

  class TimeoutMessage {
   public:
    TimeoutMessage() = default;
  };

  class IntervalMessage {
   public:
    IntervalMessage() = default;
  };

  // Optional fields for each command type
  std::optional<HaltMessage> halt;
  std::optional<InGameMessage> in_game;
  std::optional<StopMessage> stop;

  std::optional<BallPlacementMessage> home_ball_placement;
  std::optional<BallPlacementMessage> away_ball_placement;

  std::optional<PrepareKickoffMessage> home_prepare_kickoff;
  std::optional<PrepareKickoffMessage> away_prepare_kickoff;

  std::optional<KickoffMessage> home_kickoff;
  std::optional<KickoffMessage> away_kickoff;

  std::optional<PreparePenaltyMessage> home_prepare_penalty;
  std::optional<PreparePenaltyMessage> away_prepare_penalty;
  std::optional<PenaltyMessage> home_penalty;
  std::optional<PenaltyMessage> away_penalty;

  std::optional<PrepareDirectFreeKickMessage> home_prepare_direct_free_kick;
  std::optional<PrepareDirectFreeKickMessage> away_prepare_direct_free_kick;

  std::optional<DirectFreeKickMessage> home_direct_free_kick;
  std::optional<DirectFreeKickMessage> away_direct_free_kick;

  std::optional<TimeoutMessage> home_timeout;
  std::optional<TimeoutMessage> away_timeout;

  std::optional<IntervalMessage> interval;
};

} // namespace decision
#endif // DECISION_PROCESSING_MESSAGES_COMMON_GAME_COMMAND_GAME_COMMAND_MESSAGE_H
