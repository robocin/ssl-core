#ifndef BEHAVIOR_PARAMETERS_PARAMETERS_H
#define BEHAVIOR_PARAMETERS_PARAMETERS_H

#include "behavior/processing/messages/common/robot_id/robot_id.h"

#include <robocin/parameters/parameters.h>

namespace behavior {
// NOLINTBEGIN(*comment*)

constinit const auto pBehaviorPollerTimeoutMs
    = ::robocin::parameters::View<1>::asInt32(10 /*ms ~= 100Hz*/);

constinit const auto pAllyColor = Color::COLOR_BLUE; // COLOR_BLUE

constinit const auto isAttackingToRight = ::robocin::parameters::View<1>::asBool(true);

constinit const auto pBallIsMovingVelocity = ::robocin::parameters::View<2>::asInt32(300);
constinit const auto pBallIsMovingFastVelocity = ::robocin::parameters::View<3>::asInt32(850);

constinit const auto pRobotRadius = ::robocin::parameters::View<4>::asInt32(90);
constinit const auto pRobotDiameter = ::robocin::parameters::View<5>::asInt32(180);

// CBR:
constinit const auto pGoalkeeperNumber = ::robocin::parameters::View<6>::asInt32(0);
constinit const auto pForwardNumber = ::robocin::parameters::View<7>::asInt32(1);
constinit const auto pSupportNumber = ::robocin::parameters::View<8>::asInt32(2);

constinit const auto pForwardDistToEnterKickBallWhenMovingAway
    = ::robocin::parameters::View<9>::asInt32(200);

constinit const auto pForwardMaxDistToMoveAroundBallWhenIsStoppedAndLookingToBallAndTarget
    = ::robocin::parameters::View<10>::asInt32(330);

constinit const auto pApproachAngleThreshold = ::robocin::parameters::View<11>::asFloat(0.13f);

constinit const auto pFrontKickStrenght = ::robocin::parameters::View<12>::asFloat(6.5f);
constinit const auto pChipKickStrenght = ::robocin::parameters::View<13>::asFloat(6.0f);

// NOLINTEND(*comment*)
} // namespace behavior

#endif // BEHAVIOR_PARAMETERS_PARAMETERS_H
