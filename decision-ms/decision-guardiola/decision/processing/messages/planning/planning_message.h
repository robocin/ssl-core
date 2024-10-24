#ifndef DECISION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H

#include "decision/processing/messages/iproto_convertible.h"

#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <sys/types.h>

namespace decision {
class PlanningMessage : public IProtoConvertible<protocols::behavior::Planning> {
 public:
  PlanningMessage();

  [[nodiscard]] protocols::behavior::Planning toProto() const override {
    return protocols::behavior::Planning{};
  };
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
