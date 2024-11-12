#ifndef BEHAVIOR_PROCESSING_IMPL_H
#define BEHAVIOR_PROCESSING_IMPL_H

#include "behavior/processing/entities/world.h"
#include "behavior/processing/messages/behavior/behavior_message.h"

#include <optional>

namespace behavior::impl {

std::optional<RobotMessage> findMyRobot(int number, std::vector<RobotMessage>& robots);

std::optional<protocols::behavior::unification::Behavior> onInGame(World& world);
std::optional<protocols::behavior::unification::Behavior> onHalt();

} // namespace behavior::impl

#endif // BEHAVIOR_PROCESSING_IMPL_H
