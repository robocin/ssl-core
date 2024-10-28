#include "decision/processing/messages/perception/field/field_message.h"

namespace decision {
FieldMessage::FieldMessage(std::optional<uint64_t> serial_id,
                           std::optional<float> length,
                           std::optional<float> width,
                           std::optional<float> goal_depth,
                           std::optional<float> goal_width,
                           std::optional<float> penalty_area_depth,
                           std::optional<float> penalty_area_width,
                           std::optional<float> boundary_width,
                           std::optional<float> goal_center_to_penalty_mark) :
    serial_id(serial_id),
    length(length),
    width(width),
    goal_depth(goal_depth),
    goal_width(goal_width),
    penalty_area_depth(penalty_area_depth),
    penalty_area_width(penalty_area_width),
    boundary_width(boundary_width),
    goal_center_to_penalty_mark(goal_center_to_penalty_mark) {}

void FieldMessage::fromProto(const protocols::perception::Field& field_proto) {
  // std::cout << "SERIAL ID: " << field_proto.serial_id() << std::endl;
  serial_id = field_proto.serial_id();
  length = field_proto.length();
  width = field_proto.width();
  goal_depth = field_proto.goal_depth();
  goal_width = field_proto.goal_width();
  penalty_area_depth = field_proto.penalty_area_depth();
  penalty_area_width = field_proto.penalty_area_width();
  boundary_width = field_proto.boundary_width();
  goal_center_to_penalty_mark = field_proto.goal_center_to_penalty_mark();
}

FieldMessage::FieldMessage(const protocols::perception::Field& field_proto) {
  FieldMessage::fromProto(field_proto);
}

} // namespace decision
