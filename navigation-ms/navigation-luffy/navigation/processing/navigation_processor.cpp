#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <ranges>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace rc {

using ::protocols::behavior::GoToPoint;
using ::protocols::behavior::Planning;
using ::protocols::behavior::unification::Behavior;
using ::protocols::behavior::unification::Motion;

using ::protocols::navigation::Navigation;
using ::protocols::navigation::Output;

using ::protocols::perception::Detection;
using ::protocols::perception::Robot;

using ::protocols::common::PeripheralActuation;
using ::protocols::common::RobotId;

} // namespace rc

namespace {

protocols::perception::Robot
findMyRobot(int id, const google::protobuf::RepeatedPtrField<rc::Robot>& allies) { // implement
  return protocols::perception::Robot{};
}

std::vector<rc::Behavior> behaviorFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getBehaviors) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetections) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

NavigationProcessor::NavigationProcessor(std::unique_ptr<IMotionParser> motion_parser) :
    motion_parser_(std::move(motion_parser)) {}

std::optional<rc::Navigation> NavigationProcessor::process(std::span<const Payload> payloads) {
  rc::Navigation navigation_output;

  if (std::vector<rc::Behavior> behaviors = behaviorFromPayloads(payloads); !behaviors.empty()) {
    last_behavior_ = behaviors.back();
  }

  if (!last_behavior_) {
    return std::nullopt;
  }

  std::vector<rc::Detection> detections = detectionFromPayloads(payloads);
  if (detections.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }
  rc::Detection last_detection = detections.back();

  RobotMove move;
  for (const auto& behavior : last_behavior_->output()) {
    if (behavior.has_motion()) {
      // Mock only robot with I: 0
      rc::Robot robot_mock{};
      move = motion_parser_->fromGoToPoint(behavior.motion().go_to_point(),
                                           findMyRobot(0, last_detection.robots()));
    }
  }

  return navigation_output;
}

} // namespace navigation
