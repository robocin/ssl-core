#include "behavior/processing/messages/behavior/behavior_message.h"

namespace behavior {

// OutputMessage
OutputMessage::OutputMessage(RobotIdMessage robot_id,
                             MotionMessage motion,
                             PlanningMessage planning) :
    robot_id{std::move(robot_id)},
    motion{std::move(motion)},
    planning{std::move(planning)} {}

protocols::behavior::unification::Output OutputMessage::toProto() const {
  protocols::behavior::unification::Output output;
  output.mutable_robot_id()->CopyFrom(robot_id.toProto());
  output.mutable_motion()->CopyFrom(motion.toProto());
  output.mutable_planning()->CopyFrom(planning.toProto());
  return output;
}

void OutputMessage::fromProto(const protocols::behavior::unification::Output& output) {
  robot_id.fromProto(output.robot_id());
  motion.fromProto(output.motion());
  planning.fromProto(output.planning());
}

// BehaviorMessage
BehaviorMessage::BehaviorMessage(std::vector<OutputMessage> output) : output{std::move(output)} {}

protocols::behavior::unification::Behavior BehaviorMessage::toProto() const {
  protocols::behavior::unification::Behavior behavior;
  for (const auto& output_message : output) {
    behavior.add_output()->CopyFrom(output_message.toProto());
  }
  return behavior;
}

void BehaviorMessage::fromProto(const protocols::behavior::unification::Behavior& behavior) {
  // TODO: Implement this function
}

} // namespace behavior
