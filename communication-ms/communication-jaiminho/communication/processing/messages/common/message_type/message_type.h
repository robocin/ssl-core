#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMON_MESSAGE_TYPE_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMON_MESSAGE_TYPE_H

#include <protocols/common/message_type.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class MessageTypeMessage : public robocin::IProtoConvertible<protocols::common::MessageType> {
  enum Message {
    UNKNOWN = 0,
    SSL_SPEED = 1,
    SSL_POSITION = 2,
    SSL_TELEMETRY = 3,
    SSL_ODOMETRY = 4,
    SSL_MOTORS = 5
  };

 public:
  explicit MessageTypeMessage(std::optional<Message> message_type = std::nullopt);

  [[nodiscard]] protocols::common::MessageType toProto() const override;

  void fromProto(protocols::common::MessageType message_type) override;

  std::optional<Message> message_type_;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_MESSAGE_TYPE_H
