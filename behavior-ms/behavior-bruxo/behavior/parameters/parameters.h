#ifndef BEHAVIOR_PARAMETERS_PARAMETERS_H
#define BEHAVIOR_PARAMETERS_PARAMETERS_H

#include "behavior/processing/messages/common/robot_id/robot_id.h"

#include <robocin/parameters/parameters.h>

namespace behavior {
// NOLINTBEGIN(*comment*)

constinit const auto pBehaviorPollerTimeoutMs
    = ::robocin::parameters::View<1>::asInt32(10 /*ms ~= 100Hz*/);

constinit const auto pAllyColor = Color::COLOR_YELLOW;

constinit const auto isAttackingToRight = ::robocin::parameters::View<1>::asBool(true);

constinit const auto pBallIsMovingVelocity = ::robocin::parameters::View<1>::asInt32(300);
constinit const auto pBallIsMovingFastVelocity = ::robocin::parameters::View<1>::asInt32(850);

constinit const auto pRobotRadius = ::robocin::parameters::View<1>::asInt32(90);
constinit const auto pRobotDiameter = ::robocin::parameters::View<1>::asInt32(180);
// NOLINTEND(*comment*)
} // namespace behavior

#endif // BEHAVIOR_PARAMETERS_PARAMETERS_H
