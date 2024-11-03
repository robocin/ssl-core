#ifndef BEHAVIOR_PARAMETERS_PARAMETERS_H
#define BEHAVIOR_PARAMETERS_PARAMETERS_H

#include <robocin/parameters/parameters.h>

namespace behavior {
// NOLINTBEGIN(*comment*)

constinit const auto pBehaviorPollerTimeoutMs
    = ::robocin::parameters::View<1>::asInt32(10 /*ms ~= 100Hz*/);

constinit const auto pIsYellow = ::robocin::parameters::View<1>::asBool(true);

// NOLINTEND(*comment*)
} // namespace behavior

#endif // BEHAVIOR_PARAMETERS_PARAMETERS_H
