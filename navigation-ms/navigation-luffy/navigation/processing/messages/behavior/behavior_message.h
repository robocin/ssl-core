#ifndef NAVIGATION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
#define NAVIGATION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H

#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/planning/planning_message.h"

#include <cstdint>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <protocols/decision/decision.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>

namespace navigation {

class OutputMessage : public robocin::IProtoConvertible<protocols::behavior::unification::Output> {
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

  void fromProto(const protocols::behavior::unification::Output& output_proto) override;
};

class BehaviorUnificationMessage
    : public robocin::IProtoConvertible<protocols::behavior::unification::Behavior> {
 public:
  BehaviorUnificationMessage(OutputMessage output = OutputMessage{});
  OutputMessage output;

  [[nodiscard]] protocols::behavior::unification::Behavior toProto() const override {
    return protocols::behavior::unification::Behavior{};
  }

  void
  fromProto(const protocols::behavior::unification::Behavior& unification_behavior_proto) override;
};

class BehaviorMessage : public robocin::IProtoConvertible<protocols::decision::Behavior> {
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

  void fromProto(const protocols::decision::Behavior& behavior_proto) override;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
