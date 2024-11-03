#ifndef DECISION_PROCESSING_COACH_COACH_H
#define DECISION_PROCESSING_COACH_COACH_H

#include "decision/processing/coach/icoach.h"
#include "decision/processing/coach/role_manager/role_manager.h"
#include "decision/processing/messages/behavior/behavior_message.h"

namespace decision {

class Coach : public ICoach {
 public:
  TacticalPlan tactical_plan;
  std::vector<BehaviorMessage> behaviors;

  explicit Coach();

  void process(World& world) override;
  void reset() override;
  void updateTacticalPlan();
  void updateBehavior();

 private:
  RoleManager role_manager_;
  ExampleEvaluator example_evaluator_;

  void processEvaluators(World& world);
  void processRoleManager();
};

} // namespace decision

#endif /* DECISION_PROCESSING_COACH_COACH_H */
