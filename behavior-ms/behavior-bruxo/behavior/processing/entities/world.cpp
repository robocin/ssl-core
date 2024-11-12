#include "behavior/processing/entities/world.h"

#include "world.h"

#include <protocols/common/robot_id.pb.h>
#include <protocols/perception/detection.pb.h>
#include <vector>

namespace behavior {

void World::takeBallHighConfidence(const std::vector<protocols::perception::Ball>& balls) {
  if (balls.empty()) {
    return;
  }

  auto max_ball
      = std::max_element(balls.begin(), balls.end(), [](const auto& ball, const auto& candidate) {
          return ball.confidence() < candidate.confidence();
        });

  this->ball.fromProto(*max_ball);
}

void World::takeAlliesAndEnemies(const std::vector<protocols::perception::Robot>& robots) {
  if (robots.empty()) {
    return;
  }

  allies.clear();
  enemies.clear();

  for (const auto& robot : robots) {
    RobotMessage robot_message;
    robot_message.fromProto(robot);

    if (isAlly(robot_message)) {
      this->allies.emplace_back(std::move(robot_message));
    } else {
      this->enemies.emplace_back(std::move(robot_message));
    }
  }
}

void World::takeDecision(const protocols::decision::Decision& decision) {
  // Reimplement when we listen to decision
  return;
  this->decision.fromProto(decision);
}

void World::takeGameStatus(const protocols::referee::GameStatus& game_status) {
  this->game_status.fromProto(game_status);
}

bool World::isAlly(const RobotMessage& robot) const { return robot.robot_id->color == pAllyColor; }

void World::takeField(const protocols::perception::Field& field) { this->field.fromProto(field); }

void World::update(const std::vector<protocols::perception::Robot>& robots,
                   const std::vector<protocols::perception::Ball>& balls,
                   const protocols::perception::Field& field,
                   const protocols::referee::GameStatus& game_status) {

  World::takeAlliesAndEnemies(robots);
  World::takeBallHighConfidence(balls);
  World::takeGameStatus(game_status);
}

bool World::isStop() { return game_status.command->stop.has_value(); }

bool World::isHalt() { return game_status.command->halt.has_value(); }

bool World::isInGame() { return game_status.command->in_game.has_value(); }

bool World::isTimeout() {
  return game_status.command->away_timeout.has_value()
         || game_status.command->home_timeout.has_value();
}

bool World::isInterval() { return game_status.command->interval.has_value(); }

bool World::isPenalty() {
  return game_status.command->away_penalty.has_value()
         || game_status.command->home_penalty.has_value()
         || game_status.command->away_prepare_penalty.has_value()
         || game_status.command->home_prepare_penalty.has_value();
}

bool World::isDirectFreeKick() {
  return game_status.command->home_direct_free_kick.has_value()
         || game_status.command->away_direct_free_kick.has_value()
         || game_status.command->away_prepare_direct_free_kick.has_value()
         || game_status.command->home_prepare_direct_free_kick.has_value();
}

} // namespace behavior
