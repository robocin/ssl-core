#ifndef DECISION_PROCESSING_EVALUATORS_GOALKEEPER_STATE_MACHINE_EVALUATOR_H
#define DECISION_PROCESSING_EVALUATORS_GOALKEEPER_STATE_MACHINE_EVALUATOR_H

#include "decision/processing/evaluators/evaluator_result.h"
#include "decision/processing/evaluators/ievaluator.h"

namespace decision {

enum class GoalkeeperStateMachines {
  GUARD = 0,
  TAKE_BALL_AWAY = 1,
};

class GoalkeeperStateMachineEvaluatorResult : public EvaluatorResult {
 public:
  GoalkeeperStateMachines state_machine;
  double score;

  GoalkeeperStateMachineEvaluatorResult();
  GoalkeeperStateMachineEvaluatorResult(GoalkeeperStateMachines state_machine, double score);
};

class GoalkeeperStateMachineEvaluator : public IEvaluator {
 public:
  GoalkeeperStateMachineEvaluatorResult result;

  GoalkeeperStateMachineEvaluator();

  void process(World& world) override;
  void reset() override;
};

} // namespace decision

#endif /* DECISION_PROCESSING_EVALUATORS_GOALKEEPER_STATE_MACHINE_EVALUATOR_H */
