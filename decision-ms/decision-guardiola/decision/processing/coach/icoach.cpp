#include "decision/processing/coach/icoach.h"

namespace decision {

TacticalPlan ICoach::process() const {
  for (auto evaluator : evaluators_) {
    evaluator->process();
  }

  return getTacticalPlan();
}

void ICoach::removeInvalidEvaluators() {
  evaluators_.erase(std::remove_if(evaluators_.begin(),
                                   evaluators_.end(),
                                   [](IEvaluator* evaluator) { return evaluator == nullptr; }),
                    evaluators_.end());
}

void ICoach::reset() {
  for (auto evaluator : evaluators_) {
    evaluator->reset();
  }
}

} // namespace decision
