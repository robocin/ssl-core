#include "behavior/processing/messages/perception/robot/robot_message.h"

#include "robot_message.h"

#include <protocols/perception/detection.pb.h>
#include <robocin/geometry/point2d.h>

namespace behavior {

///////////////////////////////////////////// Wheel /////////////////////////////////////////////
Wheel::Wheel(std::optional<uint32_t> wheel_id, std::optional<float> motor_speed) :
    wheel_id(wheel_id),
    motor_speed(motor_speed) {};

//////////////////////////////////////////// Feedback ///////////////////////////////////////////

FeedbackMessage::FeedbackMessage(std::optional<bool> dribbler_ball_contact,
                                 std::optional<float> kick_charge_percentage,
                                 std::optional<float> battery_percentage,
                                 std::vector<Wheel> wheels) :
    dribbler_ball_contact(dribbler_ball_contact),
    kick_charge_percentage(kick_charge_percentage),
    battery_percentage(battery_percentage),
    wheels(std::move(wheels)) {};

FeedbackMessage::FeedbackMessage(const protocols::perception::Robot::Feedback& feedback_proto) {
  fromProto(feedback_proto);
};

protocols::perception::Robot::Feedback FeedbackMessage::toProto() const {
  protocols::perception::Robot::Feedback feedback_proto;

  // feedback_proto.set_dribbler_ball_contact(dribbler_ball_contact.value());
  // feedback_proto.set_kick_charge_percentage(kick_charge_percentage.value());
  // feedback_proto.set_battery_percentage(battery_percentage.value());

  // for (const auto& wheel : wheels) {
  //   feedback_proto.add_wheels()->CopyFrom(wheel.toProto());
  // }

  return feedback_proto;
};

void FeedbackMessage::fromProto(const protocols::perception::Robot::Feedback& feedback_proto) {
  dribbler_ball_contact = feedback_proto.dribbler_ball_contact();
  kick_charge_percentage = feedback_proto.kick_charge_percentage();
  battery_percentage = feedback_proto.battery_percentage();
};

///////////////////////////////////////////// Robot /////////////////////////////////////////////

RobotMessage::RobotMessage(std::optional<float> confidence,
                           std::optional<RobotIdMessage> robot_id,
                           std::optional<robocin::Point2Df> position,
                           std::optional<float> angle,
                           std::optional<robocin::Point2Df> velocity,
                           std::optional<float> angular_velocity,
                           std::optional<float> radius,
                           std::optional<float> height,
                           std::optional<float> dribbler_width,
                           std::optional<FeedbackMessage> feedback) :
    confidence(confidence),
    robot_id(std::move(robot_id)),
    position(position),
    angle(angle),
    velocity(velocity),
    angular_velocity(angular_velocity),
    radius(radius),
    height(height),
    dribbler_width(dribbler_width),
    feedback(std::move(feedback)) {};

void RobotMessage::fromProto(const protocols::perception::Robot& robot_proto) {
  confidence = robot_proto.confidence();
  position = robocin::Point2Df(robot_proto.position().x(), robot_proto.position().y());
  angle = robot_proto.angle();
  velocity = robocin::Point2Df(robot_proto.velocity().x(), robot_proto.velocity().y());
  angular_velocity = robot_proto.angular_velocity();
  radius = robot_proto.radius();
  height = robot_proto.height();
  dribbler_width = robot_proto.dribbler_width();

  if (robot_proto.has_robot_id()) {
    if (!robot_id.has_value()) {
      robot_id.emplace();
    }

    robot_id->fromProto(robot_proto.robot_id());
  }

  if (robot_proto.has_feedback()) {
    if (!feedback.has_value()) {
      feedback.emplace();
    }

    feedback->fromProto(robot_proto.feedback());
  }
};

protocols::perception::Robot RobotMessage::toProto() const {
  protocols::perception::Robot robot_proto;

  // robot_proto.set_confidence(confidence.value());
  // robot_proto.mutable_position()->set_x(position->x);
  // robot_proto.mutable_position()->set_y(position->y);
  // robot_proto.set_angle(angle.value());
  // robot_proto.mutable_velocity()->set_x(velocity->x);
  // robot_proto.mutable_velocity()->set_y(velocity->y);
  // robot_proto.set_angular_velocity(angular_velocity.value());
  // robot_proto.set_radius(radius.value());
  // robot_proto.set_height(height.value());
  // robot_proto.set_dribbler_width(dribbler_width.value());

  // if (robot_id.has_value()) {
  //   robot_proto.mutable_robot_id()->CopyFrom(robot_id->toProto());
  // }

  // if (feedback.has_value()) {
  //   robot_proto.mutable_feedback()->CopyFrom(feedback->toProto());
  // }

  return robot_proto;
};

RobotMessage::RobotMessage(const protocols::perception::Robot& robot_proto) {
  RobotMessage::fromProto(robot_proto);
};

} // namespace behavior
