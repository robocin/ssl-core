#ifndef BEHAVIOR_PARAMETERS_PARAMETERS_H
#define BEHAVIOR_PARAMETERS_PARAMETERS_H

#include "behavior/processing/messages/common/robot_id/robot_id.h"

#include <robocin/parameters/parameters.h>

namespace behavior {
// NOLINTBEGIN(*comment*)

constinit const auto pBehaviorPollerTimeoutMs
    = ::robocin::parameters::View<1>::asInt32(10 /*ms ~= 100Hz*/);

constinit const auto pAllyColor = Color::COLOR_BLUE;

// NOLINTEND(*comment*)
} // namespace behavior

#endif // BEHAVIOR_PARAMETERS_PARAMETERS_H
