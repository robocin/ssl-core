#ifndef DECISION_PROCESSING_EVALUATORS_IEVALUATOR_H
#define DECISION_PROCESSING_EVALUATORS_IEVALUATOR_H

#include "decision/processing/evaluators/evaluator_result.h"

#include <robocin/output/log.h>
namespace decision {

class IEvaluator {
 public:
  IEvaluator() = default;

  IEvaluator(const IEvaluator&) = delete;
  IEvaluator& operator=(const IEvaluator&) = delete;

  IEvaluator(IEvaluator&&) = default;
  IEvaluator& operator=(IEvaluator&&) = default;

  virtual ~IEvaluator() = default;

  virtual void process() = 0;
  virtual void reset() = 0;
};

} // namespace decision

#endif /* DECISION_PROCESSING_EVALUATORS_IEVALUATOR_H */
