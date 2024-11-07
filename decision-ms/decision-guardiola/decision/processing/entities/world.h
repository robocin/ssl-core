#ifndef DECISION_PROCESSING_ENTITIES_WORLD_H
#define DECISION_PROCESSING_ENTITIES_WORLD_H

#include "decision/processing/messages/perception/ball/ball_message.h"
#include "decision/processing/messages/perception/field/field_message.h"
#include "decision/processing/messages/perception/robot/robot_message.h"
#include "decision/processing/messages/referee/game_status_message.h"

namespace decision {

class World {
 public:
  explicit World();

  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&) noexcept = default;
  World& operator=(World&&) noexcept = default;

  virtual ~World() = default;

  std::vector<RobotMessage> allies;
  std::vector<RobotMessage> enemies;
  BallMessage ball;
  FieldMessage field;
  GameStatusMessage game_status; // referee

  void update(std::vector<RobotMessage>& robots,
              std::vector<BallMessage>& balls,
              FieldMessage& field,
              GameStatusMessage& game);

 private:
  void takeMostAccurateBall(std::vector<BallMessage>& balls);
  void takeAlliesAndEnemies(std::vector<RobotMessage>& robots);
  bool isAlly(const RobotMessage& robot) const;
};

} // namespace decision

#endif // DECISION_PROCESSING_ENTITIES_WORLD_H
