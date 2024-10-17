#include "communication/messaging/receiver/payload.h"

namespace communication {
namespace {

namespace rc {

using ::protocols::navigation::Navigation;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;

} // namespace tp

} // namespace

Payload::Payload(std::vector<rc::Navigation> navigation,
                 std::vector<tp::Referee> referee) :
    navigation_{std::move(navigation)},
    referee_{std::move(referee)} {}

std::span<const rc::Navigation> Payload::getNavigation() const { return navigation_; }

std::span<const tp::Referee> Payload::getReferee() const { return referee_; }

bool Payload::empty() const { return navigation_.empty(); }

} // namespace communication
