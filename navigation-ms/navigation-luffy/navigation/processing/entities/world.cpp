#include "navigation/processing/entities/world.h"

#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/perception/ball/ball_message.h"
#include "navigation/processing/messages/perception/field/field_message.h"
#include "navigation/processing/messages/perception/robot/robot_message.h"
#include "navigation/processing/messages/referee/game_status_message.h"
#include "world.h"

#include <cstdint>
#include <optional>
#include <protocols/common/robot_id.pb.h>
#include <protocols/perception/detection.pb.h>
#include <utility>
#include <vector>

namespace navigation {

void World::takeBallHighConfidence(std::vector<BallMessage>& balls) {
  if (balls.empty()) {
    return;
  }

  auto max_ball = std::max_element(balls.begin(), balls.end(), [](auto& ball, auto& candidate) {
    return ball.confidence < candidate.confidence;
  });

  this->ball = std::move(*max_ball);
}

void World::takeRobotsData(OutputMessage& behavior, std::vector<RobotMessage>& robots) {
  if (robots.empty()) {
    return;
  }

  this->robot_motion = std::nullopt;
  if (behavior.motion) {
    this->robot_motion = std::move(behavior.motion.value());
  }

  this->robot_planning = std::nullopt;
  if (behavior.planning) {
    this->robot_planning = std::move(behavior.planning.value());
  }

  this->allies.emplace_back(std::move(current_ally));
  this->ally_color = behavior.robot_id->color.value();
  this->enemies.clear();

  for (auto& robot_perception : robots) {

    auto it = findAllyById(robot_perception.robot_id->number);
    if (isAlly(robot_perception)) { // robot is an ally

      if (robot_perception.robot_id->number == behavior.robot_id->number) { // found current_ally
        if (it != this->allies.end()) {
          Ally& ally = *it;
          ally.update(robot_perception);
          this->current_ally = std::move(ally);
          this->allies.erase(it); // Remove current_ally from allies
        } else {
          this->current_ally = Ally(std::move(robot_perception));
        }
      } else { // other allies
        if (it != this->allies.end()) {
          it->update(robot_perception);
        } else {
          this->allies.emplace_back(std::move(robot_perception));
        }
      }

    } else {                          // robot is an enemy
      if (it != this->allies.end()) { // but was previously an ally
        this->allies.erase(it);
      }
      this->enemies.emplace_back(std::move(robot_perception));
    }
  }
}

void World::takeGameStatus(GameStatusMessage& game_status) {
  this->game_status = std::move(game_status);
}

bool World::isAlly(const RobotMessage& robot) const { return robot.robot_id->color == ally_color; }

void World::takeField(FieldMessage& field) { this->field = std::move(field); }

void World::update(OutputMessage& behavior,
                   std::vector<RobotMessage>& robots,
                   std::vector<BallMessage>& balls,
                   FieldMessage& field,
                   GameStatusMessage& game_status) {

  World::takeRobotsData(behavior, robots);
  World::takeBallHighConfidence(balls);
  World::takeGameStatus(game_status);
  World::takeField(field);
}

std::vector<Ally>::iterator World::findAllyById(uint32_t id) {
  return std::find_if(this->allies.begin(), this->allies.end(), [id](const Ally& ally) {
    return ally.robot_id->number == id;
  });
}

} // namespace navigation
