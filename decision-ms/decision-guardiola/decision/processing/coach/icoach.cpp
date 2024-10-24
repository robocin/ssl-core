#include "decision/processing/coach/icoach.h"

namespace decision {

TacticalPlan ICoach::process() const {
  for (auto evaluator : evaluators_) {
    evaluator->process();
  }

  return getTacticalPlan();
}

void ICoach::reset() {
  for (auto evaluator : evaluators_) {
    evaluator->reset();
  }
}

} // namespace decision
