#include "behavior/processing/messages/motion/motion_message.h"

namespace behavior {

GoToPointMessage::GoToPointMessage(std::optional<robocin::Point2D<float>> target,
                                   std::optional<double> target_angle,
                                   std::optional<MovingProfile> moving_profile,
                                   std::optional<PrecisionToTarget> precision_to_target,
                                   std::optional<bool> sync_rotate_with_linear_movement) :
    target{std::move(target)},
    target_angle{std::move(target_angle)},
    moving_profile{std::move(moving_profile)},
    precision_to_target{std::move(precision_to_target)},
    sync_rotate_with_linear_movement{std::move(sync_rotate_with_linear_movement)} {}

protocols::behavior::GoToPoint GoToPointMessage::toProto() const {
  protocols::behavior::GoToPoint go_to_point;

  if (target.has_value()) {
    go_to_point.mutable_target()->set_x(target->x);
    go_to_point.mutable_target()->set_y(target->y);
  }
  if (target_angle.has_value()) {
    go_to_point.set_target_angle(target_angle.value());
  }
  if (moving_profile.has_value()) {
    go_to_point.set_moving_profile(static_cast<protocols::behavior::MovingProfile>(
        moving_profile.value_or(MovingProfile::SafeInStopSpeed)));
  }
  if (precision_to_target.has_value()) {
    go_to_point.set_precision_to_target(static_cast<protocols::behavior::PrecisionToTarget>(
        precision_to_target.value_or(PrecisionToTarget::NORMAL)));
  }
  if (sync_rotate_with_linear_movement.has_value()) {
    go_to_point.set_sync_rotate_with_linear_movement(sync_rotate_with_linear_movement.value());
  }

  return go_to_point;
}

void GoToPointMessage::fromProto(const protocols::behavior::GoToPoint& go_to_point) {
  target = robocin::Point2D<float>{go_to_point.target().x(), go_to_point.target().y()};
  target_angle = go_to_point.target_angle();
  moving_profile = static_cast<MovingProfile>(go_to_point.moving_profile());
  precision_to_target = static_cast<PrecisionToTarget>(go_to_point.precision_to_target());
  sync_rotate_with_linear_movement = go_to_point.sync_rotate_with_linear_movement();
}

GoToPointWithTrajectoryMessage::GoToPointWithTrajectoryMessage() {}

RotateInPointMessage::RotateInPointMessage() {}

RotateOnSelfMessage::RotateOnSelfMessage() {}

MotionMessage::MotionMessage(
    std::optional<GoToPointMessage> go_to_point,
    std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory,
    std::optional<RotateInPointMessage> rotate_in_point,
    std::optional<RotateOnSelfMessage> rotate_on_self) :
    go_to_point{std::move(go_to_point)},
    go_to_point_with_trajectory{std::move(go_to_point_with_trajectory)},
    rotate_in_point{std::move(rotate_in_point)},
    rotate_on_self{std::move(rotate_on_self)} {}

protocols::behavior::unification::Motion MotionMessage::toProto() const {
  protocols::behavior::unification::Motion motion;
  if (go_to_point.has_value()) {
    motion.set_allocated_go_to_point(
        new protocols::behavior::GoToPoint(go_to_point.value().toProto()));
  }
  if (go_to_point_with_trajectory.has_value()) {
    motion.set_allocated_go_to_point_with_trajectory(
        new protocols::behavior::GoToPointWithTrajectory(
            go_to_point_with_trajectory.value().toProto()));
  }
  if (rotate_in_point.has_value()) {
    motion.set_allocated_rotate_in_point(
        new protocols::behavior::RotateInPoint(rotate_in_point.value().toProto()));
  }
  if (rotate_on_self.has_value()) {
    motion.set_allocated_rotate_on_self(
        new protocols::behavior::RotateOnSelf(rotate_on_self.value().toProto()));
  }

  return motion;
}

void MotionMessage::fromProto(const protocols::behavior::unification::Motion& motion) {}

} // namespace behavior
