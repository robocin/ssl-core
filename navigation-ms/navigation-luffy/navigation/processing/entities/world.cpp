#include "navigation/processing/entities/world.h"

#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/perception/ball/ball_message.h"
#include "navigation/processing/messages/perception/field/field_message.h"
#include "navigation/processing/messages/perception/robot/robot_message.h"
#include "navigation/processing/messages/planning/planning_message.h"
#include "navigation/processing/messages/referee/game_status_message.h"
#include "world.h"

#include <optional>
#include <protocols/common/robot_id.pb.h>
#include <protocols/perception/detection.pb.h>
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

  this->ally_color = behavior.robot_id->color.value();

  this->allies.clear();
  this->enemies.clear();

  for (auto& robot_perception : robots) {

    if (robot_perception.robot_id->number == behavior.robot_id->number
        && isAlly(robot_perception)) {
      this->ally = std::move(robot_perception);
    } else if (isAlly(robot_perception)) {
      this->allies.emplace_back(std::move(robot_perception));
    } else {
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

} // namespace navigation
