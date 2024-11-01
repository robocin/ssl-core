#include "decision/processing/coach/coach.h"

namespace decision {

Coach::Coach() { example_evaluator_ = makeEvaluator<ExampleEvaluator>(); }

void Coach::process() {
  for (auto evaluator : evaluators_) {
    evaluator->process();
  }

  setTacticalPlan();
}

void Coach::reset() {
  for (auto evaluator : evaluators_) {
    evaluator->reset();
  }
}

TacticalPlan Coach::getTacticalPlan() { return tactical_plan_; }

void Coach::setTacticalPlan() {
  tactical_plan_.example_evaluator_result_
      = *dynamic_cast<ExampleEvaluatorResult*>(&example_evaluator_->getResult());
}

} // namespace decision
