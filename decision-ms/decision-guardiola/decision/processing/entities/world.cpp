#include "decision/processing/entities/world.h"

namespace decision {

void World::update(std::optional<std::span<RobotMessage>>& allies,
                   std::optional<std::span<RobotMessage>>& enemies,
                   std::optional<BallMessage>& ball,
                   std::optional<FieldMessage>& field) {
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
}
} // namespace decision
