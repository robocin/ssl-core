#include "navigation/processing/messages/navigation/navigation_message.h"

namespace navigation {

void NavigationMessage::fromProto(const protocols::navigation::Navigation& navigation_proto) {
  for (const auto& output_proto : navigation_proto.output()) {
    output->emplace_back(output_proto);
  }
}
NavigationMessage::NavigationMessage(const protocols::navigation::Navigation& navigation_proto) {
  NavigationMessage::fromProto(navigation_proto);
}

void NavigationOutputMessage::fromProto(const protocols::navigation::Output& output_proto) {
  robot_id = RobotIdMessage(output_proto.robot_id());
  output_global_linear_velocity
      = robocin::Point2Df{output_proto.output_global_linear_velocity().x(),
                          output_proto.output_global_linear_velocity().y()};
  robot_pose = RobotPoseMessage(output_proto.robot_pose());
  peripheral_actuation = PeripheralActuationMessage(output_proto.peripheral_actuation());
  // timestamp = output_proto.timestamp();
  forward_velocity = output_proto.forward_velocity();
  left_velocity = output_proto.left_velocity();
  angular_velocity = output_proto.angular_velocity();
  custom_command = output_proto.custom_command();
  sequence_number = output_proto.sequence_number();
}

NavigationOutputMessage::NavigationOutputMessage(
    const protocols::navigation::Output& output_proto) {
  NavigationOutputMessage::fromProto(output_proto);
}
NavigationOutputMessage::NavigationOutputMessage(
    std::optional<RobotIdMessage> robot_id,
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
    timestamp(timestamp),
    forward_velocity(forward_velocity),
    left_velocity(left_velocity),
    angular_velocity(angular_velocity),
    custom_command(custom_command),
    sequence_number(sequence_number),
    output_global_linear_velocity(output_global_linear_velocity),
    robot_pose(std::move(robot_pose)) {}

protocols::navigation::Output NavigationOutputMessage::toProto() const {
  return protocols::navigation::Output{};
};

NavigationMessage::NavigationMessage(std::optional<std::vector<NavigationOutputMessage>> output) :
    output(std::move(output)) {}

protocols::navigation::Navigation NavigationMessage::toProto() const {
  return protocols::navigation::Navigation{};
}
} // namespace navigation
