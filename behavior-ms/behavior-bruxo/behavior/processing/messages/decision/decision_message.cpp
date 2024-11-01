#include "behavior/processing/messages/decision/decision_message.h"

namespace behavior {

BehaviorMessage::BehaviorMessage() :
    id(std::nullopt),
    robot_id(std::nullopt),
    target(std::nullopt) {}

protocols::decision::Behavior BehaviorMessage::toProto() const {
  protocols::decision::Behavior behavior_proto;

  behavior_proto.set_id(id.value_or(0));
  *behavior_proto.mutable_robot_id() = robot_id.value().toProto();
  behavior_proto.mutable_target()->set_x(target->x);
  behavior_proto.mutable_target()->set_y(target->y);

  return behavior_proto;
}

void BehaviorMessage::fromProto(const protocols::decision::Behavior& behavior_proto) {
  id = behavior_proto.id();
  if (behavior_proto.has_robot_id()) {
    robot_id = RobotIdMessage{};
    robot_id->fromProto(behavior_proto.robot_id());
  }
  if (behavior_proto.has_target()) {
    target = robocin::Point2Df{};
    target->x = behavior_proto.target().x();
    target->y = behavior_proto.target().y();
  }
}

DecisionMessage::DecisionMessage(std::vector<BehaviorMessage> behavior) :
    behavior{std::move(behavior)} {}

protocols::decision::Decision DecisionMessage::toProto() const {
  protocols::decision::Decision decision_proto;

  for (const auto& behavior_message : behavior) {
    decision_proto.add_behavior()->CopyFrom(behavior_message.toProto());
  }

  return decision_proto;
}

void DecisionMessage::fromProto(const protocols::decision::Decision& decision_proto) {}

} // namespace behavior
