#ifndef DECISION_PROCESSING_ROLE_MANAGER_H
#define DECISION_PROCESSING_ROLE_MANAGER_H

#include "decision/processing/coach/role_manager/roles/goalkeeper.h"
#include "decision/processing/entities/world.h"
#include "decision/processing/messages/perception/robot/robot_message.h"

namespace decision {
class RoleManager {
 public:
  GoalkeeperRole goalkeeper_role{1};
  // std::vector<RobotMessage> center_backs;
  // std::vector<RobotMessage> full_backs;
  // std::vector<RobotMessage> defensive_midfielders;
  // std::vector<RobotMessage> offensive_midfielders;
  // std::vector<RobotMessage> wingers;
  // std::vector<RobotMessage> forwards;

  explicit RoleManager() = default;

  void chooseGoalkeeper();
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_MANAGER_H
