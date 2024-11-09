#include "navigation/processing/messages/planning/planning_message.h"

#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"
#include "navigation/processing/messages/motion/motion_message.h"

namespace navigation {
PlanningMessage::PlanningMessage(DiscretizedPathMessage discretized_path,
                                 GoToPointMessage go_to_point,
                                 RotateInPointMessage rotate_in_point,
                                 RotateOnSelfMessage rotate_on_self,
                                 PeripheralActuationMessage peripheral_actuation) :
    discretized_path(std::move(discretized_path)),
    go_to_point(std::move(go_to_point)),
    rotate_in_point(std::move(rotate_in_point)),
    rotate_on_self(std::move(rotate_on_self)),
    peripheral_actuation(std::move(peripheral_actuation)) {}

PlanningMessage::PlanningMessage(const protocols::behavior::Planning& planning_proto) {
  PlanningMessage::fromProto(planning_proto);
}

protocols::behavior::Planning PlanningMessage::toProto() const {
  return protocols::behavior::Planning{};
};

void PlanningMessage::fromProto(const protocols::behavior::Planning& planning_proto) {
  discretized_path = DiscretizedPathMessage(planning_proto.discretized_path());
  go_to_point = GoToPointMessage(planning_proto.go_to_point());
  rotate_in_point = RotateInPointMessage(planning_proto.rotate_in_point());
  rotate_on_self = RotateOnSelfMessage(planning_proto.rotate_on_self());
  peripheral_actuation = PeripheralActuationMessage(planning_proto.peripheral_actuation());
}
} // namespace navigation
