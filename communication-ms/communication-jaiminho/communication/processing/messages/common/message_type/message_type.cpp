#include "communication/processing/messages/common/message_type/message_type.h"

namespace communication {

MessageTypeMessage::MessageTypeMessage(std::optional<Message> message_type) :
    message_type{std::move(message_type)} {}
} // namespace communication
