#include "decision/processing/evaluators/example_evaluator.h"

#include <robocin/output/log.h>

namespace decision {

ExampleEvaluatorResult::ExampleEvaluatorResult() = default;

ExampleEvaluator::ExampleEvaluator() { reset(); }

void ExampleEvaluator::process() { robocin::ilog("EXAMPLE EVALUATOR WORKING"); }

void ExampleEvaluator::reset() { example_evaluator_result_ = ExampleEvaluatorResult{}; }

EvaluatorResult& ExampleEvaluator::getResult() {
  //   return example_evaluator_result_;
  return example_evaluator_result_;
}

} // namespace decision
