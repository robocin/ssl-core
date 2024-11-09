#ifndef NAVIGATION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
#define NAVIGATION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H

#include "navigation/processing/messages/common/peripheral_actuation/peripheral_actuation.h"
#include "navigation/processing/messages/motion/motion_message.h"

#include <protocols/behavior/planning.pb.h>
#include <protocols/common/robot_id.pb.h>
#include <robocin/utility/iproto_convertible.h>
#include <sys/types.h>

namespace navigation {
class PlanningMessage : public robocin::IProtoConvertible<protocols::behavior::Planning> {
 public:
  PlanningMessage();
  PlanningMessage(DiscretizedPathMessage discretized_path,
                  GoToPointMessage go_to_point,
                  RotateInPointMessage rotate_in_point,
                  RotateOnSelfMessage rotate_on_self,
                  PeripheralActuationMessage peripheral_actuation);
  explicit PlanningMessage(const protocols::behavior::Planning& planning_proto);

  [[nodiscard]] protocols::behavior::Planning toProto() const override;

  DiscretizedPathMessage discretized_path;
  GoToPointMessage go_to_point;
  RotateInPointMessage rotate_in_point;
  RotateOnSelfMessage rotate_on_self;
  PeripheralActuationMessage peripheral_actuation;

  void fromProto(const protocols::behavior::Planning& planning_proto) override;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_PLANNING_PLANNING_MESSAGE_H
