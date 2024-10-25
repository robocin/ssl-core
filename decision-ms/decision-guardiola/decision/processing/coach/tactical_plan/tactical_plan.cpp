#include "decision/processing/coach/tactical_plan/tactical_plan.h"

namespace decision {

TacticalPlan::TacticalPlan() = default;

ExampleEvaluatorResult TacticalPlan::getExampleEvaluatorResult() {
  return example_evaluator_result_;
}

void TacticalPlan::setExampleEvaluatorResult(ExampleEvaluatorResult example_evaluator_result) {
  example_evaluator_result_ = example_evaluator_result;
}

} // namespace decision
