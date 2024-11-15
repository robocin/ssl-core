#include "behavior/processing/behavior_processor.h"

#include "behavior/behavior_message.h"
#include "behavior/messaging/receiver/payload.h"
#include "behavior/parameters/parameters.h"
#include "behavior/processing/impl/impl.h"
#include "common/game_command/game_command_message.h"
#include "common/robot_id/robot_id.h"
#include "motion/motion_message.h"
#include "perception/robot/robot_message.h"
#include "state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"

#include <optional>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>
#include <ranges>
#include <robocin/geometry/point2d.h>
#include <robocin/memory/object_ptr.h>
#include <robocin/output/log.h>
#include <vector>

namespace behavior {

namespace parameters = ::robocin::parameters;

namespace {

using ::robocin::ilog;
using ::robocin::object_ptr;

namespace rc {

using ::protocols::common::RobotId;
using ::protocols::decision::Decision;
using ::protocols::perception::Ball;
using ::protocols::perception::Detection;

using ::protocols::behavior::GoToPoint;
using ::protocols::behavior::unification::Behavior;
using ::protocols::behavior::unification::Motion;
using ::protocols::behavior::unification::Output;

using ::protocols::perception::Robot;

using ::protocols::referee::GameStatus;

} // namespace rc

std::vector<rc::Detection> detectionFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDetectionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::Decision> decisionfromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getDecisionMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

std::vector<rc::GameStatus> gameStatusFromPayloads(std::span<const Payload> payloads) {
  return payloads | std::views::transform(&Payload::getGameStatusMessages) | std::views::join
         | std::ranges::to<std::vector>();
}

} // namespace

BehaviorProcessor::BehaviorProcessor(
    std::unique_ptr<parameters::IHandlerEngine> parameters_handler_engine,
    std::unique_ptr<::behavior::GoalkeeperGuardStateMachine> goalkeeper_guard_state_machine,
    std::unique_ptr<::behavior::ForwardFollowAndKickBallStateMachine>
        forward_follow_and_kick_ball_state_machine,
    std::unique_ptr<::behavior::GoalkeeperTakeBallAwayStateMachine>
        goalkeeper_take_ball_away_state_machine) :
    parameters_handler_engine_{std::move(parameters_handler_engine)},
    goalkeeper_guard_state_machine_{std::move(goalkeeper_guard_state_machine)},
    forward_follow_and_kick_ball_state_machine_{
        std::move(forward_follow_and_kick_ball_state_machine)},
    goalkeeper_take_ball_away_state_machine_{std::move(goalkeeper_take_ball_away_state_machine)} {}

std::optional<rc::Behavior> BehaviorProcessor::process(std::span<const Payload> payloads) {
  if (!BehaviorProcessor::update(payloads)) {
    ilog("Failed to update world.");
    return std::nullopt;
  }

  if (world_.isHalt() || world_.isTimeout()) {
    ilog("HALT");
    return impl::onHalt();
  }

  if (world_.isStop()) {
    ilog("STOP");
    return impl::onStop(world_, *goalkeeper_guard_state_machine_);
  }

  if (world_.isInGame()) {
    ilog("IN GAME");
    return impl::onInGame(world_,
                          *goalkeeper_guard_state_machine_,
                          *forward_follow_and_kick_ball_state_machine_,
                          *goalkeeper_take_ball_away_state_machine_);
  }

  if (world_.isPenalty()) {
    ilog("IN PENALTY");
    if (world_.game_status.command->away_penalty.has_value()
        || world_.game_status.command->away_prepare_penalty.has_value()) {
      ilog("AWAY PENALTY");
      return impl::onAwayPenalty(world_, *goalkeeper_guard_state_machine_);
    }

    if (world_.game_status.command->home_prepare_penalty.has_value()) {
      ilog("PREPARE HOME PENALTY");
      return impl::onPrepareHomePenalty(world_, *goalkeeper_guard_state_machine_);
    }

    ilog("IN GAME FROM PENALTY");
    return impl::onInGame(world_,
                          *goalkeeper_guard_state_machine_,
                          *forward_follow_and_kick_ball_state_machine_,
                          *goalkeeper_take_ball_away_state_machine_);
  }

  if (world_.isDirectFreeKick()) {
    // Se eh direct deles e ainda tem tempo
    if (world_.game_status.command->away_direct_free_kick.has_value()) {
      if (world_.game_status.command->away_direct_free_kick->remaining_time.has_value()) {
        if (world_.game_status.command->away_direct_free_kick->remaining_time.value() > 0) {
          ilog("DIRECT FREE KICK REMAINING");
          return impl::onStop(world_, *goalkeeper_guard_state_machine_);
        }
      }
    }

    ilog("IN GAME FROM FREE KICK");
    return impl::onInGame(world_,
                          *goalkeeper_guard_state_machine_,
                          *forward_follow_and_kick_ball_state_machine_,
                          *goalkeeper_take_ball_away_state_machine_);
  }

  if (world_.isKickOff()) {
    if (world_.game_status.command->away_prepare_kickoff.has_value()
        || world_.game_status.command->home_prepare_kickoff.has_value()) {
      ilog("PREPARE KICKOFF");
      return impl::onStop(world_, *goalkeeper_guard_state_machine_);
    }

    if (world_.game_status.command->away_kickoff.has_value()) {
      if (world_.game_status.command->away_kickoff->remaining_time.has_value()) {
        if (world_.game_status.command->away_kickoff->remaining_time.value() > 0) {
          ilog("KICKOFF REMAINING");
          return impl::onStop(world_, *goalkeeper_guard_state_machine_);
        }
      }
    }

    ilog("IN GAME FROM KICKOFF");
    return impl::onInGame(world_,
                          *goalkeeper_guard_state_machine_,
                          *forward_follow_and_kick_ball_state_machine_,
                          *goalkeeper_take_ball_away_state_machine_);
  }

  ilog("NADA");
  return std::nullopt;
}

bool BehaviorProcessor::update(std::span<const Payload>& payloads) {
  if (std::vector<rc::GameStatus> game_status_messages = gameStatusFromPayloads(payloads);
      !game_status_messages.empty()) {
    last_game_status_ = game_status_messages.back();
  }

  if (!last_game_status_) {
    ilog("NO GAME STATUS");
    return false;
  }

  std::vector<rc::Detection> detection_messages = detectionFromPayloads(payloads);
  if (detection_messages.empty()) {
    ilog("NO DETECTION");
    // a new package must be generated only when a new detection is received.
    return false;
  }

  last_detection_ = detection_messages.back();

  world_.update({last_detection_->robots().begin(), last_detection_->robots().end()},
                {last_detection_->balls().begin(), last_detection_->balls().end()},
                last_detection_->field(),
                last_game_status_.value());

  return true;
}

} // namespace behavior
