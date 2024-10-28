#include "decision/processing/messages/behavior/behavior_message.h"

#include "decision/processing/messages/common/robot_id/robot_id_message.h"
#include "decision/processing/messages/planning/planning_message.h"

#include <algorithm>
#include <utility>

namespace decision {
BehaviorUnificationMessage::BehaviorUnificationMessage(OutputMessage output) :
    output(std::move(output)) {}

OutputMessage::OutputMessage(RobotIdMessage robot_id,
                             MotionMessage motion,
                             PlanningMessage planning) :
    robot_id(std::move(robot_id)),
    motion(std::move(motion)),
    planning(std::move(planning)) {}

BehaviorMessage::BehaviorMessage(std::optional<uint32_t> id,
                                 std::optional<RobotIdMessage> robot_id,
                                 std::optional<robocin::Point2D<float>> target) :
    id(id),
    robot_id(std::move(robot_id)),
    target(target) {}

} // namespace decision