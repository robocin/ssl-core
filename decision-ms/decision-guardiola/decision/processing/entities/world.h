#ifndef DECISION_PROCESSING_ENTITIES_WORLD_H
#define DECISION_PROCESSING_ENTITIES_WORLD_H

#include "decision/processing/messages/perception/ball/ball_message.h"
#include "decision/processing/messages/perception/field/field_message.h"
#include "decision/processing/messages/perception/robot/robot_message.h"
#include "decision/processing/messages/referee/game_status_message.h"

namespace decision {

class World {
 public:
  World() = default;

  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&) noexcept = default;
  World& operator=(World&&) noexcept = default;

  virtual ~World() = default;

  std::span<RobotMessage> allies;
  std::span<RobotMessage> enemies;
  BallMessage ball;
  FieldMessage field;
  GameStatusMessage game_status; // referee

  void update(std::optional<std::span<RobotMessage>>& allies,
              std::optional<std::span<RobotMessage>>& enemies,
              std::optional<BallMessage>& ball,
              std::optional<FieldMessage>& field,
              std::optional<GameStatusMessage>& game_status);
};

} // namespace decision

#endif // DECISION_PROCESSING_ENTITIES_WORLD_H
