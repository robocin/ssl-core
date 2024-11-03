#ifndef BEHAVIOR_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H

#include "behavior/processing/messages/common/robot_id/robot_id.h"
#include "behavior/processing/messages/motion/motion_message.h"
#include "behavior/processing/messages/planning/planning_message.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <robocin/output/log.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

/**
 * @class OutputMessage
 * @brief A class that represents the output of the behavior module.
 *
 * This class is used to represent the output of the behavior module. It contains the robot id, the
 * motion, and the planning.
 */

class OutputMessage : public robocin::IProtoConvertible<protocols::behavior::unification::Output> {
 public:
  OutputMessage(RobotIdMessage robot_id = RobotIdMessage{},
                MotionMessage motion = MotionMessage{},
                PlanningMessage planning = PlanningMessage{});

  [[nodiscard]] protocols::behavior::unification::Output toProto() const override;

  void fromProto(const protocols::behavior::unification::Output& output) override;

  RobotIdMessage robot_id;
  MotionMessage motion;
  PlanningMessage planning;
};

/**
 * @class BehaviorMessage
 * @brief A class that represents the behavior message.
 *
 * This class is used to represent the behavior message. It contains a vector of output messages.
 */
class BehaviorMessage
    : public robocin::IProtoConvertible<protocols::behavior::unification::Behavior> {
 public:
  BehaviorMessage(std::vector<OutputMessage> output = std::vector<OutputMessage>{});

  [[nodiscard]] protocols::behavior::unification::Behavior toProto() const override;

  void fromProto(const protocols::behavior::unification::Behavior& behavior) override;

  std::vector<OutputMessage> output;
};

} // namespace behavior

#endif // BEHAVIOR_PROCESSING_MESSAGES_BEHAVIOR_BEHAVIOR_MESSAGE_H
