#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/perception/detection.pb.h>
#include <google/protobuf/timestamp.pb.h>
#include <ranges>
#include <utility>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace rc {

  using ::protocols::behavior::unification::Behavior;
  using ::protocols::behavior::unification::MotionList;
  using ::protocols::behavior::unification::PlanningList;
  using ::protocols::behavior::unification::NavigationList;
  using ::protocols::perception::Detection;
  using ::protocols::navigation::Navigation;
  using ::protocols::navigation::Output;
  using ::protocols::behavior::Planning;
  using ::protocols::perception::Robot;
  using ::protocols::behavior::GoToPoint;
  using ::protocols::common::RobotId;
  using ::protocols::common::PeripheralActuation;
  using ::protocols::common::Point2Df;
  using ::protocols::common::RobotPose;

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

  if (behaviors.empty()) {
    return std::nullopt;
  }
  rc::Behavior last_behavior = behaviors.back();
  
  switch (last_behavior.output_case()) {
    case rc::Behavior::kMotion: {
      
      const rc::MotionList& motionList = last_behavior.motion();
      rc::Robot ally;

      for (const auto& motion : motionList.motion()) {
        rc::Output output;

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

          rc::RobotId* robot_id = output.mutable_id();
          robot_id->set_number(last_behavior.id().number());
          robot_id->set_color(last_behavior.id().color());

          rc::PeripheralActuation* peripheral_actuation = output.mutable_peripheral_actuation();
          peripheral_actuation->CopyFrom(motion.peripheral_actuation());

          output.set_forward_velocity(robot_move.velocity().x);
          output.set_left_velocity(robot_move.velocity().y);
          output.set_angular_velocity(robot_move.angularVelocity());

          google::protobuf::Timestamp* timestamp = output.mutable_timestamp();
          auto now = std::chrono::system_clock::now();
          auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
          auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - seconds);
          timestamp->set_seconds(seconds.time_since_epoch().count());
          timestamp->set_nanos(nanoseconds.count());

          output.set_custom_command(1); 
          output.set_sequence_number(2);

          rc::Point2Df* global_velocity = output.mutable_output_global_linear_velocity();
          global_velocity->set_x(robot_move.velocity().x);
          global_velocity->set_y(robot_move.velocity().y);

          rc::RobotPose* robot_pose = output.mutable_robot_pose();
          // Defina os campos de robot_pose conforme necessário

          *navigation.add_output() = output; // Adiciona o output ao repeated output

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

      return navigation; // Criar objeto do protobuf navigation aqui

    }
    case rc::Behavior::kPlanning: {
      const rc::PlanningList& planningList = last_behavior.planning();
      // Adicione aqui o processamento específico para Planning
      break;
    }
    case rc::Behavior::kNavigation: {
      const rc::NavigationList& navigationList = last_behavior_.navigation();
      // Adicione aqui o processamento específico para Navigation
      break;
    }
    case rc::Behavior::OUTPUT_NOT_SET: return std::nullopt; break;
  }

  return std::nullopt;
}

} // namespace navigation
