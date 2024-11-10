#include "behavior/processing/messages/common/peripheral_actuation/peripheral_actuation.h"

namespace behavior {

void PeripheralActuationMessage::fromProto(
    const protocols::common::PeripheralActuation& peripheral_actuation_proto) {};

protocols::common::PeripheralActuation PeripheralActuationMessage::toProto() const {
  return protocols::common::PeripheralActuation{};
};
} // namespace behavior
