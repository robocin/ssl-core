#ifndef DECISION_PROCESSING_COACH_COACH_H
#define DECISION_PROCESSING_COACH_COACH_H

#include "decision/processing/coach/icoach.h"

namespace decision {

class Coach : public ICoach {
 public:
  Coach();

  void process() override;
  void reset() override;
  TacticalPlan getTacticalPlan() override;
  void setTacticalPlan();

 private:
  std::vector<IEvaluator*> evaluators_;
  TacticalPlan tactical_plan_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_COACH_H */
