#ifndef DECISION_PROCESSING_COACH_ICOACH_H
#define DECISION_PROCESSING_COACH_ICOACH_H

#include "decision/processing/coach/tactical_plan/tactical_plan.h"
#include "decision/processing/evaluators/ievaluator.h"

#include <memory>
#include <vector>

namespace decision {

class ICoach {
 public:
  ICoach() = default;

  ICoach(const ICoach&) = delete;
  ICoach& operator=(const ICoach&) = delete;
  ICoach(ICoach&&) = default;
  ICoach& operator=(ICoach&&) = default;

  virtual ~ICoach() = default;

  virtual void process() = 0;
  virtual void reset() = 0;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_ICOACH_H */
