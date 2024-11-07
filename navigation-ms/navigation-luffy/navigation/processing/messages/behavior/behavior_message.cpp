#include "navigation/processing/messages/behavior/behavior_message.h"

#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/planning/planning_message.h"

#include <algorithm>
#include <protocols/behavior/behavior_unification.pb.h>
#include <utility>

namespace navigation {
BehaviorUnificationMessage::BehaviorUnificationMessage(
    const protocols::behavior::unification::Behavior& unification_behavior_proto) {
  BehaviorUnificationMessage::fromProto(unification_behavior_proto);
}
void BehaviorUnificationMessage::fromProto(
    const protocols::behavior::unification::Behavior& unification_behavior_proto) {
  for (const protocols::behavior::unification::Output& output :
       unification_behavior_proto.output()) {
    behavior_outputs.emplace_back(RobotIdMessage(output.robot_id()),
                                  MotionMessage(output.motion()),
                                  PlanningMessage(output.planning()));
  }
}
OutputMessage::OutputMessage(const protocols::behavior::unification::Output& output_proto) {
  OutputMessage::fromProto(output_proto);
}

OutputMessage::OutputMessage(std::optional<RobotIdMessage> robot_id,
                             std::optional<MotionMessage> motion,
                             std::optional<PlanningMessage> planning) :
    robot_id(std::move(robot_id)),
    motion(std::move(motion)),
    planning(std::move(planning)) {}

void OutputMessage::fromProto(const protocols::behavior::unification::Output& output_proto) {
  robot_id = RobotIdMessage(output_proto.robot_id());
  motion = MotionMessage(output_proto.motion());
  planning = PlanningMessage(output_proto.planning());
}
BehaviorMessage::BehaviorMessage(std::optional<uint32_t> id,
                                 std::optional<RobotIdMessage> robot_id,
                                 std::optional<robocin::Point2D<float>> target) :
    id(id),
    robot_id(std::move(robot_id)),
    target(target) {}

} // namespace navigation
