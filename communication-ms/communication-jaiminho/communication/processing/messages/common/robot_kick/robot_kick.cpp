#include "communication/processing/messages/common/robot_kick/robot_kick.h"

namespace communication {

KickCommandMessage::KickCommandMessage(std::optional<double> kick_strength,
                                       std::optional<bool> is_front,
                                       std::optional<bool> is_chip,
                                       std::optional<bool> charge_capacitor,
                                       std::optional<bool> is_bypass_ir) :
    kick_strength{std::move(kick_strength)},
    is_front{std::move(is_front)},
    is_chip{std::move(is_chip)},
    charge_capacitor{std::move(charge_capacitor)},
    is_bypass_ir{std::move(is_bypass_ir)} {}

RobotKickMessage::RobotKickMessage(KickCommandMessage kick_command) :
    kick_command{std::move(kick_command)} {}

} // namespace communication
