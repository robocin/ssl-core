#ifndef COMMUNICATION_PROCESSING_COMMUNICATION_PROCESSOR_H
#define COMMUNICATION_PROCESSING_COMMUNICATION_PROCESSOR_H

#include "communication/messaging/receiver/payload.h"
#include "communication/processing/messages/common/message_type/message_type.h"
#include "communication/processing/messages/common/robot_dribbler/robot_dribbler.h"
#include "communication/processing/messages/common/robot_id/robot_id.h"
#include "communication/processing/messages/common/robot_kick/robot_kick.h"
#include "communication/processing/messages/common/robot_velocity/robot_velocity.h"
#include "communication/processing/messages/communication/communication_message.h"
#include "communication/processing/messages/flags/flags.h"

#include <protocols/communication/communication.pb.h>
#include <robocin/parameters/parameters.h>

namespace communication {

class ICommunicationProcessor {
 public:
  ICommunicationProcessor() = default;

  ICommunicationProcessor(const ICommunicationProcessor&) = delete;
  ICommunicationProcessor& operator=(const ICommunicationProcessor&) = delete;
  ICommunicationProcessor(ICommunicationProcessor&&) = default;
  ICommunicationProcessor& operator=(ICommunicationProcessor&&) = default;

  virtual ~ICommunicationProcessor() = default;

  virtual std::optional<::protocols::communication::Communication>
  process(std::span<const Payload> payloads) = 0;
};

class CommunicationProcessor : public ICommunicationProcessor {
 public:
  explicit CommunicationProcessor(
      std::unique_ptr<::robocin::parameters::IHandlerEngine> parameters_handler_engine);

  std::optional<::protocols::communication::Communication>
  process(std::span<const Payload> payloads) override;

 private:
  std::unique_ptr<::robocin::parameters::IHandlerEngine> parameters_handler_engine_;

  std::optional<::protocols::third_party::game_controller::Referee> last_game_controller_referee_;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_COMMUNICATION_PROCESSOR_H
