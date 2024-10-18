#include "behavior/messaging/receiver/payload.h"

namespace behavior {
namespace {

namespace rc {

using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

} // namespace

Payload::Payload(std::vector<rc::Detection> detections, std::vector<rc::GameStatus> game_statuses) :
    detections_{std::move(detections)},
    game_statuses_{std::move(game_statuses)} {}

std::span<const rc::Detection> Payload::getDetectionPackets() const { return detections_; }

std::span<const rc::GameStatus> Payload::getGameStatusPackets() const { return game_statuses_; }

bool Payload::empty() const { return detections_.empty() and game_statuses_.empty(); }

} // namespace behavior
