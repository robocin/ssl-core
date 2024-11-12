#include "behavior/processing/impl/impl.h"

namespace behavior {

namespace parameters = ::robocin::parameters;

namespace {

using ::robocin::ilog;

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

} // namespace

namespace impl {

// Takes
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

std::optional<RobotMessage> takeForward(std::vector<RobotMessage>& robots) {
  return impl::findMyRobot(pForwardNumber(), robots);
}

std::optional<RobotMessage> takeGoalkeeper(std::vector<RobotMessage>& robots) {
  return impl::findMyRobot(pGoalkeeperNumber(), robots);
};

std::optional<RobotMessage> takeSupport(std::vector<RobotMessage>& robots) {
  return impl::findMyRobot(pSupportNumber(), robots);
};

void emplaceForwardOutput(RobotMessage& forward, World& world, BehaviorMessage& behavior_message) {
  // Ball 2D is required because .angle() method is implemented from a Point2Df object.
  auto ball_2_d = robocin::Point2Df(world.ball.position->x, world.ball.position->y);
  auto target_angle = (ball_2_d - forward.position.value()).angle();
  bool shouldKick = true;

  // process should kick
  std::optional<PeripheralActuationMessage> peripheral_actuation = std::nullopt;
  if (shouldKick) {
    peripheral_actuation = std::move(PeripheralActuationMessage{KickCommandMessage{
        7.0 /* strength */,
        true /* is_front */,
        false /* is_chip */,
        false /* charge_capacitor -> makeChargeCapacitor based on distance to ball */,
        false /* bypass_ir */
    }});
  }

  // Always send go to point
  behavior_message.output.emplace_back(
      RobotIdMessage{pAllyColor, pForwardNumber()},
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

void emplaceSupportOutput(RobotMessage& support, World& world, BehaviorMessage& behavior_message) {
};

void emplaceGoalkeeperOutput(RobotMessage& goalkeeper,
                             World& world,
                             BehaviorMessage& behavior_message) {};

// Game running
std::optional<rc::Behavior> onInGame(World& world) {
  BehaviorMessage behavior_message;
  robocin::ilog("Allies detected: {}", world.allies.size());

  // Take forward
  auto forward = takeForward(world.allies);
  if (forward.has_value()) {
    emplaceForwardOutput(forward.value(), world, behavior_message);
  }

  // Take goalkeeper
  auto goalkeeper = takeGoalkeeper(world.allies);
  if (goalkeeper.has_value()) {
    emplaceGoalkeeperOutput(goalkeeper.value(), world, behavior_message);
  }

  // Take support
  auto support = takeSupport(world.allies);
  if (!support.has_value()) {
    emplaceSupportOutput(support.value(), world, behavior_message);
  }

  return behavior_message.toProto();
};

std::optional<rc::Behavior> onHalt() { return std::nullopt; };

} // namespace impl

} // namespace behavior
