#include "decision/processing/decision_processor.h"

#include "common/robot_id/robot_id_message.h"
#include "decision/messaging/receiver/payload.h"
#include "decision/parameters/parameters.h"
#include "decision/processing/entities/world.h"
#include "decision/processing/messages/behavior/behavior_message.h"
#include "decision/processing/messages/decision/decision_message.h"
#include "decision/processing/messages/perception/detection/detection_message.h"
#include "perception/ball/ball_message.h"
#include "perception/robot/robot_message.h"
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

  DecisionProcessor::update(payloads);

  coach_->process(world_);
  TacticalPlan tactical_plan = coach_->tactical_plan;
  robocin::ilog("TEMOS {} BEHAVIORS", coach_->behaviors.size());

  return rc::Decision{};
}

// Private methods
void DecisionProcessor::takeMostAccurateBall(std::vector<BallMessage>& balls, World& world) {
  BallMessage* most_accurate_ball = nullptr;
  float most_accurate_confidence = 0.0;

  for (auto& ball : balls) {
    if (ball.confidence.value() >= most_accurate_confidence) {
      most_accurate_confidence = ball.confidence.value();
      most_accurate_ball = &ball;
    }
  }

  world.ball = std::move(*most_accurate_ball);
}

void DecisionProcessor::takeAlliesAndEnemies(std::vector<RobotMessage>& robots, World& world) {
  std::vector<RobotMessage> yellow;
  std::vector<RobotMessage> blue;

  for (auto& robot : robots) {
    if (!robot.robot_id.has_value()) {
      continue;
    }

    if (robot.robot_id->color == RobotIdMessage::Color::COLOR_YELLOW) {
      yellow.emplace_back(std::move(robot));
    }

    if (robot.robot_id->color == RobotIdMessage::Color::COLOR_BLUE) {
      blue.emplace_back(std::move(robot));
    }

    // todo: handle unspecified color
  }

  if (pAllyColor == RobotIdMessage::Color::COLOR_YELLOW) {
    world.allies = yellow;
    world.enemies = blue;
  } else {
    world.allies = blue;
    world.enemies = yellow;
  }
}

bool DecisionProcessor::update(std::span<const Payload>& payloads) {

  if (std::vector<rc::GameStatus> game_status = gameStatusFromPayloads(payloads);
      !game_status.empty()) {
    last_game_status_ = GameStatusMessage(game_status.back());
  }

  if (!last_game_status_) {
    return false;
  }

  std::vector<rc::Detection> detections = detectionFromPayloads(payloads);
  if (detections.empty()) {
    // a new package must be generated only when a new detection is received.
    return false;
  }

  last_detection_ = DetectionMessage(detections.back());

  DecisionProcessor::takeMostAccurateBall(last_detection_->balls, world_);
  DecisionProcessor::takeAlliesAndEnemies(last_detection_->robots, world_);

  return true;
}

} // namespace decision
