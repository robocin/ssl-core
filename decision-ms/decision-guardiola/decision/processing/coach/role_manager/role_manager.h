#ifndef DECISION_PROCESSING_ROLE_MANAGER_H
#define DECISION_PROCESSING_ROLE_MANAGER_H

#include "decision/processing/entities/world.h"
#include "decision/processing/messages/perception/robot/robot_message.h"

namespace decision {
class RoleManager {
 public:
  World world;
  RobotMessage goalkeeper;
  std::vector<RobotMessage> defenders;
  std::vector<RobotMessage> supports;
  RobotMessage forward;

  explicit RoleManager(World& world);

  RoleManager(const RoleManager&) = delete;
  RoleManager& operator=(const RoleManager&) = delete;
  RoleManager(RoleManager&&) = default;
  RoleManager& operator=(RoleManager&&) = default;

  virtual ~RoleManager() = default;

  void takeGoalkeeper();
  void takeDefenders();
  void takeSupports();
  void takeForward();
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_MANAGER_H
