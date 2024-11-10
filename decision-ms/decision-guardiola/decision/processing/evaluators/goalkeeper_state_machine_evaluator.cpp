#include "decision/processing/evaluators/goalkeeper_state_machine_evaluator.h"

#include "decision/processing/analyzer/field_analyzer.h"
#include "decision/processing/entities/machine_states.h"

#include <robocin/geometry/point2d.h>
#include <robocin/output/log.h>

namespace decision {

GoalkeeperStateMachineEvaluatorResult::GoalkeeperStateMachineEvaluatorResult() = default;

GoalkeeperStateMachineEvaluatorResult::GoalkeeperStateMachineEvaluatorResult(
    MachineStates::GoalkeeperStateMachines state_machine,
    double score) :
    state_machine(state_machine),
    score(score) {}

GoalkeeperStateMachineEvaluator::GoalkeeperStateMachineEvaluator() { reset(); }

void GoalkeeperStateMachineEvaluator::process(World& world) {
  auto&& field = world.field;
  auto&& ball = world.ball;

  robocin::Point2Df ball_position = robocin::Point2Df(ball.position->x, ball.position->y);
  robocin::Point2Df ball_velocity = robocin::Point2Df(ball.velocity->x, ball.velocity->y);

  bool is_ball_inside_area = FieldAnalyzer::allyPenaltyAreaContains(ball_position, field);
  bool is_ball_stopped = ball_velocity.length() < 300;
  bool is_ball_moving_slowly = ball_velocity.length() > 300 && ball_velocity.length() < 850;
  bool is_ball_moving_to_enemy_side
      = !is_ball_stopped && ((ball_velocity.x * field.attackDirection().x) > 0);
  bool is_ball_slow_and_moving_away_from_our_goal
      = is_ball_moving_slowly && is_ball_moving_to_enemy_side;

  bool should_take_ball_away
      = is_ball_inside_area && (is_ball_stopped || is_ball_slow_and_moving_away_from_our_goal);

  if (should_take_ball_away) {
    result = {MachineStates::GoalkeeperStateMachines::TAKE_BALL_AWAY, 1.0};
  } else {
    result = {MachineStates::GoalkeeperStateMachines::GUARD, 1.0};
  }
}

void GoalkeeperStateMachineEvaluator::reset() { result = GoalkeeperStateMachineEvaluatorResult{}; }

} // namespace decision
