#include "communication/processing/communication_processor.h"

#include "communication/communication_message.h"
#include "communication/messaging/receiver/payload.h"
#include "communication/processing/messages/common/message_type/message_type.h"

#include <protocols/navigation/navigation.pb.h>
#include <ranges>
#include <robocin/output/log.h>

namespace communication {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {
using ::protocols::communication::Communication;
using ::protocols::communication::OutputRobot;
using ::protocols::navigation::Navigation;
using ::robocin::ilog;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;

} // namespace tp

std::vector<rc::Navigation> navigationFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getNavigation) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<tp::Referee> refereeFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getReferee) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

CommunicationProcessor::CommunicationProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)} {}

std::optional<rc::Communication>
CommunicationProcessor::process(std::span<const Payload> payloads) {
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
        navigation.peripheral_actuation().kick_command().charge_capacitor(), /* always false */
        navigation.peripheral_actuation().kick_command().kick_strength(),
        false /* dribbler always off */,
        0.0 /* dribbler speed unused */
    });
  }
  ///////////////////////////////////////////////////////////////////////////
  return communication_message.toProto();
}

} // namespace communication
