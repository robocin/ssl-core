#include "behavior/processing/state_machine/forward_follow_and_kick_ball/states/align.h"

#include "behavior/parameters/parameters.h"
#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"
#include "behavior/processing/state_machine/goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h"

#include <robocin/geometry/point2d.h>

namespace behavior {

Align::Align() = default;

OutputMessage Align::exec(const World& world, RobotIdMessage& ally_id) {
  robocin::ilog("Exec Align state");
  ally_id_ = std::move(ally_id);
  robocin::Point2Df ball_position = world.field.allyGoalInsideBottom();
  std::cout << " ball position in goalkeeper fsm: " << ball_position.x << " " << ball_position.y
            << std::endl;
  checkAndHandleTransitions(world);
  return makeAlignOutput(world);
}

void Align::checkAndHandleTransitions(const World& world) {
  if (shouldTransitionToGoToBall(world)) {
    state_machine_->transitionTo(new GoToBall);
    return;
  }
  if (shouldTransitionToKickBall(world)) {
    state_machine_->transitionTo(new KickBall);
    return;
  }
}

bool Align::shouldTransitionToGoToBall(const World& world) const {
  return (!ForwardFollowAndKickBallCommon::isAllyBehindBall(world, ally_id_.number.value())
          || ForwardFollowAndKickBallCommon::allyLostBall(world, ally_id_.number.value())
          || ForwardFollowAndKickBallCommon::isBallInsideEnemyArea(world));
}

bool Align::shouldTransitionToKickBall(const World& world) const {
  return ForwardFollowAndKickBallCommon::isAllyNotLookingToTargetAndBall(world,
                                                                         ally_id_.number.value())
         && ForwardFollowAndKickBallCommon::isBallInRangeToKick(world, ally_id_.number.value());
}

robocin::Point2Df KickBall::getMotionTarget(const World& world) const {
  std::optional<RobotMessage> ally
      = ForwardFollowAndKickBallCommon::getAlly(world, ally_id_.number.value());
  if (!ally.has_value()) {
    return {0.0f, 0.0f};
  }
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  robocin::Point2Df ally_position = ally->position.value();
  robocin::Point2Df kick_target = ForwardFollowAndKickBallCommon::getKickTarget();

  robocin::Line kick_target_to_ball_line = {kick_target, ball_position};
  robocin::Point2Df target_point = ally_position.projectedOntoLine(kick_target_to_ball_line.p1(),
                                                                   kick_target_to_ball_line.p2());
  robocin::Point2Df ball_to_target_point_vector = target_point - ball_position;

  float original_size = ball_to_target_point_vector.norm();
  const float FACTOR_TO_MULTIPLY_TOTAL_DIST = 0.85;
  float vector_size
      = std::clamp(original_size,
                   static_cast<float>(1.5 * pRobotRadius()),
                   ForwardFollowAndKickBallCommon::DISTANCE_TO_CONSIDER_IN_RANGE_TO_KICK_BALL
                       * FACTOR_TO_MULTIPLY_TOTAL_DIST);

  target_point = ball_position + ball_to_target_point_vector.resized(vector_size);

  return target_point;
}

float KickBall::getMotionAngle(const World& world) const {
  robocin::Point2Df kick_target = ForwardFollowAndKickBallCommon::getKickTarget();
  robocin::Point2Df ball_position
      = robocin::Point2Df{world.ball.position->x, world.ball.position->y};
  return (kick_target - ball_position).angle();
}

GoToPointMessage::MovingProfile Align::getMotionMovingProfile(const World& world) const {
  return GoToPointMessage::MovingProfile{};
}

OutputMessage Align::makeAlignOutput(const World& world) {
  return OutputMessage{RobotIdMessage{makeAlignRobotId(world)},
                       MotionMessage{makeAlignMotion(world)},
                       PlanningMessage{makeAlignPlanning(world)}};
}

RobotIdMessage Align::makeAlignRobotId(const World& world) {
  // TODO(mlv): Create the robot id message
  return std::move(ally_id_);
}

MotionMessage Align::makeAlignMotion(const World& world) {
  // TODO(mlv): Create the motion message
  GoToPointMessage go_to_point = GoToPointMessage{getMotionTarget(world),
                                                  getMotionAngle(world),
                                                  getMotionMovingProfile(world)};
  return MotionMessage{std::move(go_to_point)};
};

PlanningMessage Align::makeAlignPlanning(const World& world) {
  // TODO(mlv): Create the planning message
  return PlanningMessage{};
}
}; // namespace behavior
