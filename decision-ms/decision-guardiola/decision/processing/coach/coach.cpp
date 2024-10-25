#include "decision/processing/coach/coach.h"

namespace decision {

Coach::Coach() { example_evaluator_ = makeEvaluator<ExampleEvaluator>(); }

TacticalPlan Coach::getTacticalPlan() const {
  TacticalPlan tactical_plan = TacticalPlan{};

  tactical_plan.setExampleEvaluatorResult(example_evaluator_->getExampleEvaluatorResult());

  return tactical_plan;
}

} // namespace decision
