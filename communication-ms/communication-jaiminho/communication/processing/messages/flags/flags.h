#ifndef COMMUNICATION_PROCESSING_MESSAGES_FLAGS_H
#define COMMUNICATION_PROCESSING_MESSAGES_FLAGS_H

#include <optional>
#include <protocols/communication/communication.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class FlagsMessage : public robocin::IProtoConvertible<protocols::communication::Flags> {
 public:
  FlagsMessage(std::optional<bool> robot_locked = std::nullopt,
               std::optional<bool> critical_move = std::nullopt,
               std::optional<bool> global_speed = std::nullopt);

  [[nodiscard]] protocols::communication::Flags toProto() const override;

  void fromProto(const protocols::communication::Flags& flags) override;

  std::optional<bool> robot_locked;
  std::optional<bool> critical_move;
  std::optional<bool> global_speed;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_FLAGS_H
