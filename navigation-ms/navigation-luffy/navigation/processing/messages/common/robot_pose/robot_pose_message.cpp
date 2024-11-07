#include "navigation/processing/messages/common/robot_pose/robot_pose_message.h"

namespace navigation {

explicit RobotPoseMessage::RobotPoseMessage(robocin::Point2Df position, float orientation) :
    position(position),
    orientation(orientation) {}

protocols::common::RobotPose RobotPoseMessage::toProto() const {
  return protocols::common::RobotPose{};
};

void RobotPoseMessage::fromProto(const protocols::common::RobotPose& robot_pose_proto){
  position = robocin::Point2Df{robot_pose_proto.position().x(), robot_pose_proto.position().y()};
  orientation = robot_pose_proto.orientation();
}

RobotPoseMessage::RobotPoseMessage(const protocols::common::RobotPose& robot_pose_proto){
  RobotPoseMessage::fromProto(robot_pose_proto);
}
} // namespace navigation
