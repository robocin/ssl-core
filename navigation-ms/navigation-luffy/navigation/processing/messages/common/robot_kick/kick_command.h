#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H

#include <protocols/common/robot_kick.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class KickCommandMessage
    : public robocin::IProtoConvertible<protocols::common::RobotKick::KickCommand> {
 public:
  KickCommandMessage();
  KickCommandMessage(double strength,
                     bool is_front,
                     bool is_chip,
                     bool charge_capacitor,
                     bool is_bypass_ir);
  explicit KickCommandMessage(const protocols::common::RobotKick::KickCommand& kick_command_proto);
  double strength;
  bool is_front;
  bool is_chip;
  bool charge_capacitor;
  bool is_bypass_ir;

  [[nodiscard]] protocols::common::RobotKick::KickCommand toProto() const override;

  void fromProto(const protocols::common::RobotKick::KickCommand& kick_command_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
