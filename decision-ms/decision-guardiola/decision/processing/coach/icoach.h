#ifndef DECISION_PROCESSING_COACH_ICOACH_H
#define DECISION_PROCESSING_COACH_ICOACH_H

#include "decision/processing/evaluators/ievaluator.h"

namespace decision {

class ICoach {
 public:
  ICoach() = default;

  ICoach(const ICoach&) = delete;
  ICoach& operator=(const ICoach&) = delete;

  ICoach(ICoach&&) = default;
  ICoach& operator=(ICoach&&) = default;

  virtual ~ICoach() = default;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_ICOACH_H */
