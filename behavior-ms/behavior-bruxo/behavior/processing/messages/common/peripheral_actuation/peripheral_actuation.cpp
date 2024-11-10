#include "behavior/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

#include "behavior/processing/messages/common/robot_kick/kick_command.h"

namespace behavior {

PeripheralActuationMessage::PeripheralActuationMessage(KickCommandMessage kick_command) :
    kick_command(std::move(kick_command)) {};

void PeripheralActuationMessage::fromProto(
    const protocols::common::PeripheralActuation& peripheral_actuation_proto) {};

protocols::common::PeripheralActuation PeripheralActuationMessage::toProto() const {
  return protocols::common::PeripheralActuation{};
};
} // namespace behavior
