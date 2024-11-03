#include "behavior/messaging/receiver/payload.h"

#include <protocols/referee/game_status.pb.h>

namespace behavior {
namespace {

namespace rc {

using ::protocols::decision::Decision;
using ::protocols::perception::Detection;
using ::protocols::referee::GameStatus;

} // namespace rc

} // namespace

Payload::Payload(std::vector<rc::Detection> detections,
                 std::vector<rc::Decision> decisions,
                 std::vector<rc::GameStatus> game_status) :
    detections_{std::move(detections)},
    decisions_{std::move(decisions)},
    game_status_{std::move(game_status)} {}

std::span<const rc::Detection> Payload::getDetectionMessages() const { return detections_; }

std::span<const rc::Decision> Payload::getDecisionMessages() const { return decisions_; }

std::span<const rc::GameStatus> Payload::getGameStatusMessages() const { return game_status_; }

bool Payload::empty() const { return detections_.empty() and decisions_.empty(); }

} // namespace behavior
