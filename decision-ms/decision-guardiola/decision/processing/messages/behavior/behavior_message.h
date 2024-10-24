#ifndef DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id.h"
#include "decision/processing/messages/iproto_convertible.h"
#include "decision/processing/messages/motion/motion_message.h"
#include "decision/processing/messages/planning/planning_message.h"

#include <cstdint>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <protocols/decision/decision.pb.h>
#include <robocin/geometry/point2d.h>
#include <sys/types.h>

namespace decision {

class OutputMessage : public IProtoConvertible<protocols::behavior::unification::Output> {
 public:
  OutputMessage(RobotIdMessage robot_id = RobotIdMessage{},
                MotionMessage motion = MotionMessage{},
                PlanningMessage planning = PlanningMessage{});

  RobotIdMessage robot_id;
  MotionMessage motion;
  PlanningMessage planning;

  [[nodiscard]] protocols::behavior::unification::Output toProto() const override {
    return protocols::behavior::unification::Output{};
  };
};

class BehaviorUnificationMessage
    : public IProtoConvertible<protocols::behavior::unification::Behavior> {
 public:
  BehaviorUnificationMessage(OutputMessage output = OutputMessage{});
  OutputMessage output;

  [[nodiscard]] protocols::behavior::unification::Behavior toProto() const override {
    return protocols::behavior::unification::Behavior{};
  }
};

class BehaviorMessage : public IProtoConvertible<protocols::decision::Behavior> {
 public:
  BehaviorMessage(std::optional<uint32_t> id = std::nullopt,
                  std::optional<RobotIdMessage> robot_id = std::nullopt,
                  std::optional<robocin::Point2D<float>> target = std::nullopt);
  std::optional<uint32_t> id;
  std::optional<RobotIdMessage> robot_id;
  std::optional<robocin::Point2D<float>> target;

  [[nodiscard]] protocols::decision::Behavior toProto() const override {
    return protocols::decision::Behavior{};
  }
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
