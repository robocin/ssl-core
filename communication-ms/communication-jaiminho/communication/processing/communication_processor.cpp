#include "communication/processing/communication_processor.h"

#include "communication/communication_message.h"
#include "communication/messaging/receiver/payload.h"
#include "communication/parameters/parameters.h"
#include "communication/processing/messages/common/message_type/message_type.h"

#include <protocols/navigation/navigation.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/third_party/simulation/robot_control.pb.h>
#include <ranges>
#include <robocin/output/log.h>
#include <vector>

namespace communication {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {
using ::protocols::communication::Communication;
using ::protocols::communication::OutputRobot;
using ::protocols::navigation::Navigation;
using ::protocols::perception::Detection;
using ::robocin::ilog;

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
CommunicationProcessor::processSimulator(std::span<const Payload> payloads) {

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

  for (auto navigation : last_navigation.output()) {
    tp::RobotCommand* ith_robot_command = robot_control.add_robot_commands();

    ith_robot_command->set_id(navigation.robot_id().number());

    tp::RobotMoveCommand* ith_move_command = ith_robot_command->mutable_move_command();

    tp::MoveLocalVelocity* ith_move_local_velocity = ith_move_command->mutable_local_velocity();
    ith_move_local_velocity->set_forward(navigation.forward_velocity());
    ith_move_local_velocity->set_left(navigation.left_velocity());
    ith_move_local_velocity->set_angular(navigation.angular_velocity());

    ith_robot_command->set_kick_speed(
        navigation.peripheral_actuation().kick_command().kick_strength());
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
    communication_message.commands.emplace_back(OutputRobotMessage{
        navigation.robot_id().number(),
        navigation.forward_velocity(),
        navigation.left_velocity(),
        navigation.angular_velocity(),
        navigation.peripheral_actuation().kick_command().is_front(),
        navigation.peripheral_actuation().kick_command().is_chip(),
        navigation.peripheral_actuation().kick_command().charge_capacitor(),
        navigation.peripheral_actuation().kick_command().kick_strength(),
        false /* dribbler always off */,
        0.0 /* dribbler speed unused */
    });
  }
  ///////////////////////////////////////////////////////////////////////////
  return communication_message.toProto();
}

} // namespace communication
