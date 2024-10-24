#ifndef DECISION_PROCESSING_COACH_COACH_H
#define DECISION_PROCESSING_COACH_COACH_H

#include "decision/processing/coach/icoach.h"

namespace decision {

class Coach : public ICoach {
 public:
  Coach();

  [[nodiscard]] TacticalPlan getTacticalPlan() const override;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_COACH_H */
