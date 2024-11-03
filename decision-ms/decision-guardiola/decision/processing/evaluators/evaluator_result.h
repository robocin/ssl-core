#ifndef DECISION_PROCESSING_EVALUATORS_EVALUATOR_RESULT_H
#define DECISION_PROCESSING_EVALUATORS_EVALUATOR_RESULT_H

namespace decision {

class EvaluatorResult {
 public:
  EvaluatorResult() = default;

  EvaluatorResult(const EvaluatorResult&) = default;
  EvaluatorResult& operator=(const EvaluatorResult&) = default;

  EvaluatorResult(EvaluatorResult&&) = default;
  EvaluatorResult& operator=(EvaluatorResult&&) = default;

  virtual ~EvaluatorResult() = default;
};

} // namespace decision

#endif /* DECISION_PROCESSING_EVALUATORS_EVALUATOR_RESULT_H */
