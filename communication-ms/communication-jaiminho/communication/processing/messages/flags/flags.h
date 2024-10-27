#ifndef COMMUNICATION_PROCESSING_MESSAGES_FLAGS_H
#define COMMUNICATION_PROCESSING_MESSAGES_FLAGS_H

#include <protocols/communication/robot_info.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class FlagsMessage : public robocin::IProtoConvertible<protocols::communication::Flags> {
 public:
  explicit FlagsMessage(std::optional<bool> robot_locked = std::nullopt,
                        std::optional<bool> critical_move = std::nullopt,
                        std::optional<bool> global_speed = std::nullopt);

  [[nodiscard]] protocols::communication::Flags toProto() const override {
    protocols::communication::Flags flags;
    flags.set_robot_locked(robot_locked.value_or(false));
    flags.set_critical_move(critical_move.value_or(false));
    flags.set_global_speed(global_speed.value_or(false));

    return flags;
  };

  void fromProto(protocols::communication::Flags flags) override {
    robot_locked = flags.robot_locked();
    critical_move = flags.critical_move();
    global_speed = flags.global_speed();
  };

  std::optional<bool> robot_locked;
  std::optional<bool> critical_move;
  std::optional<bool> global_speed;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_FLAGS_H
