#include "behavior/processing/behavior_processor.h"

#include "behavior/messaging/receiver/payload.h"
#include "behavior/parameters/parameters.h"
#include "state_machine/goalkeeper/goalkeeper_state_machine.h"

#include <optional>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>
#include <robocin/memory/object_ptr.h>
#include <robocin/output/log.h>
#include <vector>

namespace behavior {

namespace parameters = ::robocin::parameters;

namespace {

using ::robocin::ilog;
using ::robocin::object_ptr;

namespace rc {

using ::protocols::common::RobotId;
using ::protocols::decision::Decision;
using ::protocols::perception::Ball;
using ::protocols::perception::Detection;

using ::protocols::behavior::GoToPoint;
using ::protocols::behavior::unification::Behavior;
using ::protocols::behavior::unification::Motion;
using ::protocols::behavior::unification::Output;

using ::protocols::referee::GameStatus;

} // namespace rc

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetectionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Decision> decisionfromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDecisionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::GameStatus> gameStatusFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getGameStatusMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

BehaviorProcessor::BehaviorProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine,
    std::unique_ptr<::behavior::GoalkeeperStateMachine> goalkeeper_state_machine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)},
    goalkeeper_state_machine_{std::move(goalkeeper_state_machine)} {}

std::optional<rc::Behavior> BehaviorProcessor::process(std::span<const Payload> payloads) {

  if (std::vector<rc::Decision> decision_messages = decisionfromPayloads(payloads);
      !decision_messages.empty()) {
    last_decision_ = decision_messages.back();
  }

  if (!last_decision_) {
    return std::nullopt;
  }

  if (std::vector<rc::GameStatus> game_status_messages = gameStatusFromPayloads(payloads);
      !game_status_messages.empty()) {
    last_game_status_ = game_status_messages.back();
  }

  if (!last_game_status_) {
    return std::nullopt;
  }

  std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
  if (detection_messages.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }
  const rc::Detection last_detection = detection_messages.back();

  BehaviorMessage behavior_message;
  // TODO: implement the logic to generate the behavior based on the last detection and the last
  // decision
  ///////////////////////////////////////////////////////////////////////////////////

  for (const auto& robot : last_detection.robots()) {

    behavior_message.output.emplace_back(
        OutputMessage{RobotIdMessage{}, MotionMessage{}, PlanningMessage{}});
  }

  ///////////////////////////////////////////////////////////////////////////////////
  goalkeeper_state_machine_->run();

  return behavior_message.toProto();
}

} // namespace behavior
