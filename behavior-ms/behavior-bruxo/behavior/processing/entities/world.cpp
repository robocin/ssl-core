#include "behavior/processing/entities/world.h"

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

void World::update(const protocols::decision::Decision& decision,
                   const std::vector<protocols::perception::Robot>& robots,
                   const protocols::perception::Ball& ball) {
  this->decision.fromProto(decision);

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

  this->ball.fromProto(ball);
}

} // namespace behavior
