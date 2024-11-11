#include "navigation/processing/utils/moving_profile_util.h"

#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/motion/motion_message.h"

namespace navigation {

std::pair<float, float>
MovingProfileUtil::minAndMaxVelocityToProfile(GoToPointMessage::MovingProfile profile) {
  switch (profile) {
    case GoToPointMessage::MovingProfile::DirectApproachBallSpeed:
      return {moving_profile::APPROACH_BALL_MIN_SPEED, moving_profile::APPROACH_BALL_MAX_SPEED};

    case GoToPointMessage::MovingProfile::DirectKickBallwithEnemyClose:
      return {moving_profile::KICK_BALL_WITH_ENEMY_MIN_SPEED,
              moving_profile::KICK_BALL_WITH_ENEMY_MAX_SPEED};

    case GoToPointMessage::MovingProfile::DirectSafeKickBallSpeed:
    case GoToPointMessage::MovingProfile::DirectBalancedKickBallSpeed:
      return {moving_profile::KICK_BALL_MIN_SPEED, moving_profile::KICK_BALL_MAX_SPEED};

    case GoToPointMessage::MovingProfile::TOTOZINHO:
      return {moving_profile::TOTOZINHO_MIN_SPEED, moving_profile::TOTOZINHO_MAX_SPEED};
    default: return {moving_profile::ALLY_MIN_SPEED, moving_profile::ALLY_MAX_SPEED};
  }
}

float MovingProfileUtil::propDistanceToProfile(GoToPointMessage::MovingProfile profile) {

  switch (profile) {
    case GoToPointMessage::MovingProfile::DirectApproachBallSpeed:
      return moving_profile::APPROACH_BALL_PROP_DISTANCE;

    case GoToPointMessage::MovingProfile::DirectSafeKickBallSpeed:
      return moving_profile::KICK_BALL_SAFE_PROP_DISTANCE;

    case GoToPointMessage::MovingProfile::DirectBalancedKickBallSpeed:
      return moving_profile::KICK_BALL_BALANCED_PROP_DISTANCE;
    default: return moving_profile::MIN_DIST_TO_PROP_VELOCITY;
  }
}
} // namespace navigation
