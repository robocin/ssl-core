#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/motion.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/navigation/planning.pb.h>
#include <protocols/perception/detection.pb.h>
#include <ranges>
#include <utility>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace rc {

  using ::protocols::behavior::unification::Behavior;
  using ::protocols::perception::Detection;
  using ::protocols::behavior::unification::Motion;
  using ::protocols::navigation::Navigation;
  using ::protocols::navigation::Planning;
  using ::protocols::perception::Robot;
  using ::protocols::navigation::GoToPoint;
  using ::protocols::common::RobotId;
  using ::protocols::common::PeripheralActuation;

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

} // namespace]

NavigationProcessor::NavigationProcessor(
    std::unique_ptr<GoToPointParser> go_to_point_parser,
    std::unique_ptr<RotateInPointParser> rotate_in_point_parser,
    std::unique_ptr<RotateOnSelfParser> rotate_on_self_parser) :
    go_to_point_parser_(std::move(go_to_point_parser)),
    rotate_in_point_parser_(std::move(rotate_in_point_parser)),
    rotate_on_self_parser_(std::move(rotate_on_self_parser)) {}

std::optional<rc::Navigation> NavigationProcessor::process(std::span<const Payload> payloads) {
  std::vector<rc::Behavior> behaviors = behaviorFromPayloads(payloads);
  std::vector<rc::Detection> detections = detectionFromPayloads(payloads);

  rc::Navigation navigation;

  if (detections.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }

  rc::Detection last_detection = detections.back();

  if (!behaviors.empty()) {
    return std::nullopt;
  }
  rc::Behavior last_behavior = behaviors.back();
  
  switch (last_behavior.output_case()) {
    case rc::Behavior::kMotion: {
      
      const rc::Motion& motion = last_behavior.motion();
      rc::Robot ally;

      if (motion.has_go_to_point()) {
        rc::GoToPoint go_to_point = motion.go_to_point();
        
        // get robot from detection if robot id == behavior id field
        for (const auto& robot : last_detection.robots()) {
          if (robot.robot_id().number() == last_behavior.id().number()) {
            ally = robot;
            break;
          }
        }

        RobotMove robot_move = go_to_point_parser_->parse(go_to_point, ally);

        rc::RobotId* robot_id = navigation.mutable_id();
        robot_id->set_number(last_behavior.id().number());
        robot_id->set_color(last_behavior.id().color());

        rc::PeripheralActuation* peripheral_actuation = navigation.mutable_peripheral_actuation();
        peripheral_actuation->CopyFrom(motion.peripheral_actuation());

        navigation.set_forward_velocity(robot_move.velocity().x);
        navigation.set_left_velocity(robot_move.velocity().y);
        navigation.set_angular_velocity(robot_move.angularVelocity());

        rc::GoToPoint* go_2_point = navigation.mutable_go_to_point();
        go_2_point->CopyFrom(motion.go_to_point().target());

        return navigation; // Criar objeto do protobuf navigation aqui

      } else if (motion.has_rotate_in_point()) {
        // RobotMove robot_move = rotate_in_point_parser_->parse(motion);
        // return robot_move; // Criar objeto do protobuf navigation aqui

      } else if (motion.has_rotate_on_self()) {
        // RobotMove robot_move = rotate_on_self_parser_->parse(motion);
        // return robot_move; // Criar objeto do protobuf navigation aqui

      } else {
        // RobotMove robot_move = go_to_point_with_trajectory_parser_->parse(motion);
        // return robot_move; // Criar objeto do protobuf navigation aqui
      }
    }
    case rc::Behavior::kPlanning: {
      const rc::Planning& planning = last_behavior_.planning();
      // Adicione aqui o processamento específico para Planning
      break;
    }
    case rc::Behavior::kNavigation: {
      const rc::Navigation& navigation = last_behavior_.navigation();
      // Adicione aqui o processamento específico para Navigation
      break;
    }
    case rc::Behavior::OUTPUT_NOT_SET: return std::nullopt; break;
  }

  return std::nullopt;
}

} // namespace navigation
