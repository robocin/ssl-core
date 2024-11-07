#include "behavior/processing/entities/world.h"

namespace behavior {

void World::update(std::optional<DecisionMessage>& decision,
                   std::optional<std::span<RobotMessage>>& allies,
                   std::optional<std::span<RobotMessage>>& enemies,
                   std::optional<BallMessage>& ball,
                   std::optional<GameStatusMessage>& game_status) {

  if (decision.has_value()) {
    this->decision = std::move(decision.value());
  }

  if (allies.has_value()) {
    this->allies = allies.value();
  }

  if (enemies.has_value()) {
    this->enemies = enemies.value();
  }

  if (ball.has_value()) {
    this->ball = std::move(ball.value());
  }

  if (game_status.has_value()) {
    this->game_status = std::move(game_status.value());
  }
}

} // namespace behavior
