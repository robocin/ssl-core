#include "decision/processing/coach/coach.h"

#include <robocin/output/log.h>

namespace decision {

Coach::Coach() {
  example_evaluator_ = ExampleEvaluator{};
  role_manager_ = RoleManager{};
}

void Coach::process(World& world) {
  Coach::processEvaluators(world);
  Coach::processRoleManager();

  Coach::updateTacticalPlan();
  Coach::updateBehavior();
}

void Coach::reset() { example_evaluator_.reset(); }

void Coach::processEvaluators(World& world) { example_evaluator_.process(world); }

void Coach::processRoleManager() { role_manager_.chooseGoalkeeper(); }

void Coach::updateTacticalPlan() {
  tactical_plan.example_evaluator_result_ = example_evaluator_.result;
}

void Coach::updateBehavior() {
  std::vector<BehaviorMessage> current_behaviors;
  current_behaviors.emplace_back(role_manager_.goalkeeper_role.chooseBehavior());
}

} // namespace decision
