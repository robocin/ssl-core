#ifndef DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
#define DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H

#include <protocols/common/robot_kick.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace decision {

class KickCommandMessage
    : public robocin::IProtoConvertible<protocols::common::RobotKick::KickCommand> {
 public:
  explicit KickCommandMessage(double strength,
                              bool is_front,
                              bool is_chip,
                              bool charge_capacitor,
                              bool is_bypass_ir);
  double strength;
  bool is_front;
  bool is_chip;
  bool charge_capacitor;
  bool is_bypass_ir;

  [[nodiscard]] protocols::common::RobotKick::KickCommand toProto() const override {
    return protocols::common::RobotKick::KickCommand{};
  };

  void fromProto(const protocols::common::RobotKick::KickCommand& kick_command_proto) override;
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
