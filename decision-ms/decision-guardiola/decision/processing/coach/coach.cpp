#include "decision/processing/coach/coach.h"

#include <robocin/output/log.h>

namespace decision {

Coach::Coach() { example_evaluator_ = ExampleEvaluator{}; }

void Coach::process() {
  robocin::ilog("COACH PROCESSING");
  Coach::processEvaluators();
  Coach::updateTacticalPlan();
}

void Coach::reset() { example_evaluator_.reset(); }

void Coach::processEvaluators() { example_evaluator_.process(); }

void Coach::updateTacticalPlan() {
  tactical_plan.example_evaluator_result_ = example_evaluator_.result;
}

} // namespace decision
