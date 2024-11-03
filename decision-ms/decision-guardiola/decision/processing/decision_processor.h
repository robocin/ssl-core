#ifndef DECISION_PROCESSING_DECISION_PROCESSOR_H
#define DECISION_PROCESSING_DECISION_PROCESSOR_H

#include "decision/messaging/receiver/payload.h"
#include "decision/processing/coach/coach.h"
#include "decision/processing/messages/perception/detection/detection_message.h"
#include "decision/processing/messages/referee/game_status_message.h"
#include "perception/robot/robot_message.h"
#include "world.h"

#include <memory>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <robocin/parameters/parameters.h>

namespace decision {

class IDecisionProcessor {
 public:
  IDecisionProcessor() = default;

  IDecisionProcessor(const IDecisionProcessor&) = delete;
  IDecisionProcessor& operator=(const IDecisionProcessor&) = delete;
  IDecisionProcessor(IDecisionProcessor&&) = default;
  IDecisionProcessor& operator=(IDecisionProcessor&&) = default;

  virtual ~IDecisionProcessor() = default;

  virtual std::optional<::protocols::decision::Decision> process(std::span<const Payload> payloads)
      = 0;
};

class DecisionProcessor : public IDecisionProcessor {
 public:
  struct AlliesAndEnemies {
    std::vector<RobotMessage> allies;
    std::vector<RobotMessage> enemies;
  };

  explicit DecisionProcessor(
      std::unique_ptr<::robocin::parameters::IHandlerEngine> parameters_handler_engine,
      std::unique_ptr<Coach> coach);

  std::optional<::protocols::decision::Decision>
  process(std::span<const Payload> payloads) override;

 private:
  std::unique_ptr<::robocin::parameters::IHandlerEngine> parameters_handler_engine_;
  std::optional<GameStatusMessage> last_game_status_;
  std::optional<DetectionMessage> last_detection_;
  std::unique_ptr<Coach> coach_;
  World world_;

  bool update(std::span<const Payload>& payloads);
  void takeMostAccurateBall(std::vector<BallMessage>& balls, World& world);
  void takeAlliesAndEnemies(std::vector<RobotMessage>& robots, World& world);
};

} // namespace decision

#endif // DECISION_PROCESSING_DDECISION_PROCESSOR_H
