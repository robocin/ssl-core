#include "communication/processing/communication_processor.h"

#include "communication/communication_message.h"
#include "communication/messaging/receiver/payload.h"
#include "communication/parameters/parameters.h"
#include "communication/processing/messages/common/message_type/message_type.h"

#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/third_party/simulation/robot_control.pb.h>
#include <ranges>
#include <vector>

namespace communication {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {

using ::protocols::communication::Communication;
using ::protocols::communication::OutputRobot;
using ::protocols::navigation::Navigation;
using ::protocols::perception::Detection;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;
using ::protocols::third_party::simulation::MoveLocalVelocity;
using ::protocols::third_party::simulation::RobotCommand;
using ::protocols::third_party::simulation::RobotControl;
using ::protocols::third_party::simulation::RobotMoveCommand;

} // namespace tp

std::vector<rc::Navigation> navigationFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getNavigation) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<tp::Referee> refereeFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getReferee) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetections) | std::views::join
         | std::ranges::to<std::vector>();
}
} // namespace

CommunicationProcessor::CommunicationProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)} {}

std::optional<tp::RobotControl>
CommunicationProcessor::processSimulator(std::span<const Payload> payloads){

  if (std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
      !detection_messages.empty()) {
    last_detection_ = detection_messages.back();
  }

  if (!last_detection_) {
    return std::nullopt;
  }

  if (std::vector<tp::Referee> referees = refereeFromPayloads(payloads); !referees.empty()) {
    last_game_controller_referee_ = std::move(referees.back());
  }

  if (!last_game_controller_referee_) {
    return std::nullopt;
  }

  std::vector<rc::Navigation> navigation = navigationFromPayloads(payloads);
  if (navigation.empty()) {
    return std::nullopt;
  }
  rc::Navigation last_navigation = navigation.back();

  ///////////////////////////////////////////////////////////////////////////

  tp::RobotControl robot_control;

  for (const auto& robot : last_detection_->robots()) {
    tp::RobotCommand* robot_command = robot_control.add_robot_commands();
    robot_command->set_id(robot.robot_id().number());

    tp::MoveLocalVelocity* move_local_velocity
        = robot_command->mutable_move_command()->mutable_local_velocity();
    move_local_velocity->set_forward(0.0);
    move_local_velocity->set_left(0.0);
    move_local_velocity->set_angular(3.0);
  }

  robocin::ilog("RobotControl: {}", robot_control.DebugString());
  return robot_control;

}

std::optional<rc::Communication>
CommunicationProcessor::processReal(std::span<const Payload> payloads) {

  if (std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
      !detection_messages.empty()) {
    last_detection_ = detection_messages.back();
  }

  if (!last_detection_) {
    return std::nullopt;
  }

  if (std::vector<tp::Referee> referees = refereeFromPayloads(payloads); !referees.empty()) {
    last_game_controller_referee_ = std::move(referees.back());
  }

  if (!last_game_controller_referee_) {
    return std::nullopt;
  }

  std::vector<rc::Navigation> navigation = navigationFromPayloads(payloads);
  if (navigation.empty()) {
    return std::nullopt;
  }
  rc::Navigation last_navigation = navigation.back();

  ///////////////////////////////////////////////////////////////////////////
  CommunicationMessage communication_message;

  for (const auto& navigation : last_navigation.output()) {
    communication_message.commands.emplace_back(OutputRobotMessage{});
  }
  ///////////////////////////////////////////////////////////////////////////
  return communication_message.toProto();
}

} // namespace communication
