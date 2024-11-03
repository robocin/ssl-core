#ifndef DECISION_PROCESSING_COACH_COACH_H
#define DECISION_PROCESSING_COACH_COACH_H

#include "decision/processing/coach/icoach.h"

namespace decision {

class Coach : public ICoach {
 public:
  TacticalPlan tactical_plan;

  Coach();

  void process(World& world) override;
  void reset() override;
  void updateTacticalPlan();

 private:
  ExampleEvaluator example_evaluator_;

  void processEvaluators(World& world);
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_COACH_H */
