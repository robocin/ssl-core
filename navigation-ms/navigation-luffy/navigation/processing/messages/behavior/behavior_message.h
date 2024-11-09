#ifndef NAVIGATION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
#define NAVIGATION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H

#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/planning/planning_message.h"

#include <cstdint>
#include <optional>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>
#include <vector>

namespace navigation {

class OutputMessage : public robocin::IProtoConvertible<protocols::behavior::unification::Output> {
 public:
 
  OutputMessage(std::optional<RobotIdMessage> robot_id = std::nullopt,
                std::optional<MotionMessage> motion = std::nullopt,
                std::optional<PlanningMessage> planning = std::nullopt);
  explicit OutputMessage(const protocols::behavior::unification::Output& output_proto);

  std::optional<RobotIdMessage> robot_id;
  std::optional<MotionMessage> motion;
  std::optional<PlanningMessage> planning;

  [[nodiscard]] protocols::behavior::unification::Output toProto() const override {
    return protocols::behavior::unification::Output{};
  };

  void fromProto(const protocols::behavior::unification::Output& output_proto) override;
};

class BehaviorUnificationMessage
    : public robocin::IProtoConvertible<protocols::behavior::unification::Behavior> {
 public:
  explicit BehaviorUnificationMessage(
      const protocols::behavior::unification::Behavior& unification_behavior_proto);

  std::vector<OutputMessage> behavior_outputs;

  [[nodiscard]] protocols::behavior::unification::Behavior toProto() const override {
    return protocols::behavior::unification::Behavior{};
  }

  void
  fromProto(const protocols::behavior::unification::Behavior& unification_behavior_proto) override;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
