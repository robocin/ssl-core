#ifndef BEHAVIOR_PROCESSING_BEHAVIOR_PROCESSOR_H
#define BEHAVIOR_PROCESSING_BEHAVIOR_PROCESSOR_H

#include "behavior/messaging/receiver/payload.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"
#include "behavior/processing/messages/referee/game_status_message.h"

#include "state_machine/goalkeeper/goalkeeper_state_machine.h"


#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <robocin/parameters/parameters.h>

namespace behavior {

class IBehaviorProcessor {
 public:
  IBehaviorProcessor() = default;

  IBehaviorProcessor(const IBehaviorProcessor&) = delete;
  IBehaviorProcessor& operator=(const IBehaviorProcessor&) = delete;
  IBehaviorProcessor(IBehaviorProcessor&&) = default;
  IBehaviorProcessor& operator=(IBehaviorProcessor&&) = default;

  virtual ~IBehaviorProcessor() = default;

  virtual std::optional<::protocols::behavior::unification::Behavior>
  process(std::span<const Payload> payloads) = 0;
};

class BehaviorProcessor : public IBehaviorProcessor {
 public:
  explicit BehaviorProcessor(
      std::unique_ptr<::robocin::parameters::IHandlerEngine> parameters_handler_engine,
      std::unique_ptr<::behavior::GoalkeeperStateMachine> goalkeeper_state_machine);

  std::optional<::protocols::behavior::unification::Behavior>
  process(std::span<const Payload> payloads) override;

 private:
  World world_;
  std::unique_ptr<::robocin::parameters::IHandlerEngine> parameters_handler_engine_;
  std::unique_ptr<behavior::GoalkeeperStateMachine> goalkeeper_state_machine_;
  std::optional<::protocols::decision::Decision> last_decision_;
  std::optional<::protocols::referee::GameStatus> last_game_status_;
};

} // namespace behavior

#endif // BEHAVIOR_PROCESSING_BEHAVIOR_PROCESSOR_H
