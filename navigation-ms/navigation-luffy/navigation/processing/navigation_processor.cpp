#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <ranges>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace {

namespace rc {

using ::protocols::behavior::unification::Behavior;
using ::protocols::navigation::Navigation;

} // namespace rc

std::vector<rc::Behavior> behaviorFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getBehaviors) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

NavigationProcessor::NavigationProcessor() {}

std::optional<rc::Navigation> NavigationProcessor::process(std::span<const Payload> payloads) {

  std::vector<rc::Behavior> behaviors = behaviorFromPayloads(payloads);
  if (behaviors.empty()) {
    // a new package must be generated only when a new behavior is received.
    return std::nullopt;
  }

  return;
}

} // namespace navigation
