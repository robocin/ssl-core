#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"
#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/navigation/navigation_message.h"
#include "navigation/processing/messages/perception/detection/detection_message.h"
#include "navigation/processing/messages/referee/game_status_message.h"
#include "world.h"

#include <optional>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>
#include <robocin/output/log.h>

namespace navigation {

namespace rc {
using ::protocols::behavior::unification::Behavior;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

namespace {

std::vector<rc::Behavior> behaviorFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getBehaviors) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetections) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::GameStatus> gameStatusFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getGameStatuses) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

NavigationProcessor::NavigationProcessor(std::unique_ptr<IMotionParser> motion_parser,
                                         std::unique_ptr<World> world) :
    motion_parser_(std::move(motion_parser)),
    world_(std::move(world)) {}

std::optional<::protocols::navigation::Navigation>
NavigationProcessor::process(std::span<const Payload> payloads) {
  if (std::vector<rc::Behavior> behaviors = behaviorFromPayloads(payloads); !behaviors.empty()) {
    last_behavior_ = BehaviorUnificationMessage(behaviors.back());
  }

  if (std::vector<rc::GameStatus> game_statuses = gameStatusFromPayloads(payloads);
      !game_statuses.empty()) {
    last_game_status_ = GameStatusMessage(game_statuses.back());
  }

  if (!last_behavior_ or !last_game_status_) {
    return std::nullopt;
  }

  std::vector<rc::Detection> detections = detectionFromPayloads(payloads);
  if (detections.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }
  DetectionMessage last_detection = DetectionMessage(detections.back());

  ///////////////////////////////////////////////////////////////////////////
  NavigationMessage navigation_msg;

  for (auto& behavior : last_behavior_->behavior_outputs) {
    setWorld(behavior, last_detection, last_game_status_.value());
    NavigationOutputMessage output_msg = motion_parser_->parseMotion(world_);
    navigation_msg.output.emplace_back(std::move(output_msg));
  }

  return navigation_msg.toProto();
}

void NavigationProcessor::setWorld(OutputMessage& behavior,
                                   DetectionMessage& detection,
                                   GameStatusMessage& game_status) {
  world_->update(behavior, detection.robots, detection.balls, detection.field.value(), game_status);
}

} // namespace navigation
