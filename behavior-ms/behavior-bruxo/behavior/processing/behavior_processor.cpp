#include "behavior/processing/behavior_processor.h"

#include "behavior/behavior_message.h"
#include "behavior/messaging/receiver/payload.h"
#include "behavior/parameters/parameters.h"
#include "common/game_command/game_command_message.h"
#include "common/robot_id/robot_id.h"
#include "motion/motion_message.h"
#include "perception/robot/robot_message.h"
#include "state_machine/goalkeeper/goalkeeper_state_machine.h"
#include "state_machine/goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"

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

// CBR: function for every game command
void onRun(BehaviorMessage& behavior_message, World& world) {
  // Take forward
  int forward_number = 2;

  auto robot = findMyRobot(forward_number, world.allies);

  // Ball 2D is required because .angle() method is implemented from a Point2Df object.
  auto ball_2_d = robocin::Point2Df(world.ball.position->x, world.ball.position->y);
  auto target_angle = (ball_2_d - robot->position.value()).angle();
  bool shouldKick = true;

  // process should kick
  std::optional<PeripheralActuationMessage> peripheral_actuation = std::nullopt;
  if (shouldKick) {
    peripheral_actuation = std::move(PeripheralActuationMessage{KickCommandMessage{
        7.0 /* strength */,
        true /* is_front */,
        false /* is_chip */,
        true /* charge_capacitor */,
        false /* bypass_ir */
    }});
  }

  // Always send go to point
  behavior_message.output.emplace_back(
      RobotIdMessage{pAllyColor, forward_number},
      MotionMessage{
          GoToPointMessage{robocin::Point2Df{world.ball.position->x, world.ball.position->y},
                           target_angle,
                           GoToPointMessage::MovingProfile::DirectApproachBallSpeed,
                           GoToPointMessage::PrecisionToTarget::HIGH,
                           true /* sync_rotate_with_linear_movement */},
          std::nullopt /* go_to_point_with_trajectory */,
          std::nullopt /* rotate_in_point */,
          std::nullopt /* rotate_on_self */,
          std::move(peripheral_actuation)});
};

void onHalt() { /* Implement */ };

BehaviorProcessor::BehaviorProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine,
    std::unique_ptr<GoalkeeperTakeBallAwayStateMachine> goalkeeper_take_ball_away_state_machine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)},
    goalkeeper_take_ball_away_state_machine_{std::move(goalkeeper_take_ball_away_state_machine)} {}

std::optional<rc::Behavior> BehaviorProcessor::process(std::span<const Payload> payloads) {
  BehaviorProcessor::update(payloads);
  BehaviorMessage behavior_message;

  if (!world_.isStop()) {
    onRun(behavior_message, world_);
  }

  if (world_.isHalt()) {
    onHalt();
  }

  return behavior_message.toProto();
}

bool BehaviorProcessor::update(std::span<const Payload>& payloads) {
  if (std::vector<rc::GameStatus> game_status_messages = gameStatusFromPayloads(payloads);
      !game_status_messages.empty()) {
    last_game_status_ = game_status_messages.back();
  }

  if (!last_game_status_) {
    return false;
  }

  std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
  if (detection_messages.empty()) {
    // a new package must be generated only when a new detection is received.
    return false;
  }
  const rc::Detection last_detection = detection_messages.back();

  world_.update({last_detection.robots().begin(), last_detection.robots().end()},
                {last_detection.balls().begin(), last_detection.balls().end()},
                last_detection.field(),
                last_game_status_.value());

  return true;
}

} // namespace behavior
