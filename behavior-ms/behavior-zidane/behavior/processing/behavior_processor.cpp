#include "behavior/processing/behavior_processor.h"

#include "behavior/messaging/receiver/payload.h"
#include "behavior/parameters/parameters.h"

#include <algorithm>
#include <iterator>
#include <print>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <ranges>
#include <robocin/memory/object_ptr.h>
#include <robocin/output/log.h>

namespace behavior {

namespace parameters = ::robocin::parameters;

namespace {

using ::robocin::ilog;
using ::robocin::object_ptr;

namespace rc {

using ::protocols::behavior::unification::Behavior;
using ::protocols::decision::Decision;
using ::protocols::perception::Detection;
using ::protocols::common::RobotId;
using ::protocols::perception::Ball;
using ::protocols::behavior::unification::Motion;
using ::protocols::behavior::GoToPoint;
using ::protocols::behavior::unification::MotionList;


} // namespace rc

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetectionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Decision> decisionfromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDecisionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

BehaviorProcessor::BehaviorProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)} {}

std::optional<rc::Behavior> BehaviorProcessor::process(std::span<const Payload> payloads) {
  std::vector<rc::Decision> decision_messages = decisionfromPayloads(payloads);
  std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
  
  rc::Behavior behavior_output;
  rc::Decision last_decision = decision_messages.back();
  // ilog("Detection lentgh : {}", detection_messages.size());
  // rc::Detection last_detection = detection_messages.back();

  for (auto behavior : last_decision.behavior()) {
    if (behavior.id() == 199) {
        rc::RobotId *robot_id = behavior_output.mutable_id();
        robot_id->CopyFrom(behavior.robot_id());
    }
  }

  // rc::MotionList motion_list;
  // rc::Motion motion;
  // rc::GoToPoint go_to_point;
  // rc::Ball ball = last_detection.balls(last_detection.balls_size() - 1);

  // go_to_point.mutable_target()->set_x(ball.position().x());
  // go_to_point.mutable_target()->set_y(ball.position().y());
  // go_to_point.set_target_angle(0.0);

  // motion.set_allocated_go_to_point(&go_to_point);
  // *motion_list.add_motion() = motion;
  // behavior_output.set_allocated_motion(&motion_list);


  // todo: implement process
  return behavior_output;
}

} // namespace behavior
