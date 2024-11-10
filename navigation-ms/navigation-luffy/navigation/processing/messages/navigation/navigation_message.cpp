#include "navigation/processing/messages/navigation/navigation_message.h"

namespace navigation {

void NavigationMessage::fromProto(const protocols::navigation::Navigation& navigation_proto) {
  for (const auto& output_proto : navigation_proto.output()) {
    output.emplace_back(output_proto);
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
  protocols::navigation::Output output_proto;
  if (robot_id.has_value()) {
    output_proto.mutable_robot_id()->CopyFrom(robot_id->toProto());
  };
  if (peripheral_actuation.has_value()) {
    output_proto.mutable_peripheral_actuation()->CopyFrom(peripheral_actuation->toProto());
  };
  if (robot_pose.has_value()) {
    output_proto.mutable_robot_pose()->CopyFrom(robot_pose->toProto());
  };
  if (timestamp.has_value()) {
    output_proto.mutable_timestamp()->set_seconds(timestamp.value());
  };
  if (forward_velocity.has_value()) {
    output_proto.set_forward_velocity(forward_velocity.value());
  };
  if (left_velocity.has_value()) {
    output_proto.set_left_velocity(left_velocity.value());
  };
  if (angular_velocity.has_value()) {
    output_proto.set_angular_velocity(angular_velocity.value());
  };
  if (custom_command.has_value()) {
    output_proto.set_custom_command(custom_command.value());
  };
  if (sequence_number.has_value()) {
    output_proto.set_sequence_number(sequence_number.value());
  };
  if (output_global_linear_velocity.has_value()) {
    output_proto.mutable_output_global_linear_velocity()->set_x(output_global_linear_velocity->x);
    output_proto.mutable_output_global_linear_velocity()->set_y(output_global_linear_velocity->y);
  };

  return protocols::navigation::Output{};
};

NavigationMessage::NavigationMessage(std::vector<NavigationOutputMessage> output) :
    output(std::move(output)) {}

protocols::navigation::Navigation NavigationMessage::toProto() const {
  protocols::navigation::Navigation nav_msg;
  for (const auto& output_msg : output) {
    nav_msg.add_output()->CopyFrom(output_msg.toProto());
  }
  return nav_msg;
}
} // namespace navigation
