#include "navigation/processing/messages/navigation/navigation_message.h"

#include <algorithm>
#include <utility>

namespace navigation {
OutputMessage::OutputMessage(std::optional<RobotIdMessage> robot_id = RobotIdMessage{},
                             std::optional<PeripheralActuationMessage> peripheral_actuation,
                             std::optional<uint32_t> timestamp,
                             std::optional<double> forward_velocity,
                             std::optional<double> left_velocity,
                             std::optional<double> angular_velocity,
                             std::optional<uint32_t> custom_command,
                             std::optional<uint32_t> sequence_number,
                             std::optional<robocin::Point2Df> output_global_linear_velocity,
                             std::optional<RobotPoseMessage> robot_pose) :
    robot_id(std::move(robot_id)),
    peripheral_actuation(std::move(peripheral_actuation)),
    timestamp(std::move(timestamp)),
    forward_velocity(std::move(forward_velocity)),
    left_velocity(std::move(left_velocity)),
    angular_velocity(std::move(angular_velocity)),
    custom_command(std::move(custom_command)),
    sequence_number(std::move(sequence_number)),
    output_global_linear_velocity(std::move(output_global_linear_velocity)),
    robot_pose(std::move(robot_pose)) {}

protocols::navigation::Output OutputMessage::toProto() const {
  return protocols::navigation::Output{};
};

NavigationMessage::NavigationMessage(OutputMessage output) : output(std::move(output)) {}

protocols::navigation::Navigation NavigationMessage::toProto() const {
  return protocols::navigation::Navigation{};
}
} // namespace navigation
