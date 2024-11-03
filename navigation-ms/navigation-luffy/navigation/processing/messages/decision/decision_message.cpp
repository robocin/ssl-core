#include "navigation/processing/messages/decision/decision_message.h"

namespace navigation {

TacticalPlanMessage::TacticalPlanMessage(OffensivePlanMessage offensive,
                                         DefensivePlanMessage defensive) :
    offensive(std::move(offensive)),
    defensive(std::move(defensive)) {}

DecisionMessage::DecisionMessage(std::vector<BehaviorMessage> behavior, TacticalPlanMessage plan) :
    behavior(std::move(behavior)),
    plan(std::move(plan)) {}

} // namespace navigation
