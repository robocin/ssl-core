#include "decision/processing/role_manager/roles/goalkeeper.h"

#include "decision/processing/messages/behavior/behavior_message.h"
#include "decision/processing/role_manager/roles/irole.h"

namespace decision {

std::vector<BehaviorCandidate> GoalkeeperRole::exec() {
  return {BehaviorCandidate{BehaviorMessage::BehaviorId::GOALKEEPER, 1}};
};
} // namespace decision
