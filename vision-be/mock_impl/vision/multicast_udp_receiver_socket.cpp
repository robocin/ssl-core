#include "vision/multicast_udp_receiver_socket.h"

#include "vision/network_interface_utility.h"

#include <arpa/inet.h>
#include <format>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <system_error>
#include <unistd.h>

namespace robocin {

namespace {

constexpr int64_t kMillisecondsPerSecond = 1000;
constexpr int64_t kMicrosecondsPerMillisecond = 1000;

} // namespace

MulticastUdpReceiverSocket::MulticastUdpReceiverSocket() noexcept(false) :
    socket_fd_{socket(AF_INET, SOCK_DGRAM, 0)} {
  if (socket_fd_ == -1) {
    throw std::system_error(errno, std::system_category(), "error creating socket.");
  }
}

MulticastUdpReceiverSocket::~MulticastUdpReceiverSocket() noexcept { ::close(socket_fd_); }

void MulticastUdpReceiverSocket::bind(const std::string& ip_address,
                                      int port,
                                      const std::string& network_interface) const noexcept(false) {

  std::string iface_address = network_interface_utility::address_from(network_interface);
  if (iface_address.empty()) {
    throw std::invalid_argument(std::format("invalid network interface: '{}'.", network_interface));
  }

  int reuse = 1; // setting SO_REUSEADDR to true.
  if (::setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    throw std::system_error(errno, std::system_category(), "setsockopt");
  }

  if (sockaddr_in addr{
          .sin_family = AF_INET,
          .sin_port = ::htons(port),
          .sin_addr = {.s_addr = inet_addr(ip_address.c_str())},
      };
      ::bind(socket_fd_,
             reinterpret_cast<sockaddr*>(&addr), // NOLINT(*reinterpret-cast*)
             sizeof(addr))
      == -1) {
    throw std::system_error(errno, std::system_category(), "bind");
  }

  if (ip_mreqn membership{
          .imr_multiaddr = {.s_addr = inet_addr(ip_address.data())},
          .imr_address = {.s_addr = inet_addr(iface_address.data())},
      };
      ::setsockopt(socket_fd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &membership, sizeof(membership))
      == -1) {
    throw std::system_error(errno, std::system_category(), "setsockopt");
  }
}

bool MulticastUdpReceiverSocket::receive(std::string& buffer, std::size_t buffer_size) const {
  buffer.assign(buffer_size, '\0');
  ::ssize_t bytes_received = ::recv(socket_fd_, buffer.data(), buffer_size, 0);

  if (bytes_received == -1) {
    throw std::system_error(errno, std::system_category(), "recv");
  }

  buffer.resize(static_cast<std::size_t>(bytes_received));
  return true;
}

bool MulticastUdpReceiverSocket::receive(std::string& buffer,
                                         int64_t timeout_ms,
                                         std::size_t buffer_size = 2048) const {
  ::fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(socket_fd_, &read_fds);

  ::timeval timeout = {
      timeout.tv_sec = timeout_ms / kMillisecondsPerSecond,
      timeout.tv_usec = (timeout_ms % kMicrosecondsPerMillisecond) * kMicrosecondsPerMillisecond,
  };

  int ready = ::select(socket_fd_ + 1, &read_fds, nullptr, nullptr, &timeout);

  if (ready == -1) {
    throw std::system_error(errno, std::system_category(), "select");
  }
  if (ready == 0) {
    return false;
  }

  return receive(buffer, buffer_size);
}

} // namespace robocin
