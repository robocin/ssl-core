#include "decision/processing/evaluators/example_evaluator.h"

#include <robocin/output/log.h>

namespace decision {

ExampleEvaluatorResult::ExampleEvaluatorResult() = default;

ExampleEvaluator::ExampleEvaluator() { reset(); }

void ExampleEvaluator::process(World& world) {
  // robocin::ilog("EXAMPLE EVALUATOR WORKING");
}

void ExampleEvaluator::reset() { result = ExampleEvaluatorResult{}; }

} // namespace decision
