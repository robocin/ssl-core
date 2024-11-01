#include "behavior/processing/messages/common/robot_id/robot_id.h"

#include <protocols/decision/decision.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/output/log.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

class BehaviorMessage : public robocin::IProtoConvertible<protocols::decision::Behavior> {
 public:
  BehaviorMessage();

  [[nodiscard]] protocols::decision::Behavior toProto() const override;

  void fromProto(const protocols::decision::Behavior& behavior) override;

  std::optional<uint32_t> id;
  std::optional<RobotIdMessage> robot_id;
  std::optional<robocin::Point2Df> target;
};

class DecisionMessage : public robocin::IProtoConvertible<protocols::decision::Decision> {
 public:
  DecisionMessage(std::vector<BehaviorMessage> behavior = std::vector<BehaviorMessage>{});

  [[nodiscard]] protocols::decision::Decision toProto() const override;

  void fromProto(const protocols::decision::Decision& decision) override;

  std::vector<BehaviorMessage> behavior;
};

} // namespace behavior
