#include "behavior/processing/messages/decision/decision_message.h"

#include <protocols/decision/decision.pb.h>

namespace behavior {

protocols::decision::Behavior::BehaviorId
getProtoBehaviorId(BehaviorDecisionMessage::BehaviorId id) {
  switch (id) {
    case BehaviorDecisionMessage::BehaviorId::UNSPECIFIED:
      return protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_UNSPECIFIED;
    case BehaviorDecisionMessage::BehaviorId::GOALKEEPER:
      return protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_GOALKEEPER;
    case BehaviorDecisionMessage::BehaviorId::FORWARD:
      return protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_FORWARD;
  }
  return protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_UNSPECIFIED;
}

BehaviorDecisionMessage::BehaviorId getBehaviorId(protocols::decision::Behavior::BehaviorId id) {
  switch (id) {
    case protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_UNSPECIFIED:
      return BehaviorDecisionMessage::BehaviorId::UNSPECIFIED;
    case protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_GOALKEEPER:
      return BehaviorDecisionMessage::BehaviorId::GOALKEEPER;
    case protocols::decision::Behavior::BehaviorId::Behavior_BehaviorId_FORWARD:
      return BehaviorDecisionMessage::BehaviorId::FORWARD;
  }
  return BehaviorDecisionMessage::BehaviorId::UNSPECIFIED;
}

BehaviorDecisionMessage::BehaviorDecisionMessage() :
    id(std::nullopt),
    robot_id(std::nullopt),
    target(std::nullopt) {}

protocols::decision::Behavior BehaviorDecisionMessage::toProto() const {
  protocols::decision::Behavior behavior_proto;

  behavior_proto.set_id(getProtoBehaviorId(id.value()));
  *behavior_proto.mutable_robot_id() = robot_id.value().toProto();
  behavior_proto.mutable_target()->set_x(target->x);
  behavior_proto.mutable_target()->set_y(target->y);

  return behavior_proto;
}

void BehaviorDecisionMessage::fromProto(const protocols::decision::Behavior& behavior_proto) {
  id = getBehaviorId(behavior_proto.id());
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

DecisionMessage::DecisionMessage(std::vector<BehaviorDecisionMessage> behavior) :
    behavior{std::move(behavior)} {}

DecisionMessage::DecisionMessage(const protocols::decision::Decision& decision) {
  fromProto(decision);
}

protocols::decision::Decision DecisionMessage::toProto() const {
  protocols::decision::Decision decision_proto;

  for (const auto& behavior_message : behavior) {
    decision_proto.add_behavior()->CopyFrom(behavior_message.toProto());
  }

  return decision_proto;
}

void DecisionMessage::fromProto(const protocols::decision::Decision& decision_proto) {
  for (const auto& behavior_proto : decision_proto.behavior()) {
    behavior.emplace_back();
    behavior.back().fromProto(behavior_proto);
  }
}

} // namespace behavior
