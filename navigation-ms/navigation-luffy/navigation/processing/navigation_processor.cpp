#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/behavior/planning.pb.h>
#include <protocols/perception/detection.pb.h>
#include <google/protobuf/timestamp.pb.h>
#include "robocin/geometry/point2d.h"
#include <ranges>
#include <utility>

#define PI 3.14159265358979323846

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

// NavigationProcessor::NavigationProcessor(
//     std::unique_ptr<GoToPointParser> go_to_point_parser,
//     std::unique_ptr<RotateInPointParser> rotate_in_point_parser,
//     std::unique_ptr<RotateOnSelfParser> rotate_on_self_parser) :
//     go_to_point_parser_(std::move(go_to_point_parser)),
//     rotate_in_point_parser_(std::move(rotate_in_point_parser)),
//     rotate_on_self_parser_(std::move(rotate_on_self_parser)) {}

// NavigationProcessor::NavigationProcessor(
//     std::unique_ptr<GoToPointParser> go_to_point_parser) :
//     go_to_point_parser_(std::move(go_to_point_parser)) {}

NavigationProcessor::NavigationProcessor() {}

std::optional<rc::Navigation> NavigationProcessor::process(std::span<const Payload> payloads) {
  std::vector<rc::Detection> detections = detectionFromPayloads(payloads);

  rc::Navigation navigation_output;

  if(std::vector<rc::Behavior> behaviors = behaviorFromPayloads(payloads);
    !behaviors.empty()) {
    last_behavior_ = std::move(behaviors.back());
  }

  if(!last_behavior_) {
    return std::nullopt;
  }

  if (detections.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }

  rc::Detection last_detection = detections.back();
  
  switch (last_behavior_->output_case()) {
    case rc::Behavior::kMotion: {
      // robocin::ilog("Motion: {}", last_behavior.motion().DebugString());
      const rc::MotionList& motionList = last_behavior_->motion();
      rc::Robot ally;

      for (const auto& motion : motionList.motion()) {
        // robocin::ilog("Motion: {}", motion.DebugString());
        rc::Output output;
        if (motion.has_go_to_point()) {
          rc::GoToPoint go_to_point = motion.go_to_point();
          // robocin::ilog("GoToPoint: {}", go_to_point.DebugString());
          // get robot from detection if robot id == behavior id field
          for (const auto& robot : last_detection.robots()) {
            if (199 == last_behavior_->id().number()) {
              ally = robot;
              break;
            }
          }
          // RobotMove robot_move = go_to_point_parser_->parse(go_to_point, ally);

          auto parser_result = [](::protocols::behavior::GoToPoint go_to_point,
                                      ::protocols::perception::Robot robot){
          //////////////////////////////////////
            robocin::Point2D robot_position = robocin::Point2D(robot.position().x(), robot.position().y());
            robocin::Point2D target_position = robocin::Point2D(go_to_point.target().x(), go_to_point.target().y());
          
            double distanceToGoal = robot_position.distanceTo(target_position);
            double max_velocity = 2.2;

            auto smallestAngleDiff = [](double lhs, double rhs) {
                double angle = fmod(rhs - lhs, 2 * PI);
                if (angle >= PI) {
                    return angle - 2 * PI;
                } else if (angle < -PI) {
                    return angle + 2 * PI;
                }
                return angle;
            };

            auto fromPolar = [](auto length, auto angle) {
                return std::make_pair(std::cos(angle) * length, std::sin(angle) * length);
            };

            if (distanceToGoal > 50) {
                auto theta = (target_position - robot_position).angle();

                auto dTheta = smallestAngleDiff(robot.angle(), go_to_point.target_angle());
                auto v_prop = std::abs(smallestAngleDiff(PI - 0.1, dTheta)) * max_velocity / (PI - 0.1);

                return RobotMove(fromPolar(v_prop, theta), 5 * dTheta);

            } else {
                // anglePID()
                auto dTheta = smallestAngleDiff(robot.angle(), go_to_point.target_angle());

                return RobotMove(5 * dTheta);
            }
          };

          RobotMove robot_move = parser_result(go_to_point, ally);
          //////////////////////////////////////

          rc::RobotId* robot_id = output.mutable_id();
          robot_id->set_number(last_behavior_->id().number());
          robot_id->set_color(last_behavior_->id().color());

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

          *navigation_output.add_output() = output; // Adiciona o output ao repeated output

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

        // robocin::ilog("Output: {}", output.DebugString());
        return navigation_output; // Criar objeto do protobuf navigation aqui

      }
    }
    case rc::Behavior::kPlanning: {
      // robocin::ilog("Planning: {}", last_behavior_->planning().DebugString());
      const rc::PlanningList& planningList = last_behavior_->planning();
      // Adicione aqui o processamento específico para Planning
      break;
    }
    case rc::Behavior::kNavigation: {
      // robocin::ilog("Navigation: {}", last_behavior_->navigation().DebugString());
      const rc::NavigationList& navigationList = last_behavior_->navigation();
      // Adicione aqui o processamento específico para Navigation
      break;
    }
    case rc::Behavior::OUTPUT_NOT_SET: {
      // robocin::ilog("Output not set");
      rc::Output output;         
      rc::RobotId *robot_id = output.mutable_id();
      robot_id->CopyFrom(last_behavior_->id());
      *navigation_output.add_output() = output;
      return navigation_output; 
    } 
  }

  return std::nullopt;
}

} // namespace navigation
