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

void World::takeBallHighConfidence(const std::vector<BallMessage>& balls) {
  if (balls.empty()) {
    return;
  }

  auto max_ball
      = std::max_element(balls.begin(), balls.end(), [](const auto& ball, const auto& candidate) {
          return ball.confidence < candidate.confidence;
        });

  this->ball = std::move(BallMessage{*max_ball});
}

void World::takeRobotsData(const OutputMessage& behavior, const std::vector<RobotMessage>& robots) {
  if (robots.empty()) {
    return;
  }

  this->robot_motion = std::nullopt;
  if (behavior.motion) {
    this->robot_motion = MotionMessage(behavior.motion.value());
  }

  this->robot_planning = std::nullopt;
  if (behavior.planning) {
    this->robot_planning = PlanningMessage(behavior.planning.value());
  }

  this->ally_color = behavior.robot_id.value().color.value();

  allies.clear();
  enemies.clear();

  for (const auto& robot : robots) {
    RobotMessage robot_message(robot);

    if (robot.robot_id->number == behavior.robot_id->number && isAlly(robot_message)) {
      this->robot = RobotMessage(robot_message);
    }

    if (isAlly(robot_message)) {
      this->allies.emplace_back(std::move(robot_message));
    } else {
      this->enemies.emplace_back(std::move(robot_message));
    }
  }
}

void World::takeGameStatus(const GameStatusMessage& game_status) {
  this->game_status = GameStatusMessage(game_status);
}

bool World::isAlly(const RobotMessage& robot) const { return robot.robot_id->color == ally_color; }

void World::takeField(const FieldMessage& field) { this->field = FieldMessage(field); }

void World::update(const OutputMessage& behavior,
                   const std::vector<RobotMessage>& robots,
                   const std::vector<BallMessage>& balls,
                   const FieldMessage& field,
                   const GameStatusMessage& game_status) {

  World::takeRobotsData(behavior, robots);
  World::takeBallHighConfidence(balls);
  World::takeGameStatus(game_status);
  World::takeField(field);
}

} // namespace navigation
