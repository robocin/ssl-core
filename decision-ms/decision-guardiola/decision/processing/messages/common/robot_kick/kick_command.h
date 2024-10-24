#ifndef DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
#define DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H

#include "decision/processing/messages/iproto_convertible.h"

#include <protocols/common/robot_kick.pb.h>

namespace decision {

class KickCommandMessage : public IProtoConvertible<protocols::common::RobotKick::KickCommand> {
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
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_ROBOT_KICK_KICK_COMMAND_H
