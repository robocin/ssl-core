#include "behavior/processing/entities/world.h"

#include <robocin/output/log.h>

namespace behavior {

namespace {
using robocin::ilog;
} // namespace

void World::update(std::optional<DecisionMessage>& decision,
                   std::optional<std::span<RobotMessage>>& robots,
                   std::optional<BallMessage>& ball) {

  if (decision.has_value()) {
    this->decision = std::move(decision.value());
  }

  if (robots.has_value()) {
    // TODO(ersa): implement the logic to separate allies and enemies
    this->allies = robots.value();
  }

  // if (enemies.has_value()) {
  //   this->enemies = enemies.value();
  // }

  if (ball.has_value()) {
    this->ball = std::move(ball.value());
  }

  // if (game_status.has_value()) {
  //   this->game_status = std::move(game_status.value());
  // }
}

} // namespace behavior
