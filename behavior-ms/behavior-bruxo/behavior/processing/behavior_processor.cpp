#include "behavior/processing/behavior_processor.h"

#include "behavior/behavior_message.h"
#include "behavior/messaging/receiver/payload.h"
#include "behavior/parameters/parameters.h"
#include "common/game_command/game_command_message.h"
#include "common/robot_id/robot_id.h"
#include "motion/motion_message.h"
#include "perception/robot/robot_message.h"
#include "state_machine/goalkeeper/goalkeeper_state_machine.h"
#include "state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"

#include <optional>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>
#include <robocin/geometry/point2d.h>
#include <robocin/memory/object_ptr.h>
#include <robocin/output/log.h>
#include <vector>

namespace behavior {

namespace parameters = ::robocin::parameters;

namespace {

using ::robocin::ilog;
using ::robocin::object_ptr;

namespace rc {

using ::protocols::common::RobotId;
using ::protocols::decision::Decision;
using ::protocols::perception::Ball;
using ::protocols::perception::Detection;

using ::protocols::behavior::GoToPoint;
using ::protocols::behavior::unification::Behavior;
using ::protocols::behavior::unification::Motion;
using ::protocols::behavior::unification::Output;

using ::protocols::perception::Robot;

using ::protocols::referee::GameStatus;

} // namespace rc

std::optional<RobotMessage> findMyRobot(int number, std::vector<RobotMessage>& robots) {
  // This function does not handle a case where it does not find a robot
  for (auto& robot : robots) {
    auto number_match = robot.robot_id->number.value() == number;
    if (number_match) {
      return RobotMessage{
          robot.confidence.value(),
          RobotIdMessage{robot.robot_id->color.value(), robot.robot_id->number.value()},
          robot.position.value(),
          robot.angle.value(),
          robot.velocity.value(),
          robot.angular_velocity.value(),
          robot.radius.value(),
          robot.height.value(),
          robot.dribbler_width.value(),
          std::nullopt /* Feedback */};
    }
  }

  // Unreachble hopefully
  return std::nullopt;
}

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetectionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Decision> decisionfromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDecisionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::GameStatus> gameStatusFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getGameStatusMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

BehaviorProcessor::BehaviorProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine,
    std::unique_ptr<::behavior::GoalkeeperGuardStateMachine> goalkeeper_guard_state_machine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)},
    goalkeeper_guard_state_machine_{std::move(goalkeeper_guard_state_machine)} {}

std::optional<rc::Behavior> BehaviorProcessor::process(std::span<const Payload> payloads) {

  if (std::vector<rc::Decision> decision_messages = decisionfromPayloads(payloads);
      !decision_messages.empty()) {
    last_decision_ = decision_messages.back();
  }

  if (!last_decision_.has_value()) {
    return std::nullopt;
  }

  if (std::vector<rc::GameStatus> game_status_messages = gameStatusFromPayloads(payloads);
      !game_status_messages.empty()) {
    last_game_status_ = game_status_messages.back();
  }

  if (!last_game_status_.has_value()) {
    return std::nullopt;
  }

  std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
  if (detection_messages.empty()) {
    // a new package must be generated only when a new detection is received.
    return std::nullopt;
  }

  const rc::Detection last_detection = detection_messages.back();

  BehaviorMessage behavior_message;

  world_.update({last_detection.robots().begin(), last_detection.robots().end()},
                {last_detection.balls().begin(), last_detection.balls().end()},
                last_detection.field(),
                last_game_status_.value());

  // if (!world_.game_status.command->stop.has_value()) {
  //   auto robot = findMyRobot(2, world_.allies);
  //   if (robot.has_value()) {
  //     auto ball_2_d = robocin::Point2Df(world_.ball.position->x, world_.ball.position->y);
  //     auto target_angle = (ball_2_d - robot->position.value()).angle();

  //     behavior_message.output.emplace_back(
  //         RobotIdMessage{pAllyColor, 0},
  //         MotionMessage{
  //             GoToPointMessage{robocin::Point2Df{world_.ball.position->x,
  //             world_.ball.position->y},
  //                              target_angle,
  //                              GoToPointMessage::MovingProfile::DirectApproachBallSpeed,
  //                              GoToPointMessage::PrecisionToTarget::HIGH,
  //                              true /* sync_rotate_with_linear_movement */}});
  //   }
  // }
  goalkeeper_guard_state_machine_->run(RobotIdMessage{pAllyColor, 5});

  behavior_message.output.emplace_back(std::move(goalkeeper_guard_state_machine_->output));

  return behavior_message.toProto();
}

} // namespace behavior
