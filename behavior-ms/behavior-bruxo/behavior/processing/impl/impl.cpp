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

std::optional<rc::Behavior> onInGame(World& world) {
  BehaviorMessage behavior_message;

  // Take forward
  robocin::ilog("Allies detected: {}", world.allies.size());
  int forward_number = 10;

  auto robot = findMyRobot(forward_number, world.allies);
  if (!robot.has_value()) {
    ilog("Robot with id {} not found from detection packets.", forward_number);
    return std::nullopt;
  }

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
        false /* charge_capacitor -> makeChargeCapacitor based on distance to ball */,
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

  return behavior_message.toProto();
};

std::optional<rc::Behavior> onHalt() { return std::nullopt; };

} // namespace impl

} // namespace behavior
