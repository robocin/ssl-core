#ifndef DECISION_PROCESSING_EVALUATORS_IEVALUATOR_H
#define DECISION_PROCESSING_EVALUATORS_IEVALUATOR_H

namespace decision {

class IEvaluator {
 public:
  IEvaluator() = default;

  IEvaluator(const IEvaluator&) = delete;
  IEvaluator& operator=(const IEvaluator&) = delete;

  IEvaluator(IEvaluator&&) = default;
  IEvaluator& operator=(IEvaluator&&) = default;

  virtual ~IEvaluator() = default;
};

} // namespace decision

#endif /* DECISION_PROCESSING_EVALUATORS_IEVALUATOR_H */
