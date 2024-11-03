#include "navigation/processing/utils/moving_profile_util.h"

namespace navigation {

std::pair<double, double>
MovingProfileUtil::minAndMaxVelocityToProfile(::protocols::behavior::MovingProfile profile) {
  switch (profile) {
    case ::protocols::behavior::MovingProfile::DirectApproachBallSpeed:
      return {moving_profile::APPROACH_BALL_MIN_SPEED, moving_profile::APPROACH_BALL_MAX_SPEED};

    case ::protocols::behavior::MovingProfile::DirectKickBallwithEnemyClose:
      return {moving_profile::KICK_BALL_WITH_ENEMY_MAX_SPEED,
              moving_profile::KICK_BALL_WITH_ENEMY_MIN_SPEED};

    case ::protocols::behavior::MovingProfile::DirectSafeKickBallSpeed:
    case ::protocols::behavior::MovingProfile::DirectBalancedKickBallSpeed:
      return {moving_profile::KICK_BALL_MIN_SPEED, moving_profile::KICK_BALL_MAX_SPEED};

    case ::protocols::behavior::MovingProfile::TOTOZINHO:
      return {moving_profile::TOTOZINHO_MIN_SPEED, moving_profile::TOTOZINHO_MAX_SPEED};
    default: return {moving_profile::ALLY_MIN_SPEED, moving_profile::ALLY_MAX_SPEED};
  }
}

double MovingProfileUtil::propDistanceToProfile(::protocols::behavior::MovingProfile profile) {

  switch (profile) {
    case ::protocols::behavior::MovingProfile::DirectApproachBallSpeed:
      return moving_profile::APPROACH_BALL_PROP_DISTANCE;

    case ::protocols::behavior::MovingProfile::DirectSafeKickBallSpeed:
      return moving_profile::KICK_BALL_SAFE_PROP_DISTANCE;

    case ::protocols::behavior::MovingProfile::DirectBalancedKickBallSpeed:
      return moving_profile::KICK_BALL_BALANCED_PROP_DISTANCE;
    default: return moving_profile::MIN_DIST_TO_PROP_VELOCITY;
  }
}
} // namespace navigation
