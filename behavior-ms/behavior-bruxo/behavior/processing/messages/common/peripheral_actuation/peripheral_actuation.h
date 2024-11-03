#ifndef BEHAVIOR_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
#define BEHAVIOR_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H

#include "behavior/processing/messages/common/robot_kick/kick_command.h"

#include <protocols/common/peripheral_actuation.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

class PeripheralActuationMessage
    : public robocin::IProtoConvertible<protocols::common::PeripheralActuation> {
 public:
  explicit PeripheralActuationMessage(KickCommandMessage kick_command
                                      /*RobotDribblerMessage robot_dribbler*/);
  KickCommandMessage kick_command;

  [[nodiscard]] protocols::common::PeripheralActuation toProto() const override {
    return protocols::common::PeripheralActuation{};
  };
};
} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
