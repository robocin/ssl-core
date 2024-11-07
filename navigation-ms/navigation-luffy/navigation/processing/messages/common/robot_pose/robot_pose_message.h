#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H

#include <optional>
#include <protocols/common/robot_pose.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class RobotPoseMessage : public robocin::IProtoConvertible<protocols::common::RobotPose> {
 public:
  robocin::Point2Df position;
  float orientation;

  RobotPoseMessage(robocin::Point2Df position = robocin::Point2Df{0, 0}, float orientation = 0.0F);

  explicit RobotPoseMessage(const protocols::common::RobotPose& robot_pose_proto);

  [[nodiscard]] protocols::common::RobotPose toProto() const override;

  void fromProto(const protocols::common::RobotPose& robot_pose_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H
