#include "decision/processing/decision_output/mappers/decision_output_mapper.h"

#include "decision/parameters/parameters.h"

#include <protocols/common/robot_id.pb.h>
#include <protocols/decision/decision.pb.h>

namespace decision {
namespace {
namespace rc {
using ::protocols::common::Point2Df;
using ::protocols::common::RobotId;
using ::protocols::decision::Behavior;
using ::protocols::decision::Decision;
using ::protocols::decision::DefensivePlan;
using ::protocols::decision::OffensivePlan;
using ::protocols::decision::TacticalPlan;
} // namespace rc

// TODO(fnap): refactor function name to behaviorFromSomething when something is stablished
rc::Behavior getBehavior() {
  rc::Behavior behavior;
  behavior.set_id(0);

  rc::RobotId& robot_id = *behavior.mutable_robot_id();
  robot_id.set_number(4);
  robot_id.set_color(rc::RobotId::COLOR_BLUE);

  rc::Point2Df& target = *behavior.mutable_target();
  target.set_x(199);
  target.set_y(199);

  return behavior;
}

// TODO(fnap): refactor function name to tacticalPlanFromSomething when something is stablished
rc::TacticalPlan getTacticalPlan() {
  rc::TacticalPlan plan;

  rc::DefensivePlan& defensive_plan = *plan.mutable_defensive();
  // defensive_plan.set_defensive(getDefensivePlan());

  rc::OffensivePlan& offensive_plan = *plan.mutable_offensive();
  // defensive_plan.set_defensive(getOffensivePlan());

  return plan;
}

// TODO(fnap): refactor function name to defensivePlanFromSomething when something is stablished
rc::DefensivePlan getDefensivePlan() { return rc::DefensivePlan{}; }

// TODO(fnap): refactor function name to offensivePlanFromSomething when something is stablished
rc::OffensivePlan getOffensivePlan() { return rc::OffensivePlan{}; }

} // namespace

rc::Decision DecisionOutputMapper::map() {
  rc::Decision decision_output;

  rc::Behavior& behavior_one = *decision_output.add_behavior();
  behavior_one = getBehavior();

  rc::Behavior& behavior_two = *decision_output.add_behavior();
  behavior_two = getBehavior();

  rc::TacticalPlan& plan = *decision_output.mutable_plan();
  plan = getTacticalPlan();

  return decision_output;
}
} // namespace decision
