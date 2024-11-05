#ifndef DECISION_PROCESSING_ROLE_MANAGER_H
#define DECISION_PROCESSING_ROLE_MANAGER_H

#include "decision/processing/messages/behavior/behavior_message.h"
#include "decision/processing/role_manager/roles/irole.h"

#include <memory>
#include <vector>

namespace decision {

class RoleManager {
 public:
  std::vector<std::unique_ptr<IRole>> current_roles;
  std::vector<BehaviorCandidate> behavior_candidates;

  void process();

 private:
  void chooseGoalkeeper(std::vector<std::unique_ptr<IRole>>& processing_roles);
  void chooseSupports(std::vector<std::unique_ptr<IRole>>& processing_roles);
  void chooseForward(std::vector<std::unique_ptr<IRole>>& processing_roles);
  void assignRoles();
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_MANAGER_H
