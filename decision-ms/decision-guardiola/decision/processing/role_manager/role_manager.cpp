#include "decision/processing/role_manager/role_manager.h"

#include "decision/processing/role_manager/roles/goalkeeper.h"
#include "decision/processing/role_manager/roles/irole.h"

#include <memory>
#include <vector>

namespace decision {

constexpr int kMaxPossibleCurrentRoles = 11;

RoleManager::RoleManager() { current_roles.reserve(kMaxPossibleCurrentRoles); }

void RoleManager::process() {
  current_roles.clear();
  RoleManager::chooseGoalkeeper();
  RoleManager::chooseForward();

  behavior_candidates.clear();
  for (const auto& role : current_roles) {
    // Roles calculates multiple BehaviorCandidates and suggests to manager
    std::vector<BehaviorCandidate> exec_candidates = role->exec();
    behavior_candidates.insert(behavior_candidates.end(),
                               exec_candidates.begin(),
                               exec_candidates.end());
  }
}

void RoleManager::chooseGoalkeeper() {
  // Implement heuristic to choose role
  current_roles.emplace_back(std::make_unique<GoalkeeperRole>());
}

void RoleManager::chooseForward() {
  // todo: mplement heuristic to choose forward roles
}

void RoleManager::chooseSupports() {
  // todo: implement heuristic to choose support roles
}

void RoleManager::assignRoles() {
  // Assign role to specific robotId
};

} // namespace decision
