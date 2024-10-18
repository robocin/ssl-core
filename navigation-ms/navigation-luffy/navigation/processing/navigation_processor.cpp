#include "navigation/processing/navigation_processor.h"

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/motion.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/navigation/planning.pb.h>
#include <ranges>
#include <utility>

namespace navigation {

namespace parameters = ::robocin::parameters;

namespace rc {

using ::protocols::behavior::unification::Behavior;
using ::protocols::behavior::unification::Motion;
using ::protocols::navigation::Navigation;
using ::protocols::navigation::Planning;

} // namespace rc

namespace {

std::vector<rc::Behavior> behaviorFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getBehaviors) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

NavigationProcessor::NavigationProcessor(
    std::unique_ptr<GoToPointParser> go_to_point_parser,
    std::unique_ptr<RotateInPointParser> rotate_in_point_parser,
    std::unique_ptr<RotateOnSelfParser> rotate_on_self_parser) :
    go_to_point_parser_(std::move(go_to_point_parser)),
    rotate_in_point_parser_(std::move(rotate_in_point_parser)),
    rotate_on_self_parser_(std::move(rotate_on_self_parser)) {}

std::optional<rc::Navigation> NavigationProcessor::process(std::span<const Payload> payloads) {
  std::vector<rc::Behavior> behaviors = behaviorFromPayloads(payloads);

  if (behaviors.empty()) {
    // a new package must be generated only when a new behavior is received.
    return std::nullopt;
  }

  const rc::Behavior last_behavior = behaviors.back();

  switch (last_behavior.output_case()) {
    case rc::Behavior::kMotion: {
      const rc::Motion& motion = last_behavior.motion();
      if (motion.has_go_to_point()) {
        RobotMove robot_move = go_to_point_parser_->parse(motion);
        return robot_move; // Criar objeto do protobuf navigation aqui
      } else if (motion.has_rotate_in_point()) {
        RobotMove robot_move = rotate_in_point_parser_->parse(motion);
        return robot_move; // Criar objeto do protobuf navigation aqui
      } else if (motion.has_rotate_on_self()) {
        RobotMove robot_move = rotate_on_self_parser_->parse(motion);
        return robot_move; // Criar objeto do protobuf navigation aqui
      } else {
        // RobotMove robot_move = go_to_point_with_trajectory_parser_->parse(motion);
        // return robot_move; // Criar objeto do protobuf navigation aqui
      }
    }
    case rc::Behavior::kPlanning: {
      const rc::Planning& planning = last_behavior.planning();
      // Adicione aqui o processamento específico para Planning
      break;
    }
    case rc::Behavior::kNavigation: {
      const rc::Navigation& navigation = last_behavior.navigation();
      // Adicione aqui o processamento específico para Navigation
      break;
    }
    case rc::Behavior::OUTPUT_NOT_SET: return std::nullopt; break;
  }

  return;
}

} // namespace navigation
