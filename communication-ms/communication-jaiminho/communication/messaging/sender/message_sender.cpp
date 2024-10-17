#include "communication/messaging/sender/message_sender.h"

#include <protocols/perception/detection.pb.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>

namespace communication {
namespace {

namespace service_discovery = robocin::service_discovery;

using ::robocin::ilog;

namespace rc {

using ::protocols::communication::RobotInfo;

} // namespace rc

} // namespace

MessageSender::MessageSender(std::unique_ptr<::robocin::IZmqPublisherSocket> communication_socket) :
    communication_socket_{std::move(communication_socket)} {}

void MessageSender::send(const rc::RobotInfo& robot_command) {
  // ilog("sending... {}", game_status.DebugString());

  communication_socket_->send({
      service_discovery::kCommunicationCommandTopic,
      robot_command.SerializeAsString(),
  });
}

} // namespace communication
