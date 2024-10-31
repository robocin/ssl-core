#include "communication/processing/communication_processor.h"

#include "communication/messaging/receiver/payload.h"
#include "communication/processing/messages/common/message_type/message_type.h"

#include <cstddef>
#include <protocols/communication/robot_info.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <ranges>

namespace communication {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {

using ::protocols::communication::Output;
using ::protocols::communication::RobotInfo;
using ::protocols::navigation::Navigation;

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

std::optional<rc::RobotInfo> CommunicationProcessor::process(std::span<const Payload> payloads) {

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
  rc::Navigation last_navigation_ = navigation.back();

  ///////////////////////////////////////////////////////////////////////////
  CommunicationMessage communication_message;

  for (const auto& navigation : navigation) {
    communication_message.output_messages.emplace_back(
        OutputMessage{CommandMessage{MessageTypeMessage{},
                                     RobotIdMessage{},
                                     RobotVelocityMessage{},
                                     RobotKickMessage{},
                                     RobotDribblerMessage{},
                                     FlagsMessage{}}});
  }
  ///////////////////////////////////////////////////////////////////////////
  return communication_message.toProto();
}

} // namespace communication
