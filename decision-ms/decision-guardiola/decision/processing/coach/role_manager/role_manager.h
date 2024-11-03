#ifndef DECISION_PROCESSING_ROLE_MANAGER_H
#define DECISION_PROCESSING_ROLE_MANAGER_H

#include "decision/processing/entities/world.h"
#include "decision/processing/messages/perception/robot/robot_message.h"

namespace decision {
class RoleManager {
 public:
  World world;
  RobotMessage goalkeeper;
  std::vector<RobotMessage> center_backs;
  std::vector<RobotMessage> full_backs;
  std::vector<RobotMessage> defensive_midfielders;
  std::vector<RobotMessage> offensive_midfielders;
  std::vector<RobotMessage> wingers;
  std::vector<RobotMessage> forwards;

  explicit RoleManager(World& world);

  RoleManager(const RoleManager&) = delete;
  RoleManager& operator=(const RoleManager&) = delete;
  RoleManager(RoleManager&&) = default;
  RoleManager& operator=(RoleManager&&) = default;

  virtual ~RoleManager() = default;

  void chooseGoalkeeper();
  void chooseCentralBacks();
  void chooseFullBacks();
  void chooseDefensiveMidfielders();
  void chooseAttackingMidfielders();
  void chooseWingers();
  void chooseForwards();
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_MANAGER_H
