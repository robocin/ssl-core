#ifndef GOTOPOINTPARSER_H
#define GOTOPOINTPARSER_H

#include <optional>
#include "MotionParser.h"
#include "navigation/processing/motion_parser/MotionParser.h"

namespace rc {

using ::protocols::navigation::GoToPoint;
using ::protocols::navigation::MovingProfile;

} // namespace rc

class GoToPointParser :: public navigation::IMotionParser<GoToPoint& goToPoint> {
  inline static constexpr double DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M = 0.02;
  inline static constexpr double SMALL_TOLERANCE_TO_DESIRED_POSITION_M = 0.01;

  Navigation::MoveTaskState moveTask;

 public:
  template <class M>
  inline GoToPointParser() {}

  inline static std::pair<double, double> minAndMaxVelocityToProfile(rc::MovingProfile profile) {

    switch(profile){
        case rc::MovingProfile::DirectApproachBallSpeed:
            return {Env::MovingProfile::APPROACH_BALL_MIN_SPEED, 
                    Env::MovingProfile::APPROACH_BALL_MAX_SPEED};
        case rc::MovingProfile::DirectKickBallwithEnemyClose:
            return {Env::MovingProfile::KICK_BALL_WITH_ENEMY_MAX_SPEED,
                    Env::MovingProfile::KICK_BALL_WITH_ENEMY_MIN_SPEED};
        case rc::MovingProfile::DirectSafeKickBallSpeed:
        case rc::MovingProfile::DirectBalancedKickBallSpeed:
            return {Env::MovingProfile::KICK_BALL_MIN_SPEED, 
                    Env::MovingProfile::KICK_BALL_MAX_SPEED};
        case rc::MovingProfile::TOTOZINHO:
            return {Env::MovingProfile::TOTOZINHO_MIN_SPEED, 
                    Env::MovingProfile::TOTOZINHO_MAX_SPEED};
        default:
            return {Env::MovingProfile::ALLY_MIN_SPEED, 
                    Env::MovingProfile::ALLY_MAX_SPEED};
    }
  }

  inline static double propDistanceToProfile(rc::MovingProfile profile) {

    switch(profile){
        case rc::MovingProfile::DirectApproachBallSpeed:
            return Env::MovingProfile::APPROACH_BALL_PROP_DISTANCE;
        case rc::MovingProfile::DirectSafeKickBallSpeed:
            return Env::MovingProfile::KICK_BALL_SAFE_PROP_DISTANCE;
        case rc::MovingProfile::DirectBalancedKickBallSpeed:
            return Env::MovingProfile::KICK_BALL_BALANCED_PROP_DISTANCE;
        default:
            return Env::MovingProfile::MIN_DIST_TO_PROP_VELOCITY;
    }
  }

  inline Navigation::RobotMove parse(const GoToPoint& motion) {

    if(typeof(motion) != GoToPoint)
        return std::nullopt_t;

    const auto& ally = world.ally();

    auto&& s0 = ally.position();
    auto&& s = goToPoint.target();
    auto deltaS = (s - s0) / Env::M_TO_MM;

    const double kp = Env::Navigation::ANGLE_KP;
    const double maxAngularVel = Env::Navigation::ROBOT_MAX_ANGULAR_VELOCITY;

    auto [minVelocity, maxVelocity] = minAndMaxVelocityToProfile(goToPoint.movingProfile());
    double propDistance = propDistanceToProfile(goToPoint.movingProfile());

    if (deltaS.length() <= propDistance) {
      maxVelocity =
          std::max(Math::map(deltaS.length(), 0.0, propDistance, minVelocity, maxVelocity),
                   minVelocity);
    }

    double toleranceToTarget =
        goToPoint.precisionToTarget() == MotionType::PrecisionToTarget::High ?
            SMALL_TOLERANCE_TO_DESIRED_POSITION_M :
            DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M;

    // preditor updated state
    MoveState estimateState = world.ally().estimateRobotStateByBackPropagationInMeters();

    BangBangTrajectory1DOrient orientationTrajectory =
        BangBangTrajectoryFactory::orientation(estimateState.angle(),
                                               goToPoint.targetAngle(),
                                               estimateState.angleVelocity(),
                                               Env::Navigation::ROBOT_MAX_ANGULAR_VELOCITY,
                                               Env::Navigation::ROBOT_MAX_ANGULAR_ACCELERATION);

    const double dTheta =
        Geometry::smallestAngleDiff<double>(ally.angle(), goToPoint.targetAngle());

    if (deltaS.length() > toleranceToTarget) {
      // Uses an angle PID (only proportional for now), and first try to get in the right
      // angle, using only angular speed and then use linear speed to get into the point
      const double theta = deltaS.angle();
      double accProp = Env::MovingProfile::ROBOT_DEFAULT_LINEAR_ACCELERATION.value();
      auto v0 = ally.velocity() / Env::M_TO_MM;
      auto v = Geometry2D::fromPolar<Point>(maxVelocity, theta);
      const double v0Decay = Math::abs(Geometry2D::angleBetween(v, v0)) > 60_degrees ?
                                 Env::Navigation::ROBOT_VEL_BREAK_DECAY_FACTOR :
                                 Env::Navigation::ROBOT_VEL_FAVORABLE_DECAY_FACTOR;

      // v = v0 + a*t
      v0 = v0 - (v0 * v0Decay) * Env::Navigation::CYCLE_STEP;

      auto accelerationRequired = Point((v.x() - v0.x()) / Env::Navigation::CYCLE_STEP,
                                        (v.y() - v0.y()) / Env::Navigation::CYCLE_STEP);

      double alpha = Math::map(Math::abs(dTheta), 0.0, PI, 0.0, 1.0);
      // -x^2 +1
      // double propFactor = (-(alpha * alpha) + 1);

      // (x -1)^2
      double propFactor = (alpha - 1) * (alpha - 1);
      accProp *= propFactor;

      if (accelerationRequired.length() > accProp) {
        accelerationRequired.resize(accProp);
      }

      // v = v0 + a*t
      auto newVelocity = v0 + accelerationRequired * Env::Navigation::CYCLE_STEP;

      if (newVelocity.length() < Env::Navigation::ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY) {
        newVelocity.resize(Env::Navigation::ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY);
      }

      if (is_in(moveTask.currentState(),
                Navigation::SkillMoveState::Unknown,
                Navigation::SkillMoveState::Started,
                Navigation::SkillMoveState::ChangedTarget)) {
        moveTask.resetRunningToTargetTimer();
      }

      // debug
      moveTask.updateState(ally,
                           world.referee().state(),
                           goToPoint,
                           MotionType::PathNode(goToPoint.target(), {0, 0}, 0));

      return Navigation::RobotMove{newVelocity,
                                   Math::bound(kp * dTheta, -maxAngularVel, maxAngularVel)};
    } else {
      return {{0, 0}, Math::bound(kp * dTheta, -maxAngularVel, maxAngularVel)};
    }
  }
};

#endif // GOTOPOINTPARSER_H
