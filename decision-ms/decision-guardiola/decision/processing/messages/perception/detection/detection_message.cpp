#include "decision/processing/messages/perception/detection/detection_message.h"

#include "decision/processing/messages/perception/field/field_message.h"

namespace decision {
namespace {
namespace rc {
using protocols::perception::Detection;
} // namespace rc
} // namespace

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

rc::Detection DetectionMessage::toProto() const { return rc::Detection{}; };

void DetectionMessage::fromProto(const rc::Detection& detection_proto) {

  this->serial_id = detection_proto.serial_id();
  this->created_at
      = detection_proto.created_at().seconds(); // todo(fnap): discuss the usage of this field
  this->framerate = detection_proto.framerate();

  if (detection_proto.has_field()) {
    this->field = FieldMessage(detection_proto.field());
  }

  for (const auto& ball_proto : detection_proto.balls()) {
    balls.emplace_back(ball_proto);
  }

  for (const auto& robot_proto : detection_proto.robots()) {
    robots.emplace_back(robot_proto);
  }
};

DetectionMessage::DetectionMessage(const rc::Detection& detection_proto) {
  fromProto(detection_proto);
}

} // namespace decision
