#include "behavior/processing/impl/impl.h"

#include "ally_analyzer.h"
#include "ball_analyzer.h"
#include "behavior/parameters/parameters.h"
#include "behavior/processing/messages/common/game_event/game_event_message.h"
#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"
#include "behavior/processing/state_machine/istate_machine.h"
#include "common/peripheral_actuation/peripheral_actuation.h"
#include "field_analyzer.h"
#include "forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.h"
#include "goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"
#include "perception/ball/ball_message.h"

#include <robocin/geometry/mathematics.h>
#include <robocin/geometry/point2d.h>

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

constinit float kDistanceToBallToStopChargingCapacitorMM = 200.0;

// Logic
bool makeChargeCapacitor(RobotMessage& robot, World& world) {
  // Always charges capacitor, stops charging when gets near the ball
  robocin::Point2Df ball_position_2_d{world.ball.position.value().x, world.ball.position.value().y};
  auto distance_to_ball = robot.position.value().distanceTo(ball_position_2_d);

  if (distance_to_ball > kDistanceToBallToStopChargingCapacitorMM) {
    return true;
  }

  return false;
}

bool makeShouldKick(RobotMessage& robot, World& world) {
  // implement
  return true;
}

float makeKickStrength(RobotMessage& robot, World& world) {
  // implement
  return 6.0;
}

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
  // std::cout << " ball position in forward: " << ball_2_d.x << " " << ball_2_d.y << std::endl;
  auto target_angle = (ball_2_d - forward.position.value()).angle();
  bool shouldKick = makeShouldKick(forward, world);

  // process should kick
  std::optional<PeripheralActuationMessage> peripheral_actuation = std::nullopt;
  if (shouldKick) {
    peripheral_actuation = std::move(PeripheralActuationMessage{KickCommandMessage{
        makeKickStrength(forward, world), /* strength */
        true /* is_front */,
        false /* is_chip */,
        makeChargeCapacitor(forward, world),
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
  robocin::Point2Df ball_position
      = robocin::Point2Df(world.ball.position->x, world.ball.position->y);
  auto&& field = world.field;

  std::vector<robocin::Point2Df> goalkeeper_area = {field.allyPenaltyAreaGoalCornerTop(),
                                                    field.allyPenaltyAreaCornerTop(),
                                                    field.allyPenaltyAreaCornerBottom(),
                                                    field.allyPenaltyAreaGoalCornerBottom()};

  robocin::Line ball_to_our_goal_vector = {field.allyGoalOutsideCenter(), ball_position};

  robocin::Point2Df intersect_area_point = [&]() {
    for (int i = 0; i < 3; i++) {
      robocin::Line area_side = {goalkeeper_area[i], goalkeeper_area[i + 1]};
      std::optional<robocin::Point2Df> intersect
          = mathematics::segmentsIntersection(ball_to_our_goal_vector, area_side);
      if (intersect.has_value()) {
        return intersect.value();
      }
    }
    return field.allyPenaltyAreaCenter();
  }();

  robocin::Point2Df support_target_point = [&]() {
    if (!FieldAnalyzer::contains(ball_position, field)
        || FieldAnalyzer::allyPenaltyAreaContains(ball_position, field)
        || FieldAnalyzer::allyGoalContains(ball_position, field)) {
      return intersect_area_point + field.attackDirection().resized(pRobotDiameter());
    }
    return intersect_area_point + (ball_position - intersect_area_point).resized(pRobotDiameter());
  }();

  if (FieldAnalyzer::allyPenaltyAreaContains(support_target_point, field)) {
    support_target_point = intersect_area_point + field.attackDirection().resized(pRobotDiameter());
  }

  const float target_angle = (ball_position - support_target_point).angle();

  KickCommandMessage kick_message = [&]() {
    robocin::Point2Df robot_to_ball_vector = ball_position - support.position.value();

    bool robot_is_close_to_ball = ball_position.distanceTo(support.position.value()) < 300;
    bool robot_to_ball_is_looking_forward = robot_to_ball_vector.x && field.attackDirection().x > 0;

    bool should_kick = robot_is_close_to_ball && robot_to_ball_is_looking_forward;

    if (should_kick) {
      return KickCommandMessage{5, true, false, false, false};
    }
    return KickCommandMessage{0.0, false, false, true, false};
  }();

  std::optional<PeripheralActuationMessage> peripheral_message
      = PeripheralActuationMessage{std::move(kick_message)};

  support_target_point
      = AllyAnalyzer::safeTargetPoint(world, pSupportNumber(), support_target_point);

  auto forward = takeForward(world.allies);

  if (forward.has_value()) {
    robocin::Point2Df forward_position = forward->position.value();
    robocin::Point2Df support_position = support.position.value();
    if (support.position->distanceTo(forward_position) < pRobotDiameter()) {
      robocin::Point2Df support_to_forward_vector = forward_position - support_position;
      support_target_point
          = support_target_point - support_to_forward_vector.resized(3 * pRobotRadius());
    }
  }

  // Always send go to point
  behavior_message.output.emplace_back(
      RobotIdMessage{pAllyColor, pSupportNumber()},
      MotionMessage{GoToPointMessage{support_target_point,
                                     target_angle,
                                     GoToPointMessage::MovingProfile::BalancedInDefaultSpeed,
                                     GoToPointMessage::PrecisionToTarget::HIGH,
                                     true /* sync_rotate_with_linear_movement */},
                    std::nullopt /* go_to_point_with_trajectory */,
                    std::nullopt /* rotate_in_point */,
                    std::nullopt /* rotate_on_self */,
                    std::move(peripheral_message)});
};

void emplaceGoalkeeperOutput(RobotMessage& goalkeeper,
                             World& world,
                             BehaviorMessage& behavior_message,
                             GoalkeeperGuardStateMachine& guard_state_machine) {};

bool shouldTakeBallAway(World& world) {
  auto&& field = world.field;
  auto&& ball = world.ball;

  robocin::Point2Df ball_position = {ball.position.value().x, ball.position.value().y};

  bool is_ball_inside_area = FieldAnalyzer::allyPenaltyAreaContains(ball_position, field);
  bool is_ball_stopped = BallAnalyzer::isBallStopped(ball);
  bool is_ball_slowly = BallAnalyzer::isBallMovingSlowly(ball);
  bool is_ball_moving_away_from_our_goal = BallAnalyzer::isBallMovingToEnemySide(field, ball);

  std::cout << "is_ball_slowly " << is_ball_slowly  << std::endl;
  std::cout << "is_ball_inside_area " << is_ball_inside_area  << std::endl;


  bool shouldTakeBallAway
      = is_ball_inside_area
        && (is_ball_stopped or (is_ball_slowly && is_ball_moving_away_from_our_goal));

  return shouldTakeBallAway;
}

// Game running
std::optional<rc::Behavior>
onInGame(World& world,
         GoalkeeperGuardStateMachine& guard_state_machine,
         ForwardFollowAndKickBallStateMachine& follow_and_kick_ball_state_machine,
         GoalkeeperTakeBallAwayStateMachine& take_ball_away_state_machine) {
  BehaviorMessage behavior_message;
  // robocin::ilog("Allies detected: {}", world.allies.size());

  // Take forward
  auto forward = takeForward(world.allies);
  if (forward.has_value()) {
    follow_and_kick_ball_state_machine.run(world, forward->robot_id.value());
    behavior_message.output.emplace_back(std::move(follow_and_kick_ball_state_machine.output));
  }

  // Take goalkeeper
  auto goalkeeper = takeGoalkeeper(world.allies);
  if (goalkeeper.has_value()) {
    if (shouldTakeBallAway(world)) {
      take_ball_away_state_machine.run(world, goalkeeper->robot_id.value());
      behavior_message.output.emplace_back(std::move(take_ball_away_state_machine.output));
    } else {
      guard_state_machine.run(world, goalkeeper->robot_id.value());
      behavior_message.output.emplace_back(std::move(guard_state_machine.output));
    }
  }

  // Take support
  auto support = takeSupport(world.allies);
  if (support.has_value()) {
    emplaceSupportOutput(support.value(), world, behavior_message);
  }

  return behavior_message.toProto();
};

std::optional<rc::Behavior> onHalt(World& world) {
  BehaviorMessage behavior_message;

  auto goalkeeper = takeGoalkeeper(world.allies);
  if (goalkeeper.has_value()) {
    behavior_message.output.emplace_back(RobotIdMessage{pAllyColor, pGoalkeeperNumber()},
                                         MotionMessage{});
  }

  auto forward = takeForward(world.allies);
  if (forward.has_value()) {
    behavior_message.output.emplace_back(RobotIdMessage{pAllyColor, pForwardNumber()},
                                         MotionMessage{});
  }

  return behavior_message.toProto();
}

std::optional<rc::Behavior> onStop(World& world, GoalkeeperGuardStateMachine& guard_state_machine) {
  BehaviorMessage behavior_message;
  robocin::Point2Df ball_position
      = robocin::Point2Df(world.ball.position.value().x, world.ball.position.value().y);
  robocin::Point2Df ball_to_goal_center_vector
      = (world.field.allyGoalOutsideCenter() - ball_position);
  robocin::Point2Df forward_target
      = ball_position + ball_to_goal_center_vector.resized(1.5*pStopRadius());
  float target_angle = (ball_position - forward_target).angle();

  // Take forward
  auto forward = takeForward(world.allies);
  if (forward.has_value()) {
    behavior_message.output.emplace_back(
        RobotIdMessage{pAllyColor, pForwardNumber()},
        MotionMessage{GoToPointMessage{forward_target,
                                       target_angle,
                                       GoToPointMessage::MovingProfile::BalancedInSlowSpeed,
                                       GoToPointMessage::PrecisionToTarget::HIGH,
                                       true /* sync_rotate_with_linear_movement */},
                      std::nullopt /* go_to_point_with_trajectory */,
                      std::nullopt /* rotate_in_point */,
                      std::nullopt /* rotate_on_self */,
                      PeripheralActuationMessage{KickCommandMessage{
                          0.0, /* strength */
                          false /* is_front */,
                          false /* is_chip */,
                          true /* charge */,
                          false /* bypass_ir */
                      }}});
  }

  auto support = takeSupport(world.allies);
  if (support.has_value()) {
    emplaceSupportOutput(support.value(), world, behavior_message);
  }

  // Take goalkeeper
  auto goalkeeper = takeGoalkeeper(world.allies);
  if (goalkeeper.has_value()) {

    guard_state_machine.run(world, goalkeeper->robot_id.value());
    behavior_message.output.emplace_back(std::move(guard_state_machine.output));
  }

  return behavior_message.toProto();
};

std::optional<rc::Behavior> onAwayPenalty(World& world,
                                          GoalkeeperGuardStateMachine& guard_state_machine) {
  BehaviorMessage behavior_message;

  // Take goalkeeper
  auto goalkeeper = takeGoalkeeper(world.allies);
  if (goalkeeper.has_value()) {
    guard_state_machine.run(world, goalkeeper->robot_id.value());
    behavior_message.output.emplace_back(std::move(guard_state_machine.output));
  }

  // Take forward
  auto forward = takeForward(world.allies);
  if (forward.has_value()) {
    behavior_message.output.emplace_back(
        RobotIdMessage{pAllyColor, pForwardNumber()},
        MotionMessage{GoToPointMessage{world.field.enemyPenaltyAreaCornerTop(),
                                       0.0,
                                       GoToPointMessage::MovingProfile::DirectApproachBallSpeed,
                                       GoToPointMessage::PrecisionToTarget::HIGH,
                                       true /* sync_rotate_with_linear_movement */},
                      std::nullopt /* go_to_point_with_trajectory */,
                      std::nullopt /* rotate_in_point */,
                      std::nullopt /* rotate_on_self */,
                      PeripheralActuationMessage{KickCommandMessage{
                          0.0, /* strength */
                          false /* is_front */,
                          false /* is_chip */,
                          true /* charge */,
                          false /* bypass_ir */
                      }}});
  }

  return behavior_message.toProto();
};

std::optional<rc::Behavior> onPrepareHomePenalty(World& world,
                                                 GoalkeeperGuardStateMachine& guard_state_machine) {
  BehaviorMessage behavior_message;

  // Take goalkeeper
  auto goalkeeper = takeGoalkeeper(world.allies);
  if (goalkeeper.has_value()) {
    guard_state_machine.run(world, goalkeeper->robot_id.value());
    behavior_message.output.emplace_back(std::move(guard_state_machine.output));
  }

  // Take forward
  auto forward = takeForward(world.allies);
  if (forward.has_value()) {
    behavior_message.output.emplace_back(
        RobotIdMessage{pAllyColor, pForwardNumber()},
        MotionMessage{GoToPointMessage{world.field.enemyPenaltyAreaCenter(),
                                       0.0,
                                       GoToPointMessage::MovingProfile::DirectApproachBallSpeed,
                                       GoToPointMessage::PrecisionToTarget::HIGH,
                                       true /* sync_rotate_with_linear_movement */},
                      std::nullopt /* go_to_point_with_trajectory */,
                      std::nullopt /* rotate_in_point */,
                      std::nullopt /* rotate_on_self */,
                      PeripheralActuationMessage{KickCommandMessage{
                          0.0, /* strength */
                          false /* is_front */,
                          false /* is_chip */,
                          true /* charge */,
                          false /* bypass_ir */
                      }}});
  }

  auto support = takeSupport(world.allies);
  if (support.has_value()) {
    behavior_message.output.emplace_back(
        RobotIdMessage{pAllyColor, pSupportNumber()},
        MotionMessage{GoToPointMessage{world.field.enemyPenaltyAreaCornerBottom(),
                                       0.0,
                                       GoToPointMessage::MovingProfile::BalancedInSlowSpeed,
                                       GoToPointMessage::PrecisionToTarget::HIGH,
                                       true /* sync_rotate_with_linear_movement */},
                      std::nullopt /* go_to_point_with_trajectory */,
                      std::nullopt /* rotate_in_point */,
                      std::nullopt /* rotate_on_self */,
                      PeripheralActuationMessage{KickCommandMessage{
                          0.0, /* strength */
                          false /* is_front */,
                          false /* is_chip */,
                          true /* charge */,
                          false /* bypass_ir */
                      }}});
  }

  return behavior_message.toProto();
};

} // namespace impl
} // namespace behavior
