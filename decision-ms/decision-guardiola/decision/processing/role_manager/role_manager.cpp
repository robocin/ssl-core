#include "decision/processing/role_manager/role_manager.h"

#include "decision/processing/role_manager/roles/goalkeeper.h"
#include "decision/processing/role_manager/roles/irole.h"

#include <memory>
#include <vector>

namespace decision {

constexpr int kMaxPossibleCurrentRoles = 11;

void RoleManager::process() {
  std::vector<std::unique_ptr<IRole>> roles;
  roles.reserve(kMaxPossibleCurrentRoles);

  RoleManager::chooseGoalkeeper(roles);
  RoleManager::chooseForward(roles);

  behavior_candidates.clear();
  for (const auto& role : roles) {
    // Roles calculates multiple BehaviorCandidates and suggests to manager
    std::vector<BehaviorCandidate> exec_candidates = role->exec();
    behavior_candidates.insert(behavior_candidates.end(),
                               exec_candidates.begin(),
                               exec_candidates.end());
  }
}

void RoleManager::chooseGoalkeeper(std::vector<std::unique_ptr<IRole>>& processing_roles) {
  // Implement heuristic to choose role
  processing_roles.emplace_back(std::make_unique<GoalkeeperRole>());
}

void RoleManager::chooseForward(std::vector<std::unique_ptr<IRole>>& processing_roles) {
  // Implement heuristic to choose role
}

void RoleManager::assignRoles() {
  // Assign role to specific robotId
};

} // namespace decision
