#ifndef COMMUNICATION_MESSAGING_SENDER_MESSAGE_SENDER_H
#define COMMUNICATION_MESSAGING_SENDER_MESSAGE_SENDER_H

#include "robocin/network/udp_multicast_socket_sender.h"
#include "robocin/network/zmq_publisher_socket.h"

#include <protocols/communication/communication.pb.h>
#include <protocols/third_party/simulation/robot_control.pb.h>

namespace communication {

class IMessageSender {
 public:
  IMessageSender() = default;

  IMessageSender(const IMessageSender&) = delete;
  IMessageSender& operator=(const IMessageSender&) = delete;
  IMessageSender(IMessageSender&&) = default;
  IMessageSender& operator=(IMessageSender&&) = default;

  virtual ~IMessageSender() = default;

  virtual void send(const ::protocols::communication::Communication& robot_command) = 0;
  virtual void send(const ::protocols::third_party::simulation::RobotControl& robot_control) = 0;
};

class MessageSender : public IMessageSender {
 public:
  explicit MessageSender(std::unique_ptr<::robocin::IZmqPublisherSocket> communication_socket,
                         std::unique_ptr<::robocin::IUdpMulticastSocketSender> robot_socket,
                         std::unique_ptr<::robocin::IUdpMulticastSocketSender> simm_socket);

  void send(const ::protocols::communication::Communication& robot_command) override;
  void send(const ::protocols::third_party::simulation::RobotControl& robot_control) override;

 private:
  std::unique_ptr<::robocin::IZmqPublisherSocket> communication_socket_;
  std::unique_ptr<::robocin::IUdpMulticastSocketSender> robot_socket_;
  std::unique_ptr<::robocin::IUdpMulticastSocketSender> simm_socket_;
};

} // namespace communication

#endif // COMMUNICATION_MESSAGING_SENDER_MESSAGE_SENDER_H
