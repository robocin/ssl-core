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

  [[nodiscard]] protocols::common::RobotKick_KickCommand toProto() const override;

  void fromProto(const protocols::common::RobotKick_KickCommand& kick_command) override;

  std::optional<double> kick_strength;
  std::optional<bool> is_front;
  std::optional<bool> is_chip;
  std::optional<bool> charge_capacitor;
  std::optional<bool> is_bypass_ir;
};

class RobotKickMessage : public robocin::IProtoConvertible<protocols::common::RobotKick> {
 public:
  explicit RobotKickMessage(KickCommandMessage kick_command = KickCommandMessage{});

  [[nodiscard]] protocols::common::RobotKick toProto() const override;

  void fromProto(const protocols::common::RobotKick& robot_kick) override;

  KickCommandMessage kick_command;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_ROBOT_KICK_H
