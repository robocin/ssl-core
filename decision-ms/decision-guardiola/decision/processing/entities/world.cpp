#include "decision/processing/entities/world.h"

#include "decision/processing/messages/referee/game_status_message.h"

namespace decision {

void World::update(std::optional<std::span<RobotMessage>>& allies,
                   std::optional<std::span<RobotMessage>>& enemies,
                   std::optional<BallMessage>& ball,
                   std::optional<FieldMessage>& field,
                   std::optional<GameStatusMessage>& game_status) {
  if (allies.has_value()) {
    this->allies = allies.value();
  }

  if (enemies.has_value()) {
    this->enemies = enemies.value();
  }

  if (ball.has_value()) {
    this->ball = std::move(ball.value());
  }

  if (field.has_value()) {
    this->field = std::move(field.value());
  }

  if (game_status.has_value()) {
    this->game_status = std::move(game_status.value());
  }
}
} // namespace decision