#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H

#include <optional>
#include <protocols/common/robot_pose.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class RobotPoseMessage : public robocin::IProtoConvertible<protocols::common::RobotPose> {
 public:
  explicit RobotPoseMessage(robocin::Point2Df position, float orientation);
  explicit RobotPoseMessage(const protocols::common::RobotPose& robot_pose_proto);
  robocin::Point2Df position;
  float orientation;

  [[nodiscard]] protocols::common::RobotPose toProto() const override;

  void fromProto(const protocols::common::RobotPose& robot_pose_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H
