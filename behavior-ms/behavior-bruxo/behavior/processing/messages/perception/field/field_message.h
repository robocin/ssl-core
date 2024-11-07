#ifndef BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H

#include <cstdint>
#include <optional>
#include <protocols/perception/detection.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

class FieldMessage : public robocin::IProtoConvertible<protocols::perception::Field> {
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

  [[nodiscard]] protocols::perception::Field toProto() const override;

  void fromProto(const protocols::perception::Field& field_proto) override;
};
} // namespace behavior
#endif // BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H
