#include "navigation/processing/messages/motion/motion_message.h"

#include <protocols/behavior/behavior_unification.pb.h>

namespace navigation {
MotionMessage::MotionMessage(
    std::optional<GoToPointMessage> go_to_point,
    std::optional<GoToPointWithTrajectoryMessage> go_to_point_with_trajectory,
    std::optional<RotateInPointMessage> rotate_in_point,
    std::optional<RotateOnSelfMessage> rotate_on_self) :
    go_to_point(std::move(go_to_point)),
    go_to_point_with_trajectory(std::move(go_to_point_with_trajectory)),
    rotate_in_point(std::move(rotate_in_point)),
    rotate_on_self(std::move(rotate_on_self)) {}

MotionMessage::MotionMessage(protocols::behavior::unification::Motion& motion_proto) {
  fromProto(motion_proto);
}

void MotionMessage::fromProto(const protocols::behavior::unification::Motion& motion_proto) {
  if (motion_proto.has_go_to_point()) {
    go_to_point = GoToPointMessage(motion_proto.go_to_point());
  }
  if (motion_proto.has_go_to_point_with_trajectory()) {
    go_to_point_with_trajectory
        = GoToPointWithTrajectoryMessage(motion_proto.go_to_point_with_trajectory());
  }
  if (motion_proto.has_rotate_in_point()) {
    rotate_in_point = RotateInPointMessage(motion_proto.rotate_in_point());
  }
  if (motion_proto.has_rotate_on_self()) {
    rotate_on_self = RotateOnSelfMessage(motion_proto.rotate_on_self());
  }
}

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

} // namespace navigation
