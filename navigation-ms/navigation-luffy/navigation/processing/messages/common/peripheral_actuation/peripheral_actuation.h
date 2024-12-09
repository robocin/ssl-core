#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H

#include "navigation/processing/messages/common/robot_dribbler/robot_dribbler_message.h"
#include "navigation/processing/messages/common/robot_kick/kick_command.h"

#include <optional>
#include <protocols/common/peripheral_actuation.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class PeripheralActuationMessage
    : public robocin::IProtoConvertible<protocols::common::PeripheralActuation> {
 public:
  std::optional<KickCommandMessage> kick_command;
  std::optional<RobotDribblerMessage> robot_dribbler;

  explicit PeripheralActuationMessage(std::optional<KickCommandMessage> kick_command = std::nullopt,
                                      std::optional<RobotDribblerMessage> robot_dribbler
                                      = std::nullopt);
  explicit PeripheralActuationMessage(
      const protocols::common::PeripheralActuation& peripheral_actuation_proto);

  [[nodiscard]] protocols::common::PeripheralActuation toProto() const override;

  void fromProto(const protocols::common::PeripheralActuation& peripheral_actuation_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_PERIPHERAL_ACTUATION_PERIPHERAL_ACTUATION_H
