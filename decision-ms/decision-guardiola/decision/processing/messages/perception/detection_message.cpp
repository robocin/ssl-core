#include "decision/processing/messages/perception/detection_message.h"

namespace decision {

Wheel::Wheel(std::optional<uint32_t> wheel_id, std::optional<float> motor_speed) :
    wheel_id(wheel_id),
    motor_speed(motor_speed) {};

FeedbackMessage::FeedbackMessage(std::optional<bool> dribbler_ball_contact,
                                 std::optional<float> kick_charge_percentage,
                                 std::optional<float> battery_percentage,
                                 std::vector<Wheel> wheels) :
    dribbler_ball_contact(dribbler_ball_contact),
    kick_charge_percentage(kick_charge_percentage),
    battery_percentage(battery_percentage),
    wheels(std::move(wheels)) {};

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
} // namespace decision
