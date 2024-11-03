#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H

#include "navigation/processing/messages/common/robot_kick/kick_command.h"

#include <protocols/common/peripheral_actuation.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

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
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
