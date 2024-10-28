#ifndef DECISION_PROCESSING_MESSAGES_PERCEPTION_DETECTION_DETECTION_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_PERCEPTION_DETECTION_DETECTION_MESSAGE_H

#include "decision/processing/messages/iproto_convertible.h"
#include "decision/processing/messages/perception/ball/ball_message.h"
#include "decision/processing/messages/perception/field/field_message.h"
#include "decision/processing/messages/perception/robot/robot_message.h"

#include <cstdint>
#include <optional>
#include <protocols/perception/detection.pb.h>

namespace decision {

class DetectionMessage : public IProtoConvertible<protocols::perception::Detection> {
 public:
  std::optional<uint64_t> serial_id;
  std::optional<uint32_t> created_at; // todo(fnap): discuss what to do with timestamp
  std::optional<uint32_t> framerate;
  std::vector<BallMessage> balls;
  std::vector<RobotMessage> robots;
  std::optional<FieldMessage> field;

  explicit DetectionMessage(std::optional<uint64_t> serial_id = std::nullopt,
                            std::optional<uint32_t> created_at = std::nullopt,
                            std::optional<uint32_t> framerate = std::nullopt,
                            std::vector<BallMessage> balls = {},
                            std::vector<RobotMessage> robots = {},
                            std::optional<FieldMessage> field = std::nullopt);

  [[nodiscard]] protocols::perception::Detection toProto() const override {
    return protocols::perception::Detection{};
  }

  inline void fromProto(const protocols::perception::Detection& detection_proto) {};
};

} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_PERCEPTION_DETECTION_DETECTION_MESSAGE_H
