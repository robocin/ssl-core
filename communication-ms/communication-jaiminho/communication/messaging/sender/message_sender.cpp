#include "communication/messaging/sender/message_sender.h"

#include "message_sender.h"

#include <protocols/perception/detection.pb.h>
#include <protocols/third_party/simulation/robot_control.pb.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>

namespace communication {
namespace {

namespace service_discovery = robocin::service_discovery;

using ::robocin::ilog;

namespace rc {

using ::protocols::communication::Communication;

} // namespace rc

namespace tp {

using ::protocols::third_party::simulation::RobotControl;

} // namespace tp

} // namespace

MessageSender::MessageSender(std::unique_ptr<::robocin::IZmqPublisherSocket> communication_socket,
                             std::unique_ptr<::robocin::IUdpMulticastSocketSender> robot_socket,
                             std::unique_ptr<::robocin::IUdpMulticastSocketSender> simm_socket) :
    communication_socket_{std::move(communication_socket)},
    robot_socket_{std::move(robot_socket)},
    simm_socket_{std::move(simm_socket)} {}

void MessageSender::send(const rc::Communication& robot_command) {
  ilog("sending...robot_command {}", robot_command.DebugString());

  communication_socket_->send({
      service_discovery::kCommunicationCommandTopic,
      robot_command.SerializeAsString(),
  });
  robot_socket_->send(robot_command.SerializeAsString());

  // ilog("Message sent");
}

void MessageSender::send(const tp::RobotControl& robot_control) {
  ilog("sending...robot_control {}", robot_control.DebugString());

  communication_socket_->send({
      service_discovery::kCommunicationCommandTopic,
      robot_control.SerializeAsString(),
  });
  simm_socket_->send(robot_control.SerializeAsString());

  // ilog("Message sent");
}

} // namespace communication
