#include "robocin/network/udp_multicast_socket_sender.h"

#if defined(__robocin_lib_arpa_inet) and __robocin_lib_arpa_inet >= 202405L

#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <type_traits>
#include <unistd.h>

namespace robocin {

UdpMulticastSocketSender::UdpMulticastSocketSender(size_t size) :
    fd_(socket(AF_INET, SOCK_DGRAM, 0)),
    size_(size) {
  if (fd_ == -1) {
    throw std::runtime_error("failed to create socket.");
  }
}

void UdpMulticastSocketSender::connect(std::string_view ip_address, int port) const {
  if (::setsockopt(fd_,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   &std::integral_constant<int, 1>::value,
                   sizeof(int))
      == -1) {
    throw std::runtime_error("failed to set SO_REUSEADDR.");
  }

  sockaddr_in udp_addr{};
  udp_addr.sin_family = AF_INET;
  udp_addr.sin_port = ::htons(port);
  udp_addr.sin_addr.s_addr = ::inet_addr(std::string{ip_address}.c_str());

  if (::connect(fd_, reinterpret_cast<sockaddr*>(&udp_addr), sizeof(udp_addr)) == -1) {
    throw std::runtime_error("failed to connect to multicast group.");
  }
}

void UdpMulticastSocketSender::send(const send_type& message) const {
  // Simulator uses this one
  uint32_t message_size = message.size();
  ssize_t bytes_sent = ::send(fd_, message.data(), message_size, 0);

  if (bytes_sent == message_size) {
    // Sent successfully
    return;
  }

  // Error occured
  int err = errno;
  const char* error_message = strerror(err);
  std::cout << "[" << bytes_sent << "]: " << error_message << "\n";
}

void UdpMulticastSocketSender::send(std::string_view message) const {
  // Simulator uses this one
  uint32_t message_size = message.size();
  ssize_t bytes_sent = ::send(fd_, message.data(), message_size, 0);

  if (bytes_sent == message_size) {
    // Sent successfully
    return;
  }

  // Error occured
  int err = errno;
  const char* error_message = strerror(err);
  std::cout << "[" << bytes_sent << "]: " << error_message << "\n";
}

int UdpMulticastSocketSender::fd() const { return fd_; }

void UdpMulticastSocketSender::close() const {
  if (::close(fd_) == -1) {
    throw std::runtime_error("failed to close socket.");
  }
}

} // namespace robocin

#endif
