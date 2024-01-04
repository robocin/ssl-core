#include "protocols/third_party/detection/raw_wrapper.pb.h"
#include "vision/network/socket.h"
#include "vision/network/udp_multicast_socket_receiver.h"

#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <iostream>
#include <memory>
#include <string>

using protocols::third_party::detection::SSL_WrapperPacket;
using vision::ISocketReceiver;
using vision::UdpMulticastSocketReceiver;

int main() {
  std::unique_ptr<ISocketReceiver> udp_socket
      = std::make_unique<UdpMulticastSocketReceiver>("224.5.23.2", "192.168.18.5", /*port=*/10020);

  while (true) {
    std::string message = udp_socket->receive();
    SSL_WrapperPacket packet;
    packet.ParseFromString(message);

    std::cout << "Received message: " << packet.DebugString() << '\n';

    absl::SleepFor(absl::Seconds(1));
  }
  return 0;
}
