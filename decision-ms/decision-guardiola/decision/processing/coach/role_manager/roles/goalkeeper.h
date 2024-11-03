#ifndef DECISION_PROCESSING_ROLE_MANAGER_ROLES_GOALKEEPER_H
#define DECISION_PROCESSING_ROLE_MANAGER_ROLES_GOALKEEPER_H

#include "decision/processing/messages/behavior/behavior_message.h"

namespace decision {
class GoalkeeperRole {
 public:
  explicit GoalkeeperRole(int evaluation);
  ~GoalkeeperRole();

  BehaviorMessage chooseBehavior();

 private:
  int evaluation_;
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_MANAGER_ROLES_GOALKEEPER_H
