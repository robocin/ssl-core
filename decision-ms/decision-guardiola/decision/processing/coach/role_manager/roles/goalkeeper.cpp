#include "decision/processing/coach/role_manager/roles/goalkeeper.h"

#include "decision/processing/messages/behavior/behavior_message.h"

namespace decision {
GoalkeeperRole::GoalkeeperRole(int evaluation) : evaluation_(evaluation) {}

BehaviorMessage GoalkeeperRole::chooseBehavior() {
  return BehaviorMessage{BehaviorMessage::GOALKEEPER, std::nullopt, std::nullopt};
};
} // namespace decision
