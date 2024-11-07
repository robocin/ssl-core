#include "communication/processing/messages/flags/flags.h"

namespace communication {

FlagsMessage::FlagsMessage(std::optional<bool> robot_locked,
                           std::optional<bool> critical_move,
                           std::optional<bool> global_speed) :
    robot_locked(std::move(robot_locked)),
    critical_move(std::move(critical_move)),
    global_speed(std::move(global_speed)) {}

protocols::communication::Flags FlagsMessage::toProto() const {
  protocols::communication::Flags flags;
  flags.set_robot_locked(robot_locked.value_or(false));
  flags.set_critical_move(critical_move.value_or(false));
  flags.set_global_speed(global_speed.value_or(false));

  return flags;
}

void FlagsMessage::fromProto(protocols::communication::Flags flags) {
  robot_locked = flags.robot_locked();
  critical_move = flags.critical_move();
  global_speed = flags.global_speed();
}

} // namespace communication
