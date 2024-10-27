#include "decision/processing/coach/coach.h"

namespace decision {

Coach::Coach() = default;

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

void Coach::setTacticalPlan() { tactical_plan_; }

} // namespace decision
