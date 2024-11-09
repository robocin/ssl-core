#ifndef DECISION_PROCESSING_ROLE_MANAGER_ROLES_GOALKEEPER_H
#define DECISION_PROCESSING_ROLE_MANAGER_ROLES_GOALKEEPER_H

#include "decision/processing/messages/behavior/behavior_message.h"
#include "decision/processing/role_manager/roles/irole.h"

namespace decision {
class GoalkeeperRole : public IRole {
 public:
  explicit GoalkeeperRole() = default;

  std::vector<BehaviorCandidate> exec() override;

 private:
  int evaluation_;
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_MANAGER_ROLES_GOALKEEPER_H
