#ifndef DECISION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
#define DECISION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H

#include "decision/processing/messages/common/robot_kick/kick_command.h"
#include "decision/processing/messages/iproto_convertible.h"

#include <protocols/common/peripheral_actuation.pb.h>

namespace decision {

class PeripheralActuationMessage
    : public IProtoConvertible<protocols::common::PeripheralActuation> {
 public:
  explicit PeripheralActuationMessage(KickCommandMessage kick_command
                                      /*RobotDribblerMessage robot_dribbler*/);
  KickCommandMessage kick_command;

  [[nodiscard]] protocols::common::PeripheralActuation toProto() const override {
    return protocols::common::PeripheralActuation{};
  };
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
