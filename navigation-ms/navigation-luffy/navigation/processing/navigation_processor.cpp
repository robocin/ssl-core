#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <ranges>
#include "motion_parser/MotionParser.h"

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

  rc::Behavior last_behavior = behaviors.back();

  MotionParser motion_parser{};

  switch (behavior.output_case()) {
    case Behavior::kMotion: {
      const Motion& motion = behavior.motion();
      RobotMove robot_move = motion_parser.parse(motion);
      break;
    }
    case Behavior::kPlanning: {
      const navigation::Planning& planning = behavior.planning();
      // Adicione aqui o processamento específico para Planning
      break;
    }
    case Behavior::kNavigation: {
      const navigation::Navigation& navigation = behavior.navigation();
      // Adicione aqui o processamento específico para Navigation
      break;
    }
    case Behavior::OUTPUT_NOT_SET:
      return std::nullopt;
      break ;
  }



  return;
}

} // namespace navigation
