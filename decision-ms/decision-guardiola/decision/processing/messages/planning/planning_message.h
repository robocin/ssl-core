#ifndef DECISION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H

#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>

namespace decision {
class PlanningMessage : public robocin::IProtoConvertible<protocols::behavior::Planning> {
 public:
  PlanningMessage();

  [[nodiscard]] protocols::behavior::Planning toProto() const override {
    return protocols::behavior::Planning{};
  };

  void fromProto(const protocols::behavior::Planning& planning_proto) override;
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
