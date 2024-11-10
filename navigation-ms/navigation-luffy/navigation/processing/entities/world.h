#ifndef BEHAVIOR_PROCESSING_ENTITIES_WORLD_H
#define BEHAVIOR_PROCESSING_ENTITIES_WORLD_H

#include "navigation/parameters/parameters.h"
#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/perception/ball/ball_message.h"
#include "navigation/processing/messages/perception/field/field_message.h"
#include "navigation/processing/messages/perception/robot/robot_message.h"
#include "navigation/processing/messages/planning/planning_message.h"
#include "navigation/processing/messages/referee/game_status_message.h"

#include <optional>
#include <vector>

namespace navigation {

class World {
 public:
  World() = default;

  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&) noexcept = default;
  World& operator=(World&&) noexcept = default;

  virtual ~World() = default;

  BallMessage ball;
  FieldMessage field;
  GameStatusMessage game_status;
  std::optional<MotionMessage> robot_motion;
  std::optional<PlanningMessage> robot_planning;
  RobotMessage ally;

  std::vector<RobotMessage> allies;
  std::vector<RobotMessage> enemies;
  RobotIdMessage::Color ally_color;

  void update(OutputMessage& behavior,
              std::vector<RobotMessage>& robots,
              std::vector<BallMessage>& balls,
              FieldMessage& field,
              GameStatusMessage& game_status);

 private:
  void takeBallHighConfidence(std::vector<BallMessage>& balls);
  void takeRobotsData(OutputMessage& behavior, std::vector<RobotMessage>& robots);
  void takeGameStatus(GameStatusMessage& game_status);
  void takeField(FieldMessage& field);

  [[nodiscard]] bool isAlly(const RobotMessage& robot) const;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_ENTITIES_WORLD_H
