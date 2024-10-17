#include "decision/messaging/receiver/payload.h"

namespace decision {
namespace {

namespace tp {

using ::protocols::perception::DetectionWrapper;
using ::protocols::referee::GameStatus;

} // namespace tp

} // namespace

Payload::Payload(std::vector<tp::DetectionWrapper> detections,
                 std::vector<tp::GameStatus> game_statuses) :
    detections_{std::move(detections)},
    game_statuses_{std::move(game_statuses)} {}

std::span<const tp::DetectionWrapper> Payload::getDetections() const { return detections_; }

std::span<const tp::GameStatus> Payload::getGameStatuses() const { return game_statuses_; }

bool Payload::empty() const { return detections_.empty() and game_statuses_.empty(); }

} // namespace decision
