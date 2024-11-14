#ifndef BEHAVIOR_PROCESSING_IMPL_H
#define BEHAVIOR_PROCESSING_IMPL_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/analyzer/ball_analyzer.h"
#include "behavior/processing/analyzer/field_analyzer.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"
#include "behavior/processing/state_machine/goalkeeper_guard/goalkeeper_guard_state_machine.h"
#include "behavior/processing/state_machine/istate_machine.h"
#include "forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h"
#include "forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.h"
#include "goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h"

#include <optional>

namespace behavior::impl {

std::optional<RobotMessage> findMyRobot(int number, std::vector<RobotMessage>& robots);

// Game states
std::optional<protocols::behavior::unification::Behavior>
onInGame(World& world,
         GoalkeeperGuardStateMachine& guard_state_machine,
         ForwardFollowAndKickBallStateMachine& forward_follow_and_kick_ball_state_machine,
         GoalkeeperTakeBallAwayStateMachine& take_ball_away_state_machine);
std::optional<protocols::behavior::unification::Behavior> onHalt();
std::optional<protocols::behavior::unification::Behavior> onStop(World& world, GoalkeeperGuardStateMachine& guard_state_machine);

std::optional<RobotMessage> takeForward(std::vector<RobotMessage>& robots);
void emplaceForwardOutput(RobotMessage& forward, World& world, BehaviorMessage& behavior_message);

std::optional<RobotMessage> takeGoalkeeper(std::vector<RobotMessage>& robots);
void emplaceGoalkeeperOutput(RobotMessage& goalkeeper,
                             World& world,
                             BehaviorMessage& behavior_message,
                             GoalkeeperGuardStateMachine& guard_state_machine);

std::optional<RobotMessage> takeSupport(std::vector<RobotMessage>& robots);
void emplaceSupportOutput(RobotMessage& support, World& world, BehaviorMessage& behavior_message);

// Logic
bool makeShouldKick(RobotMessage& robot, World& world);
bool makeChargeCapacitor(RobotMessage& robot, World& world);
bool shouldTakeBallAway(World& world);

float makeKickStrength(RobotMessage& robot, World& world);
} // namespace behavior::impl

#endif // BEHAVIOR_PROCESSING_IMPL_H
