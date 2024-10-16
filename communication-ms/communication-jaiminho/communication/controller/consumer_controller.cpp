#include "communication/controller/consumer_controller.h"

#include "communication/messaging/receiver/payload.h"

#include <protocols/communication/robot_info.pb.h>
#include <robocin/concurrency/concurrent_queue.h>
#include <robocin/memory/object_ptr.h>
#include <robocin/output/log.h>

namespace communication {
namespace {

using ::robocin::IConcurrentQueue;
using ::robocin::ilog;
using ::robocin::object_ptr;

namespace rc {

using ::protocols::communication::RobotComm;

} // namespace rc

} // namespace

ConsumerController::ConsumerController(object_ptr<IConcurrentQueue<Payload>> messages,
                                       std::unique_ptr<ICommunicationProcessor> communication_processor,
                                       std::unique_ptr<IMessageSender> message_sender) :
    messages_{messages},
    communication_processor_{std::move(communication_processor)},
    message_sender_{std::move(message_sender)} {}

void ConsumerController::run() {
  // ilog("running.");

  while (true) {
    std::vector<Payload> payloads = messages_->dequeue_all();

    exec(payloads);
  }
}

void ConsumerController::exec(std::span<const Payload> payloads) {
  // ilog("payloads {} empty.", payloads.empty() ? "is" : "isn't");

  if (payloads.empty()) {
    return;
  }

  if (std::optional<rc::RobotComm> comm = communication_processor_->process(payloads);
      comm != std::nullopt) {
    if(comm->has_command()) {
      message_sender_->send(*comm->command());
    }
  }
}

} // namespace communication
