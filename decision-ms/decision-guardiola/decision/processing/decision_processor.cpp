#include "decision/processing/decision_processor.h"

#include "decision/messaging/receiver/payload.h"
#include "decision/processing/entities/world.h"
#include "decision/processing/messages/behavior/behavior_message.h"
#include "decision/processing/messages/decision/decision_message.h"
#include "decision/processing/messages/perception/detection/detection_message.h"
#include "referee/game_status_message.h"

#include <protocols/common/robot_id.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>
#include <robocin/output/log.h>

namespace decision {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {

using ::protocols::common::RobotId;
using ::protocols::decision::Behavior;
using ::protocols::decision::Decision;
using ::protocols::decision::DefensivePlan;
using ::protocols::decision::OffensivePlan;
using ::protocols::decision::TacticalPlan;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetections) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::GameStatus> gameStatusFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getGameStatus) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

DecisionProcessor::DecisionProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine,
    std::unique_ptr<Coach> coach) :
    parameters_handler_engine_{std::move(parameters_handler_engine)},
    coach_{std::move(coach)} {}

std::optional<rc::Decision> DecisionProcessor::process(std::span<const Payload> payloads) {
  rc::Decision decision_output;

  if (std::vector<rc::GameStatus> game_status = gameStatusFromPayloads(payloads);
      !game_status.empty()) {
    last_game_status_ = GameStatusMessage(game_status.back());
  }

  if (!last_game_status_) {
    return std::nullopt;
  }

  std::vector<rc::Detection> detections = detectionFromPayloads(payloads);
  if (detections.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }

  last_detection_ = DetectionMessage(detections.back());

  ///////////////////////////////////////////////////////////////////////////////////

  // TODO: Implement the logic to generate the decision based on the last detection and the last
  // game status.
  coach_->process();
  TacticalPlan tactical_plan = coach_->tactical_plan;

  for (const auto& robot : last_detection.robots()) {
    rc::Behavior* behavior = decision_output.add_behavior();

    behavior->set_id(0);
    behavior->mutable_robot_id()->CopyFrom(robot.robot_id());
  }

  rc::TacticalPlan* tplan = decision_output.mutable_plan();

  rc::OffensivePlan* ofPlan = tplan->mutable_offensive();
  rc::DefensivePlan* dfPlan = tplan->mutable_defensive();

  ///////////////////////////////////////////////////////////////////////////////////

  return decision_output;
}

} // namespace decision
