#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_ROBOT_KICK_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_ROBOT_KICK_H

#include <optional>
#include <protocols/common/robot_kick.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class KickCommandMessage
    : public robocin::IProtoConvertible<protocols::common::RobotKick_KickCommand> {
 public:
  explicit KickCommandMessage(std::optional<double> kick_strength = std::nullopt,
                              std::optional<bool> is_front = std::nullopt,
                              std::optional<bool> is_chip = std::nullopt,
                              std::optional<bool> charge_capacitor = std::nullopt,
                              std::optional<bool> is_bypass_ir = std::nullopt);

  [[nodiscard]] protocols::common::RobotKick_KickCommand toProto() const override {
    protocols::common::RobotKick_KickCommand kick_command;
    kick_command.set_kick_strength(kick_strength.value_or(0));
    kick_command.set_is_front(is_front.value_or(false));
    kick_command.set_is_chip(is_chip.value_or(false));
    kick_command.set_charge_capacitor(charge_capacitor.value_or(false));
    kick_command.set_is_bypass_ir(is_bypass_ir.value_or(false));

    return kick_command;
  };

  void fromProto(protocols::common::RobotKick_KickCommand kick_command) override {
    kick_strength = kick_command.kick_strength();
    is_front = kick_command.is_front();
    is_chip = kick_command.is_chip();
    charge_capacitor = kick_command.charge_capacitor();
    is_bypass_ir = kick_command.is_bypass_ir();
  };

  std::optional<double> kick_strength;
  std::optional<bool> is_front;
  std::optional<bool> is_chip;
  std::optional<bool> charge_capacitor;
  std::optional<bool> is_bypass_ir;
};

class RobotKickMessage : public robocin::IProtoConvertible<protocols::common::RobotKick> {
 public:
  explicit RobotKickMessage(KickCommandMessage kick_command = KickCommandMessage{});

  [[nodiscard]] protocols::common::RobotKick toProto() const override {
    protocols::common::RobotKick robot_kick;
    robot_kick.mutable_kick_command()->CopyFrom(kick_command.toProto());
    return robot_kick;
  };

  void fromProto(protocols::common::RobotKick robot_kick) override {};

  KickCommandMessage kick_command;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_ROBOT_KICK_H
