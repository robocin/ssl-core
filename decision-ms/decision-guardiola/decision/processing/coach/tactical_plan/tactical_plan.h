#ifndef DECISION_PROCESSING_COACH_TACTICAL_PLAN_TACTICAL_PLAN_H
#define DECISION_PROCESSING_COACH_TACTICAL_PLAN_TACTICAL_PLAN_H

#include "decision/processing/evaluators/example_evaluator.h"
#include "decision/processing/evaluators/goalkeeper_state_machine_evaluator.h"

namespace decision {

class TacticalPlan {
 public:
  TacticalPlan();

  ExampleEvaluatorResult example_evaluator_result_;
  GoalkeeperStateMachineEvaluatorResult goalkeeper_state_machine_evaluator_result_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_TACTICAL_PLAN_TACTICAL_PLAN_H */
