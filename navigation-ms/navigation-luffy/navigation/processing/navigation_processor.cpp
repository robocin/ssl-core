#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"
#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/navigation/navigation_message.h"
#include "navigation/processing/messages/perception/detection/detection_message.h"
#include "navigation/processing/messages/perception/robot/robot_message.h"
#include "navigation/processing/messages/planning/planning_message.h"
#include "navigation/processing/messages/referee/game_status_message.h"

#include <optional>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>
#include <robocin/output/log.h>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace rc {
using ::protocols::behavior::unification::Behavior;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

namespace {

protocols::perception::Robot
findMyRobot(int number, const google::protobuf::RepeatedPtrField<rc::Robot>& robots) {
  // This function does not handle a case where it does not find a robot
  for (auto& robot : robots) {
    auto number_match = robot.robot_id().number() == number;
    if (number_match) {
      return robot;
    }
  }

  return protocols::perception::Robot{};
}

rc::Output makeOutput(RobotMove move, const protocols::behavior::unification::Output& behavior) {
  rc::Output output;

  output.set_left_velocity(move.velocity().y);
  output.set_forward_velocity(move.velocity().x);
  output.set_angular_velocity(move.angularVelocity());

  if (behavior.motion().has_peripheral_actuation()) {
    output.mutable_peripheral_actuation()->CopyFrom(behavior.motion().peripheral_actuation());
  }

  return output;
};

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

NavigationProcessor::NavigationProcessor(std::unique_ptr<IMotionParser> motion_parser) :
    motion_parser_(std::move(motion_parser)) {}

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
    motion_parser_->setWorld(behavior, last_detection, last_game_status_.value());
    NavigationOutputMessage output_msg = motion_parser_->parseMotion();
    navigation_msg.output->emplace_back(std::move(output_msg));
  }

  return navigation_msg.toProto();
}

} // namespace navigation
