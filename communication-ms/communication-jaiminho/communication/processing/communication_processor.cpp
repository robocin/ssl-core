#include "communication/processing/communication_processor.h"

#include "communication/messaging/receiver/payload.h"

#include <protocols/communication/robot_info.pb.h>
#include <protocols/navigation/navigation.pb.h>

#include <ranges>

namespace communication {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {

using ::protocols::communication::RobotInfo;
using ::protocols::navigation::Navigation;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;

} // namespace tp

// std::vector<rc::Navigation> navigationFromPayloads(std::span<const Payload> payloads) {
//     return payloads | std::views::transform(&Payload::getNavigation) | std::views::join
//             | std::ranges::to<std::vector>();
// }

std::vector<tp::Referee> refereeFromPayloads(std::span<const Payload> payloads) {
    return payloads | std::views::transform(&Payload::getReferee) | std::views::join
            | std::ranges::to<std::vector>();

}

} // namespace

CommunicationProcessor::CommunicationProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine,
    std::unique_ptr<IRobotCommandMapper> robot_command_mapper):
    parameters_handler_engine_{std::move(parameters_handler_engine)},
    robot_command_mapper_{std::move(robot_command_mapper)} {}

std::optional<rc::RobotInfo> CommunicationProcessor::process(std::span<const Payload> payloads) {

    if(std::vector<tp::Referee> referees = refereeFromPayloads(payloads); !referees.empty()) {
        last_game_controller_referee_ = std::move(referees.back());
    }

    // std::vector<rc::Navigation> navigation = navigationFromPayloads(payloads);
    // if(navigation.empty()) {
    //     return std::nullopt;
    // }

    // const rc::Navigation last_navigation = navigation.back();

    return robot_command_mapper_->fromNavigationAndReferee(*last_game_controller_referee_);
}

} // namespace communication
