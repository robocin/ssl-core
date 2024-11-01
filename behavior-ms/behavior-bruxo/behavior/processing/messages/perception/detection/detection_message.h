#ifndef BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_DETECTION_DETECTION_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_DETECTION_DETECTION_MESSAGE_H

#include "behavior/processing/messages/perception/ball/ball_message.h"
#include "behavior/processing/messages/perception/field/field_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <cstdint>
#include <optional>
#include <protocols/perception/detection.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace decision {

class DetectionMessage : public robocin::IProtoConvertible<protocols::perception::Detection> {
 public:
  std::optional<uint64_t> serial_id;
  std::optional<uint32_t> created_at;
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

  explicit DetectionMessage(const protocols::perception::Detection& detection_proto);

  [[nodiscard]] protocols::perception::Detection toProto() const override;
  void fromProto(const protocols::perception::Detection& detection_proto) override;
};

} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_DETECTION_DETECTION_MESSAGE_H
