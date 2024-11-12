#ifndef BEHAVIOR_PROCESSING_IMPL_H
#define BEHAVIOR_PROCESSING_IMPL_H

#include "behavior/parameters/parameters.h"
#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"
#include "behavior/processing/messages/perception/robot/robot_message.h"

#include <optional>

namespace behavior::impl {

std::optional<RobotMessage> findMyRobot(int number, std::vector<RobotMessage>& robots);

std::optional<protocols::behavior::unification::Behavior> onInGame(World& world);
std::optional<protocols::behavior::unification::Behavior> onHalt();

std::optional<RobotMessage> takeForward(std::vector<RobotMessage>& robots);
void emplaceForwardOutput(RobotMessage& forward, World& world, BehaviorMessage& behavior_message);

std::optional<RobotMessage> takeGoalkeeper(std::vector<RobotMessage>& robots);
void emplaceGoalkeeperOutput(RobotMessage& goalkeeper,
                             World& world,
                             BehaviorMessage& behavior_message);

std::optional<RobotMessage> takeSupport(std::vector<RobotMessage>& robots);
void emplaceSupportOutput(RobotMessage& support, World& world, BehaviorMessage& behavior_message);

// Logic
bool makeShouldKick(RobotMessage& robot, World& world);
bool makeChargeCapacitor(RobotMessage& robot, World& world);

float makeKickStrength(RobotMessage& robot, World& world);
} // namespace behavior::impl

#endif // BEHAVIOR_PROCESSING_IMPL_H
