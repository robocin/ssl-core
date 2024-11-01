#ifndef BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_ROBOT_ROBOT_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_ROBOT_ROBOT_MESSAGE_H

#include "behavior/processing/messages/common/robot_id/robot_id.h"

#include <cstdint>
#include <protocols/perception/detection.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>
#include <utility>

namespace behavior {

class Wheel : public robocin::IProtoConvertible<protocols::perception::Robot::Feedback::Wheel> {
 public:
  std::optional<uint32_t> wheel_id;
  std::optional<float> motor_speed;

  explicit Wheel(std::optional<uint32_t> wheel_id = std::nullopt,
                 std::optional<float> motor_speed = std::nullopt);

  [[nodiscard]] protocols::perception::Robot::Feedback::Wheel toProto() const override {
    return protocols::perception::Robot::Feedback::Wheel{};
  }

  void fromProto(const protocols::perception::Robot::Feedback::Wheel& wheel_proto) override {};
};

class FeedbackMessage : public robocin::IProtoConvertible<protocols::perception::Robot::Feedback> {
 public:
  std::optional<bool> dribbler_ball_contact;
  std::optional<float> kick_charge_percentage;
  std::optional<float> battery_percentage;

  std::vector<Wheel> wheels;

  explicit FeedbackMessage(std::optional<bool> dribbler_ball_contact = std::nullopt,
                           std::optional<float> kick_charge_percentage = std::nullopt,
                           std::optional<float> battery_percentage = std::nullopt,
                           std::vector<Wheel> wheels = {});

  explicit FeedbackMessage(const protocols::perception::Robot::Feedback& feedback_proto);

  [[nodiscard]] protocols::perception::Robot::Feedback toProto() const override {
    return protocols::perception::Robot::Feedback{};
  }

  void fromProto(const protocols::perception::Robot::Feedback& feedback_proto) override;
};

class RobotMessage : public robocin::IProtoConvertible<protocols::perception::Robot> {
 public:
  std::optional<float> confidence;
  std::optional<RobotIdMessage> robot_id;
  std::optional<robocin::Point2Df> position;
  std::optional<float> angle;
  std::optional<robocin::Point2Df> velocity;
  std::optional<float> angular_velocity;
  std::optional<float> radius;
  std::optional<float> height;
  std::optional<float> dribbler_width;
  std::optional<FeedbackMessage> feedback;

  explicit RobotMessage(std::optional<float> confidence = std::nullopt,
                        std::optional<RobotIdMessage> robot_id = std::nullopt,
                        std::optional<robocin::Point2Df> position = std::nullopt,
                        std::optional<float> angle = std::nullopt,
                        std::optional<robocin::Point2Df> velocity = std::nullopt,
                        std::optional<float> angular_velocity = std::nullopt,
                        std::optional<float> radius = std::nullopt,
                        std::optional<float> height = std::nullopt,
                        std::optional<float> dribbler_width = std::nullopt,
                        std::optional<FeedbackMessage> feedback = std::nullopt);

  explicit RobotMessage(const protocols::perception::Robot& robot_proto);

  [[nodiscard]] protocols::perception::Robot toProto() const override {
    return protocols::perception::Robot{};
  }

  void fromProto(const protocols::perception::Robot& robot_proto) override;
};
} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_ROBOT_ROBOT_MESSAGE_H
