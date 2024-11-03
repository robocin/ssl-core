#include "behavior/processing/entities/world.h"

#include "world.h"

#include <protocols/perception/detection.pb.h>
#include <vector>

namespace behavior {

// void World::update(std::optional<DecisionMessage>& decision,
//                    std::optional<std::span<RobotMessage>>& robots,
//                    std::optional<BallMessage>& ball) {

//   if (decision.has_value()) {
//     this->decision = std::move(decision.value());
//   }

//   if (robots.has_value()) {
//     for (const auto& robot : robots.value()) {
//       bool isAlly = (pIsYellow() && robot.robot_id->color == Color::COLOR_YELLOW)
//                     || (!pIsYellow() && robot.robot_id->color == Color::COLOR_BLUE);

//       if (isAlly) {
//         this->allies.emplace_back(std::move(robot));
//       } else {
//         this->enemies.emplace_back(std::move(robot));
//       }
//     }
//   }

//   if (ball.has_value()) {
//     // TODO(ersa): get ball with highest confidence
//     this->ball = std::move(ball.value());
//   }

//   // if (game_status.has_value()) {
//   //   // TODO(ersa): get last game status
//   //   this->game_status = std::move(game_status.value());
//   // }
// }

void World::takeBallHighConfidence(const std::vector<protocols::perception::Ball>& balls) {
  if (balls.empty()) {
    return;
  }

  auto max_ball
      = std::max_element(balls.begin(), balls.end(), [](const auto& ball1, const auto& ball2) {
          return ball1.confidence() < ball2.confidence();
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
    bool isAlly = (pIsYellow() && robot_message.robot_id->color == Color::COLOR_YELLOW)
                  || (!pIsYellow() && robot_message.robot_id->color == Color::COLOR_BLUE);

    if (isAlly) {
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

void World::update(const protocols::decision::Decision& decision,
                   const std::vector<protocols::perception::Robot>& robots,
                   const std::vector<protocols::perception::Ball>& balls,
                   const protocols::referee::GameStatus& game_status) {

  this->takeDecision(decision);
  this->takeAlliesAndEnemies(robots);
  this->takeBallHighConfidence(balls);
  this->takeGameStatus(game_status);
}

} // namespace behavior
