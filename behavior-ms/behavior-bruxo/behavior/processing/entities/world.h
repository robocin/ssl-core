#ifndef BEHAVIOR_PROCESSING_ENTITIES_WORLD_H
#define BEHAVIOR_PROCESSING_ENTITIES_WORLD_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/messages/decision/decision_message.h"
#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"
#include "behavior/processing/messages/referee/game_status_message.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>

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
  //   GameStatusMessage game_status;

  std::vector<RobotMessage> allies;
  std::vector<RobotMessage> enemies;

  //   void update(std::optional<DecisionMessage>& decision,
  //               std::optional<std::span<RobotMessage>>& robots,
  //               std::optional<BallMessage>& ball);

  void update(const protocols::decision::Decision& decision,
              const std::vector<protocols::perception::Robot>& robots,
              const protocols::perception::Ball& ball);
};

} // namespace behavior

#endif // DECISION_PROCESSING_ENTITIES_WORLD_H
