#include "navigation/messaging/receiver/payload.h"

namespace navigation {
namespace {

namespace rc {

using ::protocols::behavior::unification::Behavior;

} // namespace rc

} // namespace

Payload::Payload(std::vector<rc::Behavior> behaviors) :
    behaviors_{std::move(behaviors)} {}

std::span<const rc::Behavior> Payload::getBehaviors() const { return behaviors_; }


bool Payload::empty() const { return behaviors_.empty(); }

} // namespace navigation
