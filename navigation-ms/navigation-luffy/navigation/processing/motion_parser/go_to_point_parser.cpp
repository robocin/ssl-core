#include "go_to_point_parser.h"
#include "navigation/parameters/parameters.h"
#include "common/cpp/robocin/geometry/angles.h"
#include "common/cpp/robocin/geometry/math_lib.h"
#include <protocols/navigation/motion.pb.h>
#include <protocols/perception/detection.pb.h>
#include "navigation/processing/utils/move_task_state.h"
#include <regex>
#include "navigation/parameters/parameters.h"
#include "robocin/geometry/point2d.h"

namespace navigation {

::protocols::perception::Robot GoToPointParser::matchAlly(
    ::protocols::navigation::GoToPoint& motion,
    ::protocols::referee::GameStatus& game_status,
    ::protocols::perception::Detection& detection){

  for(auto robot : detection.robots()){
    if(motion.id().number() == robot.id().number()) //TODO: match team color
      return robot;
  }

}

RobotMove GoToPointParser::parse(
  const ::protocols::navigation::GoToPoint& motion,
  ::protocols::referee::GameStatus& game_status, 
  ::protocols::perception::Detection& detection) {

  MoveTaskState::moveTask;
  const auto& ally = this->matchAlly(motion, game_status, detection);

  auto&& s0 = ally.position();
  auto&& s = motion.target();
  auto deltaS = (s - s0) / M_TO_MM();

  const double kp = ANGLE_KP();
  const double maxAngularVel = ROBOT_MAX_ANGULAR_VELOCITY();

  auto [minVelocity, maxVelocity] = this->minAndMaxVelocityToProfile(motion.moving_profile());
  double propDistance = this->propDistanceToProfile(motion.moving_profile());

  if (deltaS.length() <= propDistance) {
    maxVelocity =
        std::max(::robocin::math::map(deltaS.length(), 0.0, propDistance, minVelocity, maxVelocity),
                  minVelocity);
  }

  double toleranceToTarget =
      motion.precisionToTarget() == ::protocols::navigation::PrecisionToTarget::High ?
          SMALL_TOLERANCE_TO_DESIRED_POSITION_M() :
          DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M();

  const double dTheta =
      ::robocin::angles::smallestAngleDiff<double>(ally.angle(), motion.targetAngle());

  if (deltaS.length() > toleranceToTarget) {
    
    // Uses an angle PID (only proportional for now), and first try to get in the right
    // angle, using only angular speed and then use linear speed to get into the point
    const double theta = deltaS.angle();
    double accProp = moving_profile::ROBOT_DEFAULT_LINEAR_ACCELERATION();
    auto v0 = ally.velocity() / M_TO_MM();
    auto v = Point2D::fromPolar(maxVelocity, theta);
    const double v0Decay = ::robocin::math::abs(Point2D::angleBetween(v, v0)) > 60_degrees ?
                                ROBOT_VEL_BREAK_DECAY_FACTOR() :
                                ROBOT_VEL_FAVORABLE_DECAY_FACTOR();

    // v = v0 + a*t
    v0 = v0 - (v0 * v0Decay) * CYCLE_STEP();

    auto accelerationRequired = Point2D((v.x() - v0.x()) / CYCLE_STEP(),
                                      (v.y() - v0.y()) / CYCLE_STEP());

    double alpha = ::robocin::math::map(::robocin::math::abs(dTheta), 0.0, PI, 0.0, 1.0);
    // -x^2 +1
    // double propFactor = (-(alpha * alpha) + 1);

    // (x -1)^2
    double propFactor = (alpha - 1) * (alpha - 1);
    accProp *= propFactor;

    if (accelerationRequired.length() > accProp) {
      accelerationRequired.resize(accProp);
    }

    // v = v0 + a*t
    auto newVelocity = v0 + accelerationRequired * CYCLE_STEP();

    if (newVelocity.length() < ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY()) {
      newVelocity.resize(ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY());
    }

    if (is_in(moveTask.currentState(),
                SkillMoveState::Unknown,
                SkillMoveState::Started,
                SkillMoveState::ChangedTarget)) {
        moveTask.resetRunningToTargetTimer();
    }

      // debug
    moveTask.updateState(ally,
                        game_status_.command(),
                        motion,
                        ::protocols::navigation::PathNode(motion.target(), {0, 0}, 0));


    return RobotMove{newVelocity, ::robocin::math::bound(kp * dTheta, -maxAngularVel, maxAngularVel)};

  } else {

    return RobotMove{{0, 0}, ::robocin::math::bound(kp * dTheta, -maxAngularVel, maxAngularVel)};
  }
}

inline static std::pair<double, double> GoToPointParser::
  minAndMaxVelocityToProfile(rc::MovingProfile& profile) {
    switch(profile.type_case()){
      case rc::MovingProfile::kDirectApproachBallSpeed:
        return {moving_profile::APPROACH_BALL_MIN_SPEED(),
              moving_profile::APPROACH_BALL_MAX_SPEED()};

      case rc::MovingProfile::kDirectKickBallwithEnemyClose:
        return {moving_profile::KICK_BALL_WITH_ENEMY_MAX_SPEED(),
              moving_profile::KICK_BALL_WITH_ENEMY_MIN_SPEED()};

      case rc::MovingProfile::kDirectSafeKickBallSpeed:
      case rc::MovingProfile::kDirectBalancedKickBallSpeed:
        return {moving_profile::KICK_BALL_MIN_SPEED(),
              moving_profile::KICK_BALL_MAX_SPEED()};

      case rc::MovingProfile::kTOTOZINHO:
        return {moving_profile::TOTOZINHO_MIN_SPEED(),
              moving_profile::TOTOZINHO_MAX_SPEED()};
      case default:
        return {moving_profile::ALLY_MIN_SPEED(), moving_profile::ALLY_MAX_SPEED()};
    }

  }

  inline static double GoToPointParser::
    propDistanceToProfile(rc::MovingProfile& profile){

    switch(profile.type_case()){
      case rc::MovingProfile::kDirectApproachBallSpeed:
        return moving_profile::APPROACH_BALL_PROP_DISTANCE();

      case rc::MovingProfile::kDirectSafeKickBallSpeed:
        return moving_profile::KICK_BALL_SAFE_PROP_DISTANCE();

      case rc::MovingProfile::kDirectBalancedKickBallSpeed:
        return moving_profile::KICK_BALL_BALANCED_PROP_DISTANCE();

      case default:
        return moving_profile::MIN_DIST_TO_PROP_VELOCITY();
    }
}

} // namespace navigation
