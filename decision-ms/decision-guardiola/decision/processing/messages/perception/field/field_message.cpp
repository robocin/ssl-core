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

} // namespace decision
