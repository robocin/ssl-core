#include "communication/processing/messages/flags/flags.h"

namespace communication {

FlagsMessage::FlagsMessage(std::optional<bool> robot_locked,
                           std::optional<bool> critical_move,
                           std::optional<bool> global_speed) :
    robot_locked{std::move(robot_locked)},
    critical_move{std::move(critical_move)},
    global_speed{std::move(global_speed)} {}

} // namespace communication
