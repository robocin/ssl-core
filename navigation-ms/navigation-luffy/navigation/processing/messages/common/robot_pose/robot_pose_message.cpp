#include "navigation/processing/messages/common/robot_pose/robot_pose_message.h"

namespace navigation {

RobotPoseMessage::RobotPoseMessage(std::optional<robocin::Point2Df> position,
                                   std::optional<float> orientation) :
    position(position),
    orientation(orientation) {}

protocols::common::RobotPose RobotPoseMessage::toProto() const {
  protocols::common::RobotPose pose_proto;
  if (position.has_value()) {
    pose_proto.mutable_position()->set_x(position->x);
    pose_proto.mutable_position()->set_y(position->y);
  }
  if (orientation.has_value()) {
    pose_proto.set_orientation(orientation.value());
  }
  return pose_proto;
};

void RobotPoseMessage::fromProto(const protocols::common::RobotPose& robot_pose_proto) {
  position = robocin::Point2Df{robot_pose_proto.position().x(), robot_pose_proto.position().y()};
  orientation = robot_pose_proto.orientation();
}

RobotPoseMessage::RobotPoseMessage(const protocols::common::RobotPose& robot_pose_proto) {
  RobotPoseMessage::fromProto(robot_pose_proto);
}
} // namespace navigation
