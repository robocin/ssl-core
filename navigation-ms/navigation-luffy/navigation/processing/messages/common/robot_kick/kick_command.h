#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H

#include <optional>
#include <protocols/common/robot_kick.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class KickCommandMessage
    : public robocin::IProtoConvertible<protocols::common::RobotKick::KickCommand> {
 public:
  KickCommandMessage();
  KickCommandMessage(std::optional<double> strength = std::nullopt,
                     std::optional<bool> is_front = std::nullopt,
                     std::optional<bool> is_chip = std::nullopt,
                     std::optional<bool> charge_capacitor = std::nullopt,
                     std::optional<bool> is_bypass_ir = std::nullopt);
  explicit KickCommandMessage(const protocols::common::RobotKick::KickCommand& kick_command_proto);
  std::optional<double> strength;
  std::optional<bool> is_front;
  std::optional<bool> is_chip;
  std::optional<bool> charge_capacitor;
  std::optional<bool> is_bypass_ir;

  [[nodiscard]] protocols::common::RobotKick::KickCommand toProto() const override;

  void fromProto(const protocols::common::RobotKick::KickCommand& kick_command_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
