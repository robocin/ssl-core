#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H

#include <optional>
#include <protocols/common/robot_pose.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class RobotPoseMessage : public robocin::IProtoConvertible<protocols::common::RobotPose> {
 public:
  std::optional<robocin::Point2Df> position;
  std::optional<float> orientation;

  explicit RobotPoseMessage(std::optional<robocin::Point2Df> position = std::nullopt,
                            std::optional<float> orientation = std::nullopt);

  explicit RobotPoseMessage(const protocols::common::RobotPose& robot_pose_proto);

  [[nodiscard]] protocols::common::RobotPose toProto() const override;

  void fromProto(const protocols::common::RobotPose& robot_pose_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_POSE_H
