#ifndef BEHAVIOR_PROCESSING_ENTITIES_WORLD_H
#define BEHAVIOR_PROCESSING_ENTITIES_WORLD_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/messages/decision/decision_message.h"
#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/field/field_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"
#include "behavior/processing/messages/referee/game_status_message.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <vector>

namespace behavior {

class World {
 public:
  World() = default;

  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&) noexcept = default;
  World& operator=(World&&) noexcept = default;

  virtual ~World() = default;

  BallMessage ball;
  DecisionMessage decision;
  GameStatusMessage game_status;
  FieldMessage field;

  std::vector<RobotMessage> allies;
  std::vector<RobotMessage> enemies;

  void update(const std::vector<protocols::perception::Robot>& robots,
              const std::vector<protocols::perception::Ball>& balls,
              const protocols::perception::Field& field,
              const protocols::referee::GameStatus& game_status);

 private:
  void takeBallHighConfidence(const std::vector<protocols::perception::Ball>& balls);
  void takeAlliesAndEnemies(const std::vector<protocols::perception::Robot>& robots);
  void takeDecision(const protocols::decision::Decision& decision);
  void takeGameStatus(const protocols::referee::GameStatus& game_status);
  void takeField(const protocols::perception::Field& field);

  [[nodiscard]] bool isAlly(const RobotMessage& robot) const;
};

} // namespace behavior

#endif // DECISION_PROCESSING_ENTITIES_WORLD_H
