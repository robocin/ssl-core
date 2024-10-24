#ifndef DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id.h"
#include "decision/processing/messages/iproto_convertible.h"
#include "decision/processing/messages/motion/motion_message.h"
#include "decision/processing/messages/planning/planning_message.h"
#include "protocols/behavior/behavior_unification.pb.h"

#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <sys/types.h>

namespace decision {

class OutputMessage : public IProtoConvertible<protocols::behavior::unification::Output> {
 public:
  explicit OutputMessage(RobotIdMessage& robot_id,
                         MotionMessage& motion,
                         PlanningMessage& planning);

  RobotIdMessage robot_id;
  MotionMessage motion;
  PlanningMessage planning;

  [[nodiscard]] protocols::behavior::unification::Output toProto() const override {
    return protocols::behavior::unification::Output{};
  };
};

class BehaviorMessage : public IProtoConvertible<protocols::behavior::unification::Behavior> {
 public:
  explicit BehaviorMessage(OutputMessage& output);
  OutputMessage output;

  [[nodiscard]] protocols::behavior::unification::Behavior toProto() const override {
    return protocols::behavior::unification::Behavior{};
  }
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
