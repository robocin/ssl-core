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
  std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
  
   if(std::vector<rc::Decision> decision_messages = decisionfromPayloads(payloads); 
    !decision_messages.empty()) {
      last_decision_ = decision_messages.back();
  }

  if (!last_decision_) {
    return std::nullopt;
  }

  if(detection_messages.empty()) {
    // ilog("Sem detection");
    return std::nullopt;
  }

  rc::Behavior behavior_output;
  // ilog("Detection lentgh : {}", detection_messages.size());
  rc::Detection last_detection = detection_messages.back();

  for (auto behavior : last_decision_->behavior()) {
    if (behavior.id() == 199) {
        rc::RobotId *robot_id = behavior_output.mutable_id();
        robot_id->CopyFrom(behavior.robot_id());
    }
  }

  rc::MotionList motion_list;
  rc::Motion motion;
  auto* go_to_point = new rc::GoToPoint;
  rc::Ball ball = last_detection.balls(last_detection.balls_size() - 1);

  go_to_point->mutable_target()->set_x(ball.position().x());
  go_to_point->mutable_target()->set_y(ball.position().y());
  go_to_point->set_target_angle(0.0);

  motion.set_allocated_go_to_point(go_to_point);
  motion_list.add_motion()->CopyFrom(motion);
  behavior_output.mutable_motion()->CopyFrom(motion_list);

  // todo: implement process
  return behavior_output;
}

} // namespace behavior
