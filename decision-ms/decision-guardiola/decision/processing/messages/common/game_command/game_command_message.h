#ifndef DECISION_PROCESSING_MESSAGES_COMMON_GAME_COMMAND_GAME_COMMAND_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_COMMON_GAME_COMMAND_GAME_COMMAND_MESSAGE_H

#include <cstdint>
#include <google/protobuf/duration.pb.h>
#include <optional>
#include <protocols/common/game_command.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace decision {

class GameCommandMessage : public robocin::IProtoConvertible<protocols::common::GameCommand> {
 public:
  // Inner command classes
  class HaltMessage : public robocin::IProtoConvertible<protocols::common::GameCommand::Halt> {
   public:
    explicit HaltMessage();

    [[nodiscard]] protocols::common::GameCommand::Halt toProto() const override {
      return protocols::common::GameCommand::Halt{};
    };

    void fromProto(const protocols::common::GameCommand::Halt& halt_proto) override;
  };

  class InGameMessage : public robocin::IProtoConvertible<protocols::common::GameCommand::InGame> {
   public:
    explicit InGameMessage();

    [[nodiscard]] protocols::common::GameCommand::InGame toProto() const override {
      return protocols::common::GameCommand::InGame{};
    };

    void fromProto(const protocols::common::GameCommand::InGame& in_game_proto) override;
  };

  class StopMessage : public robocin::IProtoConvertible<protocols::common::GameCommand::Stop> {
   public:
    explicit StopMessage();

    [[nodiscard]] protocols::common::GameCommand::Stop toProto() const override {
      return protocols::common::GameCommand::Stop{};
    };

    void fromProto(const protocols::common::GameCommand::Stop& stop_proto) override;
  };

  class BallPlacementMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::BallPlacement> {
   public:
    std::optional<robocin::Point2Df> position;
    std::optional<uint32_t> remaining_time; // todo(fnap): discuss what to use with duration

    explicit BallPlacementMessage(std::optional<robocin::Point2Df> position = std::nullopt,
                                  std::optional<uint32_t> remaining_time = std::nullopt);

    [[nodiscard]] protocols::common::GameCommand::BallPlacement toProto() const override {
      return protocols::common::GameCommand::BallPlacement{};
    };

    void
    fromProto(const protocols::common::GameCommand::BallPlacement& ball_placement_proto) override;
  };

  class PrepareKickoffMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::PrepareKickoff> {
   public:
    explicit PrepareKickoffMessage();

    [[nodiscard]] protocols::common::GameCommand::PrepareKickoff toProto() const override {
      return protocols::common::GameCommand::PrepareKickoff{};
    };

    void fromProto(
        const protocols::common::GameCommand::PrepareKickoff& prepare_kick_off_proto) override;
  };

  class KickoffMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::Kickoff> {
   public:
    std::optional<google::protobuf::Duration> remaining_time;

    explicit KickoffMessage(const google::protobuf::Duration& time);

    [[nodiscard]] protocols::common::GameCommand::Kickoff toProto() const override {
      return protocols::common::GameCommand::Kickoff{};
    };

    void fromProto(const protocols::common::GameCommand::Kickoff& kick_off_proto) override;
  };

  class PreparePenaltyMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::PreparePenalty> {
   public:
    explicit PreparePenaltyMessage();

    [[nodiscard]] protocols::common::GameCommand::PreparePenalty toProto() const override {
      return protocols::common::GameCommand::PreparePenalty{};
    };

    void
    fromProto(const protocols::common::GameCommand::PreparePenalty& prepare_penalty_proto) override;
  };

  class PenaltyMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::Penalty> {
   public:
    std::optional<google::protobuf::Duration> remaining_time;

    explicit PenaltyMessage(const google::protobuf::Duration& time);  

    [[nodiscard]] protocols::common::GameCommand::Penalty toProto() const override {
      return protocols::common::GameCommand::Penalty{};
    };

    void fromProto(const protocols::common::GameCommand::Penalty& penalty_proto) override;
  };

  class PrepareDirectFreeKickMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::PrepareDirectFreeKick> {
   public:
    explicit PrepareDirectFreeKickMessage();

    [[nodiscard]] protocols::common::GameCommand::PrepareDirectFreeKick toProto() const override {
      return protocols::common::GameCommand::PrepareDirectFreeKick{};
    };

    void
    fromProto(const protocols::common::GameCommand::PrepareDirectFreeKick& penalty_proto) override;
  };

  class DirectFreeKickMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::DirectFreeKick> {
   public:
    std::optional<google::protobuf::Duration> remaining_time;
    explicit DirectFreeKickMessage(const google::protobuf::Duration& time);

    [[nodiscard]] protocols::common::GameCommand::DirectFreeKick toProto() const override {
      return protocols::common::GameCommand::DirectFreeKick{};
    };

    void fromProto(
        const protocols::common::GameCommand::DirectFreeKick& direct_free_kick_proto) override;
  };

  class TimeoutMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::Timeout> {
   public:
    explicit TimeoutMessage();

    [[nodiscard]] protocols::common::GameCommand::Timeout toProto() const override {
      return protocols::common::GameCommand::Timeout{};
    };

    void fromProto(const protocols::common::GameCommand::Timeout& timeout_proto) override;
  };

  class IntervalMessage
      : public robocin::IProtoConvertible<protocols::common::GameCommand::Interval> {
   public:
    explicit IntervalMessage();

    [[nodiscard]] protocols::common::GameCommand::Interval toProto() const override {
      return protocols::common::GameCommand::Interval{};
    };

    void fromProto(const protocols::common::GameCommand::Interval& timeout_proto) override;
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

  // todo(fnap): implement
  explicit GameCommandMessage();

  [[nodiscard]] protocols::common::GameCommand toProto() const override {
    return protocols::common::GameCommand{};
  };

  void fromProto(const protocols::common::GameCommand& game_command_proto) override;
};

} // namespace decision
#endif // DECISION_PROCESSING_MESSAGES_COMMON_GAME_COMMAND_GAME_COMMAND_MESSAGE_H
