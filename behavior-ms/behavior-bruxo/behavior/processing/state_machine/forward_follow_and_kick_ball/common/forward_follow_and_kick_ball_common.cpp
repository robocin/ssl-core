#include "behavior/processing/state_machine/forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"

namespace behavior {

std::optional<RobotMessage> ForwardFollowAndKickBallCommon::getAlly(const World& world, int id) {
  for (const auto& ally : world.allies) {
    if (ally.robot_id.value().number == id) {
      return RobotMessage{
          ally.confidence.value(),
          RobotIdMessage{ally.robot_id->color.value(), ally.robot_id->number.value()},
          ally.position.value(),
          ally.angle.value(),
          ally.velocity.value(),
          ally.angular_velocity.value(),
          ally.radius.value(),
          ally.height.value(),
          ally.dribbler_width.value(),
          std::nullopt /* Feedback */};
    }
  }
  return std::nullopt;
}

void ForwardFollowAndKickBallCommon::setKickTarget(robocin::Point2Df kick_target) {
  kick_target_ = kick_target;
}

bool ForwardFollowAndKickBallCommon::isAllyBehindBall(const World& world, const int ally_id) {
  return AllyAnalyzer::isAllyBehindBall(world, ally_id, kick_target_, ANGLE_FAR_TO_KICK_LINE);
}

bool ForwardFollowAndKickBallCommon::allyLostBall(const World& world, int ally_id) {
  return AllyAnalyzer::lostBall(world, ally_id);
}

bool ForwardFollowAndKickBallCommon::isBallInsideEnemyArea(const World& world) {
  return BallAnalyzer::isBallInsideEnemyArea(world.field, world.ball);
}

bool ForwardFollowAndKickBallCommon::isAllyNotLookingToTargetAndBall(const World& world,
                                                                     const int ally_id) {
  return !AllyAnalyzer::isLookingToTargetAndBall(world,
                                                 ally_id,
                                                 kick_target_,
                                                 ANGLE_CLOSE_TO_KICK_LINE_UPPER);
}

bool ForwardFollowAndKickBallCommon::isBallOnDribblerWithoutCheckingForAlignment(
    const World& world,
    const int ally_id) {
  return AllyAnalyzer::isBallOnDribblerWithoutCheckingForAlignment(
      world,
      ally_id,
      ANGLE_TO_DRIBBLER_SIDE,
      DISTANCE_TO_CONSIDER_TOO_CLOSE_TO_BALL);
}

bool ForwardFollowAndKickBallCommon::isBallInRangeToKick(const World& world, const int ally_id) {
  return AllyAnalyzer::isBallInRangeToKick(world,
                                           ally_id,
                                           DISTANCE_TO_CONSIDER_IN_RANGE_TO_KICK_BALL);
}
bool ForwardFollowAndKickBallCommon::isAllyLookingToTargetAndBall(const World& world,
                                                                  const int ally_id) {
  return AllyAnalyzer::isLookingToTargetAndBall(world,
                                                ally_id,
                                                kick_target_,
                                                ANGLE_CLOSE_TO_KICK_LINE_LOWER);
}

} // namespace behavior
