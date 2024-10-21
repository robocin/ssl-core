#include "go_to_point_parser.h"

#include "navigation/parameters/parameters.h"
#include "navigation/processing/utils/move_task_state.h"
#include "robocin/geometry/angles.h"
#include "robocin/geometry/mathematics.h"

#include <numbers>
#include <protocols/perception/detection.pb.h>
#include <regex>
#include <robocin/geometry/point2d.h>

namespace navigation {

void GoToPointParser::setID(int id) { robot_id_ = id; }

::protocols::perception::Robot
GoToPointParser::matchAlly(const ::protocols::behavior::GoToPoint& motion,
                           ::protocols::referee::GameStatus& game_status,
                           ::protocols::perception::Detection& detection) {

  for (auto robot : detection.robots()) {
    if (robot_id_ == robot.robot_id().number()) // TODO: match team color
      return robot;
  }
}

RobotMove GoToPointParser::parse(const ::protocols::behavior::GoToPoint& motion,
                                 ::protocols::referee::GameStatus& game_status,
                                 ::protocols::perception::Detection& detection) {

  MoveTaskState move_task;
  const auto& ally = this->matchAlly(motion, game_status, detection);

  auto s0 = ally.position();
  auto s = motion.target();
  auto deltaS = (s - s0) / M_to_MM;

  const double kp = ANGLE_KP;
  const double maxAngularVel = ROBOT_MAX_ANGULAR_VELOCITY;

  auto [minVelocity, maxVelocity] = this->minAndMaxVelocityToProfile(motion.moving_profile());
  double propDistance = this->propDistanceToProfile(motion.moving_profile());

  if (deltaS.length() <= propDistance) {
    maxVelocity = std::max(
        ::robocin::math::map(deltaS.length(), 0.0, propDistance, minVelocity, maxVelocity),
        minVelocity);
  }

  double tolerance_to_target
      = motion.precision_to_target() == protocols::behavior::PrecisionToTarget::High ?
            SMALL_TOLERANCE_TO_DESIRED_POSITION_M :
            DEFAULT_TOLERANCE_TO_DESIRED_POSITION_M;

  const double d_theta
      = ::robocin::angles::smallestAngleDiff<double>(ally.angle(), motion.target_angle());

  if (deltaS.length() > tolerance_to_target) {

    // Uses an angle PID (only proportional for now), and first try to get in the right
    // angle, using only angular speed and then use linear speed to get into the point
    const double theta = deltaS.angle();
    double acc_prop = moving_profile::ROBOT_DEFAULT_LINEAR_ACCELERATION;
    auto v0 = ally.velocity() / M_to_MM;
    robocin::Point2D v;
    v = v.fromPolar(maxVelocity, theta);
    const double v0_decay = ::robocin::math::abs(v.angleTo(v0)) > 60 ?
                                ROBOT_VEL_BREAK_DECAY_FACTOR :
                                ROBOT_VEL_FAVORABLE_DECAY_FACTOR;

    // v = v0 + a*t
    v0 = v0 - (v0 * v0_decay) * CYCLE_STEP;

    auto acceleration_required = Point2D((v.x - v0.x) / CYCLE_STEP, (v.y - v0.y) / CYCLE_STEP);

    double alpha
        = ::robocin::math::map(::robocin::math::abs(d_theta), 0.0, std::numbers::pi, 0.0, 1.0);
    // -x^2 +1
    // double propFactor = (-(alpha * alpha) + 1);

    // (x -1)^2
    double prop_factor = (alpha - 1) * (alpha - 1);
    acc_prop *= prop_factor;

    if (acceleration_required.length() > acc_prop) {
      acceleration_required.resize(acc_prop);
    }

    // v = v0 + a*t
    auto new_velocity = v0 + acceleration_required * CYCLE_STEP;

    if (new_velocity.length() < ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY) {
      new_velocity.resize(ROBOT_MIN_POSSIBLE_LINEAR_VELOCITY);
    }

    if (move_task.currentState() == SkillMoveState::Unknown
        || move_task.currentState() == SkillMoveState::Started
        || move_task.currentState() == SkillMoveState::ChangedTarget) {
      move_task.resetRunningToTargetTimer();
    }

    // debug
    ::protocols::behavior::PathNode new_path_node;
    new_path_node.set_time(0);
    new_path_node.set_allocated_velocity(robocin::Point2Df{0, 0});
    new_path_node.set_allocated_position(motion.target());
    move_task.updateState(ally, game_status.command(), motion, new_path_node);

    return RobotMove{new_velocity,
                     ::robocin::math::bound(kp * d_theta, -maxAngularVel, maxAngularVel)};

  } else {

    return RobotMove{{0, 0}, ::robocin::math::bound(kp * d_theta, -maxAngularVel, maxAngularVel)};
  }
}

std::pair<double, double> GoToPointParser::minAndMaxVelocityToProfile(rc::MovingProfile profile) {
  switch (profile) {
    case rc::MovingProfile::DirectApproachBallSpeed:
      return {moving_profile::APPROACH_BALL_MIN_SPEED, moving_profile::APPROACH_BALL_MAX_SPEED};

    case rc::MovingProfile::DirectKickBallwithEnemyClose:
      return {moving_profile::KICK_BALL_WITH_ENEMY_MAX_SPEED,
              moving_profile::KICK_BALL_WITH_ENEMY_MIN_SPEED};

    case rc::MovingProfile::DirectSafeKickBallSpeed:
    case rc::MovingProfile::DirectBalancedKickBallSpeed:
      return {moving_profile::KICK_BALL_MIN_SPEED, moving_profile::KICK_BALL_MAX_SPEED};

    case rc::MovingProfile::TOTOZINHO:
      return {moving_profile::TOTOZINHO_MIN_SPEED, moving_profile::TOTOZINHO_MAX_SPEED};
  }
  return {moving_profile::ALLY_MIN_SPEED, moving_profile::ALLY_MAX_SPEED};
}

double GoToPointParser::propDistanceToProfile(rc::MovingProfile profile) {

  switch (profile) {
    case rc::MovingProfile::DirectApproachBallSpeed:
      return moving_profile::APPROACH_BALL_PROP_DISTANCE;

    case rc::MovingProfile::DirectSafeKickBallSpeed:
      return moving_profile::KICK_BALL_SAFE_PROP_DISTANCE;

    case rc::MovingProfile::DirectBalancedKickBallSpeed:
      return moving_profile::KICK_BALL_BALANCED_PROP_DISTANCE;
  }
  return moving_profile::MIN_DIST_TO_PROP_VELOCITY;
}

} // namespace navigation
