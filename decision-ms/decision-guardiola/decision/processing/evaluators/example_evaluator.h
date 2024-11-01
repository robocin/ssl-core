#ifndef DECISION_PROCESSING_EVALUATORS_EXAMPLE_EVALUATOR_H
#define DECISION_PROCESSING_EVALUATORS_EXAMPLE_EVALUATOR_H

#include "decision/processing/evaluators/evaluator_result.h"
#include "decision/processing/evaluators/ievaluator.h"

namespace decision {

class ExampleEvaluatorResult : public EvaluatorResult {
 public:
  ExampleEvaluatorResult();
};

class ExampleEvaluator : public IEvaluator {
 public:
  ExampleEvaluator();

  void process() override;
  void reset() override;
  EvaluatorResult& getResult() override;

 private:
  ExampleEvaluatorResult example_evaluator_result_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_EVALUATORS_EXAMPLE_EVALUATOR_H */
