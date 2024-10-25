#ifndef DECISION_PROCESSING_EVALUATORS_EXAMPLE_EVALUATOR_H
#define DECISION_PROCESSING_EVALUATORS_EXAMPLE_EVALUATOR_H

#include "decision/processing/evaluators/ievaluator.h"

namespace decision {

class ExampleEvaluatorResult {
 public:
  ExampleEvaluatorResult();
};

class ExampleEvaluator : public IEvaluator {
 public:
  ExampleEvaluator();

  void process() override;
  void reset() override;

  [[nodiscard]] ExampleEvaluatorResult getExampleEvaluatorResult() const;

 private:
  ExampleEvaluatorResult example_evaluator_result_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_EVALUATORS_EXAMPLE_EVALUATOR_H */
