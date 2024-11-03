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
  this->decision.fromProto(decision);
}

void World::takeGameStatus(const protocols::referee::GameStatus& game_status) {
  this->game_status.fromProto(game_status);
}

[[nodiscard]] bool World::isAlly(const RobotMessage& robot) const {
  return (pIsYellow() && robot.robot_id->color == Color::COLOR_YELLOW)
         || (!pIsYellow() && robot.robot_id->color == Color::COLOR_BLUE);
}

void World::update(const protocols::decision::Decision& decision,
                   const std::vector<protocols::perception::Robot>& robots,
                   const std::vector<protocols::perception::Ball>& balls,
                   const protocols::referee::GameStatus& game_status) {

  World::takeDecision(decision);
  World::takeAlliesAndEnemies(robots);
  World::takeBallHighConfidence(balls);
  World::takeGameStatus(game_status);
}

} // namespace behavior
