#include "decision/processing/messages/perception/detection/detection_message.h"

namespace decision {
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
}
