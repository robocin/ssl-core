#include "decision/processing/messages/motion/motion_message.h"

namespace decision {
MotionMessage::MotionMessage(
    std::optional<GoToPointMessage> go_to_point,
    std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory,
    std::optional<RotateInPointMessage> rotate_in_point,
    std::optional<RotateOnSelfMessage> rotate_on_self) :
    go_to_point(std::move(go_to_point)),
    go_to_point_with_trajectory(std::move(go_to_point_with_trajectory)),
    rotate_in_point(std::move(rotate_in_point)),
    rotate_on_self(std::move(rotate_on_self)) {}

GoToPointMessage::GoToPointMessage(std::optional<robocin::Point2D<float>> target,
                                   std::optional<double> target_angle,
                                   std::optional<MovingProfile> moving_profile,
                                   std::optional<PrecisionToTarget> precision_to_target,
                                   std::optional<bool> sync_rotate_with_linear_movement) :
    target(target),
    target_angle(target_angle),
    moving_profile(moving_profile),
    precision_to_target(precision_to_target),
    sync_rotate_with_linear_movement(sync_rotate_with_linear_movement) {}

RotateOnSelfMessage::RotateOnSelfMessage() = default;
RotateInPointMessage::RotateInPointMessage() = default;
GoToPointWithTrajectoryMessage::GoToPointWithTrajectoryMessage() = default;

} // namespace decision
