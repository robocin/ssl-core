#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"
#include "parameters.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <ranges>
#include <robocin/output/log.h>

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

  // For now, doing only for one robot
  RobotMove move;
  for (const auto& behavior : last_behavior_->output()) {
    rc::Robot robot;
    if (behavior.has_motion()) {
      robot = findMyRobot(behavior.robot_id().number(), last_detection.robots());

      // todo: parser is crashing
      // move = motion_parser_->fromGoToPoint(behavior.motion().go_to_point(), robot);
    }

    navigation_output.add_output()->CopyFrom(makeOutput(move, behavior));
  }

  return navigation_output;
}

} // namespace navigation
