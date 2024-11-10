#ifndef DECISION_PROCESSING_EVALUATORS_GOALKEEPER_STATE_MACHINE_EVALUATOR_H
#define DECISION_PROCESSING_EVALUATORS_GOALKEEPER_STATE_MACHINE_EVALUATOR_H

#include "decision/processing/entities/machine_states.h"
#include "decision/processing/evaluators/evaluator_result.h"
#include "decision/processing/evaluators/ievaluator.h"

namespace decision {

class GoalkeeperStateMachineEvaluatorResult : public EvaluatorResult {
 public:
  MachineStates::GoalkeeperStateMachines state_machine;
  double score;

  GoalkeeperStateMachineEvaluatorResult();
  GoalkeeperStateMachineEvaluatorResult(MachineStates::GoalkeeperStateMachines state_machine,
                                        double score);
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
