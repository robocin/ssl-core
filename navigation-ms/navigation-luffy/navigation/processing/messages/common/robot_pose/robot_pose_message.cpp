#include "navigation/processing/messages/common/robot_pose/robot_pose_message.h"

namespace navigation {

explicit RobotPoseMessage::RobotPoseMessage(robocin::Point2Df position, float orientation) :
    position(position),
    orientation(orientation) {}

protocols::common::RobotPose RobotPoseMessage::toProto() const {
  return protocols::common::RobotPose{};
};

} // namespace navigation
