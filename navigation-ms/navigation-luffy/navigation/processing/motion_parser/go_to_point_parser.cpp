#include "go_to_point_parser.h"
#include "navigation/parameters/parameters.h"
#include "common/cpp/robocin/geometry/geometry.h"
#include <any>
#include <protocols/navigation/motion.pb.h>
#include "navigation/processing/utils/move_task_state.h"
#include <regex>
#include <cmath>

namespace navigation {

GoToPointParser::GoToPointParser(std::any world) : 
  world_(std::move(world)) {}

RobotMove GoToPointParser::parse(const ::protocols::navigation::GoToPoint& motion) {
  
  const auto& ally = world.ally();

  auto&& s0 = ally.position();
  auto&& s = motion.target();
  auto deltaS = (s - s0) / M_TO_MM();

  const double kp = ANGLE_KP();
  const double maxAngularVel = ROBOT_MAX_ANGULAR_VELOCITY();

  auto [minVelocity, maxVelocity] = minAndMaxVelocityToProfile(motion.moving_profile.type());
  double propDistance = propDistanceToProfile(motion.moving_profile.type());

  if (deltaS.length() <= propDistance) {
    maxVelocity =
        std::max(map(deltaS.length(), 0.0, propDistance, minVelocity, maxVelocity),
                  minVelocity);
  }

  double toleranceToTarget =
      motion.precisionToTarget() == ::protocols::navigation::PrecisionToTarget::High ?
          SMALL_TOLERANCE_TO_DESIRED_POSITION_M() :
          DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M();

  const double dTheta =
      ::robocin::geometry::smallestAngleDiff<double>(ally.angle(), motion.targetAngle());

  if (deltaS.length() > toleranceToTarget) {
    
    // Uses an angle PID (only proportional for now), and first try to get in the right
    // angle, using only angular speed and then use linear speed to get into the point
    const double theta = deltaS.angle();
    double accProp = moving_profile::ROBOT_DEFAULT_LINEAR_ACCELERATION();
    auto v0 = ally.velocity() / M_TO_MM();
    auto v = Point2D::fromPolar(maxVelocity, theta);
    const double v0Decay = abs(Point2D::angleBetween(v, v0)) > 60_degrees ?
                                ROBOT_VEL_BREAK_DECAY_FACTOR() :
                                ROBOT_VEL_FAVORABLE_DECAY_FACTOR();

    // v = v0 + a*t
    v0 = v0 - (v0 * v0Decay) * CYCLE_STEP();

    auto accelerationRequired = Point2D((v.x() - v0.x()) / CYCLE_STEP(),
                                      (v.y() - v0.y()) / CYCLE_STEP());

    double alpha = map(abs(dTheta), 0.0, PI, 0.0, 1.0);
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
                        world.game_status().command(),
                        motion,
                        ::protocols::navigation::PathNode(motion.target(), {0, 0}, 0));


    return RobotMove{newVelocity, bound(kp * dTheta, -maxAngularVel, maxAngularVel)};
  
  } else {

    return {{0, 0}, bound(kp * dTheta, -maxAngularVel, maxAngularVel)};
  }

}

} // namespace navigation
