#ifndef DECISION_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H

#include "decision/processing/messages/iproto_convertible.h"

#include <cstdint>
#include <optional>
#include <protocols/perception/detection.pb.h>

namespace decision {

class FieldMessage : public IProtoConvertible<protocols::perception::Field> {
 public:
  std::optional<uint64_t> serial_id;
  std::optional<float> length;
  std::optional<float> width;
  std::optional<float> goal_depth;
  std::optional<float> goal_width;
  std::optional<float> penalty_area_depth;
  std::optional<float> penalty_area_width;
  std::optional<float> boundary_width;
  std::optional<float> goal_center_to_penalty_mark;

  explicit FieldMessage(std::optional<uint64_t> serial_id = std::nullopt,
                        std::optional<float> length = std::nullopt,
                        std::optional<float> width = std::nullopt,
                        std::optional<float> goal_depth = std::nullopt,
                        std::optional<float> goal_width = std::nullopt,
                        std::optional<float> penalty_area_depth = std::nullopt,
                        std::optional<float> penalty_area_width = std::nullopt,
                        std::optional<float> boundary_width = std::nullopt,
                        std::optional<float> goal_center_to_penalty_mark = std::nullopt);

  explicit FieldMessage(const protocols::perception::Field& field_proto);

  [[nodiscard]] protocols::perception::Field toProto() const override {
    return protocols::perception::Field{};
  }

  void fromProto(const protocols::perception::Field& field_proto);
};
} // namespace decision
#endif // DECISION_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H
