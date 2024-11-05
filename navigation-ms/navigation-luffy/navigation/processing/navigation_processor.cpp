#include "navigation/processing/navigation_processor.h"

#include "messages/behavior/behavior_message.h"
#include "messages/perception/detection/detection_message.h"
#include "messages/referee/game_status_message.h"
#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace rc {

using ::protocols::behavior::Planning;
using ::protocols::behavior::unification::Behavior;
using ::protocols::behavior::unification::Motion;

using ::protocols::referee::GameStatus;

using ::protocols::navigation::Navigation;
using ::protocols::navigation::Output;

using ::protocols::perception::Detection;
using ::protocols::perception::Robot;

using ::protocols::common::PeripheralActuation;
using ::protocols::common::RobotId;

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

NavigationProcessor::NavigationProcessor(std::unique_ptr<IMotionParser> motion_parser) :
    motion_parser_(std::move(motion_parser)) {}

std::optional<rc::Navigation> NavigationProcessor::process(std::span<const Payload> payloads) {
  rc::Navigation navigation_output;

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
  for (const auto& behavior : last_behavior_->output()) {
    rc::Output output;
    rc::Robot ally;

    for (const auto& robot : last_detection.robots()) {
      if (robot.robot_id().number() == behavior.robot_id().number()) {
        ally = robot;
        break;
      }
    }
    if (ally.has_robot_id()) {
      output.mutable_robot_id()->CopyFrom(ally.robot_id());

      if (behavior.has_motion()) {
        RobotMove move;
        if (behavior.motion().has_go_to_point()) {
          move = motion_parser_->fromGoToPoint(behavior.motion().go_to_point(), ally);
        } else if (behavior.motion().has_rotate_in_point()) {
          move = motion_parser_->fromRotateInPoint(behavior.motion().rotate_in_point(), ally);
        } else if (behavior.motion().has_rotate_on_self()) {
          move = motion_parser_->fromRotateOnSelf(behavior.motion().rotate_on_self(), ally);
        } else {
          // PROCESSAMENTO DO GO_TO_POINT_WITH_TRAJECTORY
        }

        output.set_left_velocity(move.velocity().y);
        output.set_forward_velocity(move.velocity().x);
        output.set_angular_velocity(move.angularVelocity());

        if (behavior.motion().has_peripheral_actuation()) {
          output.mutable_peripheral_actuation()->CopyFrom(behavior.motion().peripheral_actuation());
        }

        // TODO: Add other fields to output

      } else if (behavior.has_planning()) {
        // PROCESSAMENTO DO PLANNING
      } else {
        // PROCESSAMENTO DO NAVIGATION
      }
    }

    navigation_output.add_output()->CopyFrom(output);
  }
  ////////////////////////////////////////////////////////////////////////////
  return navigation_output;
}

} // namespace navigation
