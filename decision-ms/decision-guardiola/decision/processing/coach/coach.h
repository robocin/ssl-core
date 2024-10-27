#ifndef DECISION_PROCESSING_COACH_COACH_H
#define DECISION_PROCESSING_COACH_COACH_H

#include "decision/processing/coach/icoach.h"

namespace decision {

class Coach : public ICoach {
 public:
  Coach();

  void process() override;
  void reset() override;
  TacticalPlan getTacticalPlan() override;
  void setTacticalPlan();
  template <std::derived_from<IEvaluator> T, class... Args>
  [[nodiscard]] std::unique_ptr<T> makeEvaluator(Args&&... args) {
    auto evaluator = std::make_unique<T>(std::forward<Args>(args)...);
    evaluators_.emplace_back(evaluator.get());
    return std::move(evaluator);
  }

 private:
  std::vector<IEvaluator*> evaluators_;
  TacticalPlan tactical_plan_;

  std::unique_ptr<ExampleEvaluator> example_evaluator_;
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_COACH_H */
