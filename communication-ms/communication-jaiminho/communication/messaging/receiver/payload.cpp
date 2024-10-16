#include "communication/messaging/receiver/payload.h"

namespace communication {
namespace {

namespace rc {

using ::protocols::navigation::Navigation;

} // namespace rc

} // namespace

Payload::Payload(std::vector<rc::Navigation> navigation) :
    navigation_{std::move(navigation)} {}

std::span<const rc::Detection> Payload::getNavigation() const { return navigation_; }

std::span<const rc::Referee> Payload::getReferee() const { return referee_; }

bool Payload::empty() const { return navigation_.empty(); }

} // namespace communication
