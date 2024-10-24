#include "decision/processing/messages/behavior/behavior_message.h"

#include "decision/processing/messages/common/robot_id/robot_id.h"

#include <algorithm>
#include <utility>

namespace decision {
BehaviorMessage::BehaviorMessage(OutputMessage output) : output(std::move(output)) {}

OutputMessage::OutputMessage(RobotIdMessage robot_id,
                             MotionMessage motion,
                             PlanningMessage planning) :
    robot_id(std::move(robot_id)),
    motion(std::move(motion)),
    planning(std::move(planning)) {}

} // namespace decision
