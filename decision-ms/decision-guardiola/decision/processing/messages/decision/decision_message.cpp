#include "decision/processing/messages/decision/decision_message.h"

namespace decision {

TacticalPlanMessage::TacticalPlanMessage(OffensivePlanMessage offensive,
                                         DefensivePlanMessage defensive) :
    offensive(std::move(offensive)),
    defensive(std::move(defensive)) {}
} // namespace decision
