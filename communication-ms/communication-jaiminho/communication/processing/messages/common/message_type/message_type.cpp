#include "communication/processing/messages/common/message_type/message_type.h"

namespace communication {

MessageTypeMessage::MessageTypeMessage(std::optional<Message> message_type) :
    message_type_(message_type) {}

protocols::common::MessageType MessageTypeMessage::toProto() const {
  return static_cast<protocols::common::MessageType>(message_type_.value_or(Message::UNKNOWN));
}

void MessageTypeMessage::fromProto(protocols::common::MessageType message_type) {
  this->message_type_ = static_cast<Message>(message_type);
}

} // namespace communication
