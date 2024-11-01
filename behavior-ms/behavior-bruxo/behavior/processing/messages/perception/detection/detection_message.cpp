#include "behavior/processing/messages/perception/detection/detection_message.h"

#include "behavior/processing/messages/perception/field/field_message.h"

namespace behavior {

DetectionMessage::DetectionMessage(std::optional<uint64_t> serial_id,
                                   std::optional<uint32_t> created_at,
                                   std::optional<uint32_t> framerate,
                                   std::vector<BallMessage> balls,
                                   std::vector<RobotMessage> robots,
                                   std::optional<FieldMessage> field) :
    serial_id(serial_id),
    created_at(created_at),
    framerate(framerate),
    balls(std::move(balls)),
    robots(std::move(robots)),
    field(std::move(field)) {};

protocols::perception::Detection DetectionMessage::toProto() const { return rc::Detection{}; };

void DetectionMessage::fromProto(const protocols::perception::Detection& detection_proto) {

  serial_id = detection_proto.serial_id();
  created_at = detection_proto.created_at().seconds();
  framerate = detection_proto.framerate();

  if (detection_proto.has_field()) {
    // Checking for std::nullopt FieldMessage
    if (!field.has_value()) {
      field.emplace();
    }
    field->fromProto(detection_proto.field());
  }

  for (const auto& ball_proto : detection_proto.balls()) {
    balls.emplace_back(ball_proto);
  }

  for (const auto& robot_proto : detection_proto.robots()) {
    robots.emplace_back(robot_proto);
  }
};

DetectionMessage::DetectionMessage(const protocols::perception::Detection& detection_proto) {
  fromProto(detection_proto);
}

} // namespace behavior
