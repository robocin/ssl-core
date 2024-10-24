#include "decision/processing/messages/behavior/behavior_message.h"
#include "decision/processing/messages/iproto_convertible.h"
#include "protocols/decision/decision.pb.h"

#include <vector>

namespace decision {
class DefensivePlanMessage : public IProtoConvertible<protocols::decision::DefensivePlan> {
 public:
  explicit DefensivePlanMessage();

  [[nodiscard]] protocols::decision::DefensivePlan toProto() const override {
    return protocols::decision::DefensivePlan{};
  };
};

class OffensivePlanMessage : public IProtoConvertible<protocols::decision::OffensivePlan> {
 public:
  explicit OffensivePlanMessage();

  [[nodiscard]] protocols::decision::OffensivePlan toProto() const override {
    return protocols::decision::OffensivePlan{};
  };
};

class TacticalPlanMessage : public IProtoConvertible<protocols::decision::TacticalPlan> {
 public:
  explicit TacticalPlanMessage(OffensivePlanMessage offensive, DefensivePlanMessage defensive);

  OffensivePlanMessage offensive;
  DefensivePlanMessage defensive;

  [[nodiscard]] protocols::decision::TacticalPlan toProto() const override {
    return protocols::decision::TacticalPlan{};
  };
};

class DecisionMessage : public IProtoConvertible<protocols::decision::Decision> {
 public:
  explicit DecisionMessage(std::vector<BehaviorMessage>& behavior, TacticalPlanMessage plan);

  std::vector<BehaviorMessage> behavior;
  TacticalPlanMessage plan;

  [[nodiscard]] protocols::decision::Decision toProto() const override {
    return protocols::decision::Decision{};
  };
};

} // namespace decision
