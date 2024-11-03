#include "decision/processing/messages/decision/decision_message.h"

#include "decision/processing/messages/behavior/behavior_message.h"

namespace decision {

TacticalPlanMessage::TacticalPlanMessage(OffensivePlanMessage offensive,
                                         DefensivePlanMessage defensive) :
    offensive(std::move(offensive)),
    defensive(std::move(defensive)) {}

DecisionMessage::DecisionMessage(BehaviorMessage behavior, TacticalPlanMessage plan) :
    behavior(std::move(behavior)),
    plan(std::move(plan)) {}

} // namespace decision
