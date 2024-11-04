#include "decision/processing/entities/world.h"

#include "decision/parameters/parameters.h"
#include "decision/processing/messages/perception/ball/ball_message.h"
#include "decision/processing/messages/perception/robot/robot_message.h"

#include <algorithm>

namespace decision {

constexpr int kMaxRobotsInTeam = 11;

World::World() {
  allies.reserve(kMaxRobotsInTeam);
  enemies.reserve(kMaxRobotsInTeam);
}

void World::update(std::vector<RobotMessage>& robots,
                   std::vector<BallMessage>& balls,
                   FieldMessage& field,
                   GameStatusMessage& game_status) {

  takeMostAccurateBall(balls);
  takeAlliesAndEnemies(robots);

  this->field = std::move(field);
  this->game_status = std::move(game_status);
}

void World::takeMostAccurateBall(std::vector<BallMessage>& balls) {
  if (balls.empty()) {
    return;
  }

  auto most_accurate_ball
      = std::max_element(balls.begin(),
                         balls.end(),
                         [](BallMessage& ball, BallMessage& other_ball) {
                           return ball.confidence.value() < other_ball.confidence.value();
                         });

  ball = std::move(*most_accurate_ball);
}

void World::takeAlliesAndEnemies(std::vector<RobotMessage>& robots) {
  if (robots.empty()) {
    return;
  }

  allies.clear();
  enemies.clear();

  for (RobotMessage& robot : robots) {
    if (!robot.robot_id.has_value()) {
      continue;
    }

    if (isAlly(robot)) {
      allies.emplace_back(std::move(robot));
    } else {
      enemies.emplace_back(std::move(robot));
    }
  }
}

bool World::isAlly(const RobotMessage& robot) const { return robot.robot_id->color == pAllyColor; }

} // namespace decision
