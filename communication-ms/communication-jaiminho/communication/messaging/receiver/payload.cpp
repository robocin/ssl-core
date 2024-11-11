#include "communication/messaging/receiver/payload.h"

#include <protocols/perception/detection.pb.h>

namespace communication {
namespace {

namespace rc {

using ::protocols::navigation::Navigation;
using ::protocols::perception::Detection;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;

} // namespace tp

} // namespace

Payload::Payload(std::vector<tp::Referee> referee,
                 std::vector<rc::Navigation> navigation,
                 std::vector<rc::Detection> detection) :
    referee_{std::move(referee)},
    navigation_{std::move(navigation)},
    detection_{std::move(detection)} {}

std::span<const rc::Navigation> Payload::getNavigation() const { return navigation_; }

std::span<const tp::Referee> Payload::getReferee() const { return referee_; }

std::span<const rc::Detection> Payload::getDetections() const { return detection_; }

bool Payload::empty() const {
  return referee_.empty() and navigation_.empty() and detection_.empty();
}

} // namespace communication
