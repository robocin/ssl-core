#ifndef DECISION_PROCESSING_COACH_ICOACH_H
#define DECISION_PROCESSING_COACH_ICOACH_H

#include "decision/processing/coach/tactical_plan/tactical_plan.h"
#include "decision/processing/evaluators/ievaluator.h"

#include <concepts>
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

  [[nodiscard]] TacticalPlan process() const;
  void reset();
  void removeInvalidEvaluators();

 protected:
  [[nodiscard]] virtual TacticalPlan getTacticalPlan() const = 0;

  template <std::derived_from<IEvaluator> T, class... Args>
  [[nodiscard]] std::unique_ptr<T> makeEvaluator(Args&&... args) {
    auto evaluator = std::make_unique<T>(std::forward<Args>(args)...);
    evaluators_.emplace_back(evaluator.get());
    return std::move(evaluator);
  }

 private:
  std::vector<IEvaluator*> evaluators_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_ICOACH_H */
