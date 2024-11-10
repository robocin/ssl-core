#ifndef NAVIGATION_PROCESSING_MESSAGES_NAVIGATION_NAVIGATION_MESSAGE_H
#define NAVIGATION_PROCESSING_MESSAGES_NAVIGATION_NAVIGATION_MESSAGE_H

#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"
#include "navigation/processing/messages/common/robot_id/robot_id_message.h"
#include "navigation/processing/messages/common/robot_pose/robot_pose_message.h"

#include <cstdint>
#include <optional>
#include <protocols/navigation/navigation.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>

namespace navigation {

class NavigationOutputMessage : public robocin::IProtoConvertible<protocols::navigation::Output> {
 public:
  NavigationOutputMessage(std::optional<RobotIdMessage> robot_id = std::nullopt,
                          std::optional<PeripheralActuationMessage> peripheral_actuation
                          = std::nullopt,
                          std::optional<uint32_t> timestamp = std::nullopt,
                          std::optional<double> forward_velocity = std::nullopt,
                          std::optional<double> left_velocity = std::nullopt,
                          std::optional<double> angular_velocity = std::nullopt,
                          std::optional<uint32_t> custom_command = std::nullopt,
                          std::optional<uint32_t> sequence_number = std::nullopt,
                          std::optional<robocin::Point2Df> output_global_linear_velocity
                          = std::nullopt,
                          std::optional<RobotPoseMessage> robot_pose = std::nullopt);

  explicit NavigationOutputMessage(const protocols::navigation::Output& output_proto);

  std::optional<RobotIdMessage> robot_id;
  std::optional<PeripheralActuationMessage> peripheral_actuation;
  std::optional<uint32_t> timestamp;
  std::optional<double> forward_velocity;
  std::optional<double> left_velocity;
  std::optional<double> angular_velocity;
  std::optional<uint32_t> custom_command;
  std::optional<uint32_t> sequence_number;
  std::optional<robocin::Point2Df> output_global_linear_velocity;
  std::optional<RobotPoseMessage> robot_pose;

  [[nodiscard]] protocols::navigation::Output toProto() const override;

  void fromProto(const protocols::navigation::Output& output_proto) override;
};

class NavigationMessage : public robocin::IProtoConvertible<protocols::navigation::Navigation> {
 public:
  explicit NavigationMessage(std::vector<NavigationOutputMessage> output = {});

  explicit NavigationMessage(const protocols::navigation::Navigation& navigation_proto);

  std::vector<NavigationOutputMessage> output;

  [[nodiscard]] protocols::navigation::Navigation toProto() const override;

  void fromProto(const protocols::navigation::Navigation& navigation_proto) override;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_NAVIGATION_NAVIGATION_MESSAGE_H
