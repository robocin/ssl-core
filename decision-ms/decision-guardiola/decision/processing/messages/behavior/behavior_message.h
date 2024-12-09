#ifndef DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id_message.h"
#include "decision/processing/messages/motion/motion_message.h"
#include "decision/processing/messages/planning/planning_message.h"

#include <cstdint>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <protocols/decision/decision.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>

namespace decision {

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

  void fromProto(const protocols::behavior::unification::Output& output_proto) override {};
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
  fromProto(const protocols::behavior::unification::Behavior& unification_behavior_proto) override {
  };
};

class BehaviorMessage : public robocin::IProtoConvertible<protocols::decision::Behavior> {
 public:
  enum BehaviorId {
    UNSPECIFIED = 0,
    GOALKEEPER = 1,
    LINE_GOALKEEPER = 3,
    FULL_BACK = 4,
    CENTER_BACK = 5,
    DEFENSIVE_MIDFIELDER = 6,
    OFFENSIVE_MIDFIELDER = 7,
    WINGER = 8,
    FORWARD = 9
  };

  explicit BehaviorMessage(std::optional<BehaviorId> id = std::nullopt,
                           std::optional<RobotIdMessage> robot_id = std::nullopt,
                           std::optional<robocin::Point2D<float>> target = std::nullopt);
  std::optional<BehaviorId> id;
  std::optional<RobotIdMessage> robot_id;
  std::optional<robocin::Point2D<float>> target;

  [[nodiscard]] protocols::decision::Behavior toProto() const override;

  void fromProto(const protocols::decision::Behavior& behavior_proto) override;
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
