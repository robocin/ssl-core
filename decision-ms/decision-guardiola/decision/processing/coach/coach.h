#ifndef DECISION_PROCESSING_COACH_COACH_H
#define DECISION_PROCESSING_COACH_COACH_H

#include "decision/processing/coach/icoach.h"

#include <memory>

namespace decision {

class Coach : public ICoach {
 public:
  Coach();

  [[nodiscard]] TacticalPlan getTacticalPlan() const override;

 private:
  std::unique_ptr<ExampleEvaluator> example_evaluator_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_COACH_H */
