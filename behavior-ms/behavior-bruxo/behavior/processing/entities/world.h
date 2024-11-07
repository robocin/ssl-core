#ifndef BEHAVIOR_PROCESSING_ENTITIES_WORLD_H
#define BEHAVIOR_PROCESSING_ENTITIES_WORLD_H

#include "behavior/processing/messages/decision/decision_message.h"
#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"
#include "behavior/processing/messages/referee/game_status_message.h"

namespace behavior {

class World {
 public:
  World() = default;

  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&) noexcept = default;
  World& operator=(World&&) noexcept = default;

  virtual ~World() = default;

  BallMessage ball;
  DecisionMessage decision;
  GameStatusMessage game_status;

  std::span<RobotMessage> allies;
  std::span<RobotMessage> enemies;

  void update(std::optional<DecisionMessage>& decision,
              std::optional<std::span<RobotMessage>>& allies,
              std::optional<std::span<RobotMessage>>& enemies,
              std::optional<BallMessage>& ball,
              std::optional<GameStatusMessage>& game_status);
};

} // namespace behavior

#endif // DECISION_PROCESSING_ENTITIES_WORLD_H
