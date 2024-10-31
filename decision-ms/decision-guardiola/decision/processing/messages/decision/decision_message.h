#include "decision/processing/messages/behavior/behavior_message.h"
#include "protocols/decision/decision.pb.h"

#include <robocin/utility/iproto_convertible.h>
#include <vector>

namespace decision {
class DefensivePlanMessage : public robocin::IProtoConvertible<protocols::decision::DefensivePlan> {
 public:
  explicit DefensivePlanMessage() = default;

  [[nodiscard]] protocols::decision::DefensivePlan toProto() const override {
    return protocols::decision::DefensivePlan{};
  };

  void fromProto(const protocols::decision::DefensivePlan& defensive_plan_proto) override;
};

class OffensivePlanMessage : public robocin::IProtoConvertible<protocols::decision::OffensivePlan> {
 public:
  explicit OffensivePlanMessage() = default;

  [[nodiscard]] protocols::decision::OffensivePlan toProto() const override {
    return protocols::decision::OffensivePlan{};
  };

  void fromProto(const protocols::decision::OffensivePlan& offensive_plan_proto) override;
};

class TacticalPlanMessage : public robocin::IProtoConvertible<protocols::decision::TacticalPlan> {
 public:
  explicit TacticalPlanMessage(OffensivePlanMessage offensive = OffensivePlanMessage{},
                               DefensivePlanMessage defensive = DefensivePlanMessage{});

  OffensivePlanMessage offensive;
  DefensivePlanMessage defensive;

  [[nodiscard]] protocols::decision::TacticalPlan toProto() const override {
    return protocols::decision::TacticalPlan{};
  };

  void fromProto(const protocols::decision::TacticalPlan& tactical_plan_proto) override;
};

class DecisionMessage : public robocin::IProtoConvertible<protocols::decision::Decision> {
 public:
  explicit DecisionMessage(std::vector<BehaviorMessage> behavior = std::vector<BehaviorMessage>{},
                           TacticalPlanMessage plan = TacticalPlanMessage{});

  std::vector<BehaviorMessage> behavior;
  TacticalPlanMessage plan;

  [[nodiscard]] protocols::decision::Decision toProto() const override {
    return protocols::decision::Decision{};
  };

  void fromProto(const protocols::decision::Decision& decision_proto) override;
};

} // namespace decision
