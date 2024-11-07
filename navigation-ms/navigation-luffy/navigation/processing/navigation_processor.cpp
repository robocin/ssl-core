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
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>

namespace navigation {

namespace parameters = ::robocin::parameters;

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

NavigationProcessor::NavigationProcessor(std::unique_ptr<IMotionParser> motion_parser) :
    motion_parser_(std::move(motion_parser)) {}

std::optional<NavigationMessage> NavigationProcessor::process(std::span<const Payload> payloads) {
  NavigationMessage navigation_output;

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
  for (const auto& behavior : last_behavior_->behavior_outputs) {
    NavigationOutputMessage output;
    RobotMessage ally;

    for (auto& robot : last_detection.robots) {
      if (robot.robot_id->number == behavior.robot_id->number) {
        ally = RobotMessage(robot);
        break;
      }
    }
    if (ally.robot_id) {
      output.robot_id = ally.robot_id;

      if (behavior.motion) {
        RobotMove move;
        if (behavior.motion->go_to_point) {
          move = motion_parser_->fromGoToPoint(behavior.motion->go_to_point.value(), ally);
        } else if (behavior.motion->rotate_in_point) {
          move = motion_parser_->fromRotateInPoint(behavior.motion->rotate_in_point.value(), ally);
        } else if (behavior.motion->rotate_on_self) {
          move = motion_parser_->fromRotateOnSelf(behavior.motion->rotate_on_self.value(), ally);
        } else {
          // PROCESSAMENTO DO GO_TO_POINT_WITH_TRAJECTORY
        }

        output.left_velocity = move.velocity().y;
        output.forward_velocity = move.velocity().x;
        output.angular_velocity = move.angularVelocity();

        if (behavior.motion->peripheral_actuation) {
          output.peripheral_actuation = behavior.motion->peripheral_actuation;
        }

        // TODO: Add other fields to output

      } else if (behavior.planning) {
        // PROCESSAMENTO DO PLANNING
      } else {
        // PROCESSAMENTO DO NAVIGATION
      }
    }

    navigation_output.output.emplace_back(output);
  }
  ////////////////////////////////////////////////////////////////////////////
  return navigation_output;
}

} // namespace navigation
