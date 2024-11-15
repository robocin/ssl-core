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

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
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
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  auto milliseconds
      = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
  std::cout << "PROCESSING BEHAVIOR "
            << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3)
            << std::setfill('0') << milliseconds.count() << std::endl;

  if (world_.isHalt() || world_.isTimeout()) {
    direct_timer_ = std::chrono::steady_clock::now();
    kick_off_timer_ = std::chrono::steady_clock::now();

    ilog("HALT");
    return impl::onHalt(world_);
  }

  if (world_.isStop()) {
    direct_timer_ = std::chrono::steady_clock::now();
    kick_off_timer_ = std::chrono::steady_clock::now();

    ilog("STOP");
    return impl::onStop(world_, *goalkeeper_guard_state_machine_);
  }

  if (world_.isInGame()) {
    direct_timer_ = std::chrono::steady_clock::now();
    kick_off_timer_ = std::chrono::steady_clock::now();

    ilog("IN GAME");
    return impl::onInGame(world_,
                          *goalkeeper_guard_state_machine_,
                          *forward_follow_and_kick_ball_state_machine_,
                          *goalkeeper_take_ball_away_state_machine_);
  }

  if (world_.isPenalty()) {
    direct_timer_ = std::chrono::steady_clock::now();
    kick_off_timer_ = std::chrono::steady_clock::now();

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
    kick_off_timer_ = std::chrono::steady_clock::now();

    auto curr_time = std::chrono::steady_clock::now();
    auto time_since_last_direct
        = std::chrono::duration_cast<std::chrono::seconds>(curr_time - direct_timer_);

    if (world_.game_status.command->away_direct_free_kick.has_value()) {

      if (time_since_last_direct.count() < pWaitDirectFreeKick()) {
        ilog("Waiting direct free kick: {}s", time_since_last_direct.count());
        return impl::onStop(world_, *goalkeeper_guard_state_machine_);
      }
    }

    ilog("IN GAME FROM FREE KICK");
    return impl::onInGame(world_,
                          *goalkeeper_guard_state_machine_,
                          *forward_follow_and_kick_ball_state_machine_,
                          *goalkeeper_take_ball_away_state_machine_);
  }

  if (world_.isKickOff()) {
    direct_timer_ = std::chrono::steady_clock::now();

    auto curr_time = std::chrono::steady_clock::now();
    auto time_since_last_kickoff
        = std::chrono::duration_cast<std::chrono::seconds>(curr_time - kick_off_timer_);

    if (world_.game_status.command->away_prepare_kickoff.has_value()) {
      ilog("IN GAME FROM KICKOFF");
      return impl::onStop(world_, *goalkeeper_guard_state_machine_);
    }

    if (world_.game_status.command->away_kickoff.has_value()) {
      if (time_since_last_kickoff.count() < pWaitKickOff()) {
        ilog("Waiting kickoff: {}s", time_since_last_kickoff.count());
        return impl::onStop(world_, *goalkeeper_guard_state_machine_);
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
