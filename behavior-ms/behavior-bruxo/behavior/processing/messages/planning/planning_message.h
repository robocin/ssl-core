#ifndef BEHAVIOR_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H

#include <protocols/behavior/planning.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {
class PlanningMessage : public robocin::IProtoConvertible<protocols::behavior::Planning> {
 public:
  PlanningMessage() {};

  [[nodiscard]] protocols::behavior::Planning toProto() const override {
    protocols::behavior::Planning planning;
    return planning;
  };

  void fromProto(const protocols::behavior::Planning& planning) override {
    // Implementação específica para converter de proto para RobotIdMessage
  };
};

} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
