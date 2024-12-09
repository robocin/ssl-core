#include "navigation/messaging/receiver/payload.h"

namespace navigation {
namespace {

namespace rc {

using ::protocols::behavior::unification::Behavior;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

} // namespace

Payload::Payload(std::vector<rc::Behavior> behaviors,
                 std::vector<rc::Detection> detections,
                 std::vector<rc::GameStatus> game_statuses) :
    behaviors_{std::move(behaviors)},
    detections_{std::move(detections)},
    game_statuses_{std::move(game_statuses)} {}

std::span<const rc::Behavior> Payload::getBehaviors() const { return behaviors_; }
std::span<const rc::Detection> Payload::getDetections() const { return detections_; }
std::span<const rc::GameStatus> Payload::getGameStatuses() const { return game_statuses_; }

bool Payload::empty() const {
  return behaviors_.empty() and detections_.empty() and game_statuses_.empty();
}

} // namespace navigation
