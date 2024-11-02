#ifndef DECISION_PROCESSING_ROLE_ALLOCATOR_H
#define DECISION_PROCESSING_ROLE_ALLOCATOR_H

#include "decision/processing/entities/world.h"
#include "decision/processing/messages/perception/robot/robot_message.h"

namespace decision {
class RoleAllocator {
 public:
  World world;
  RobotMessage goalkeeper;
  std::vector<RobotMessage> central_backs;
  std::vector<RobotMessage> full_backs;
  std::vector<RobotMessage> defensive_midfielders;
  std::vector<RobotMessage> offensive_midfielders;
  std::vector<RobotMessage> wingers;
  std::vector<RobotMessage> forwards;

  explicit RoleAllocator(World& world);

  RoleAllocator(const RoleAllocator&) = delete;
  RoleAllocator& operator=(const RoleAllocator&) = delete;
  RoleAllocator(RoleAllocator&&) = default;
  RoleAllocator& operator=(RoleAllocator&&) = default;

  virtual ~RoleAllocator() = default;

  void chooseGoalkeeper();
  void chooseCentralBacks();
  void chooseFullBacks();
  void chooseDefensiveMidfielders();
  void chooseAttackingMidfielders();
  void chooseWingers();
  void chooseForwards();
};
} // namespace decision

#endif // DECISION_PROCESSING_ROLE_ALLOCATOR_H
