#ifndef DECISION_PARAMETERS_PARAMETERS_H
#define DECISION_PARAMETERS_PARAMETERS_H

#include "decision/processing/messages/common/robot_id/robot_id_message.h"

#include <robocin/parameters/parameters.h>

namespace decision {
// NOLINTBEGIN(*comment*)

constinit const auto pDecisionPollerTimeoutMs
    = ::robocin::parameters::View<1>::asInt32(10 /*ms ~= 100Hz*/);

constinit const auto pAllyColor = decision::RobotIdMessage::COLOR_YELLOW;

constinit const auto isAttackingToRight = ::robocin::parameters::View<1>::asBool(true);
// NOLINTEND(*comment*)
} // namespace decision

#endif // DECISION_PARAMETERS_PARAMETERS_H
