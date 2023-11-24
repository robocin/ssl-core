#include "robocin/common/concepts.h"

#include <string>

namespace robocin {

// The MulticastUdpReceiverSocket class provides functionality for creating and managing UDP sockets
// with multicast capabilities. It supports both sending and receiving multicast messages.
class MulticastUdpReceiverSocket {
 public:
  MulticastUdpReceiverSocket() noexcept(false);

  MulticastUdpReceiverSocket(const MulticastUdpReceiverSocket&) = default;
  MulticastUdpReceiverSocket& operator=(const MulticastUdpReceiverSocket&) = default;

  MulticastUdpReceiverSocket(MulticastUdpReceiverSocket&&) = default;
  MulticastUdpReceiverSocket& operator=(MulticastUdpReceiverSocket&&) = default;

  ~MulticastUdpReceiverSocket() noexcept;

  void bind(const std::string& ip_address, int port, const std::string& network_interface) const
      noexcept(false);

  // Always returns true.
  [[nodiscard]] bool receive(std::string& buffer, std::size_t buffer_size = 2048) const;

  [[nodiscard]] bool receive(std::string& buffer, //
                             int64_t timeout_ms,  //
                             std::size_t buffer_size = 2048) const;

  // Always returns true.
  template <protobuf Pb>
  bool receive(Pb& proto, std::size_t buffer_size = 2048) const {
    if (std::string str_result; receive(str_result, buffer_size)) {
      proto.ParseFromString(str_result);
      return true;
    }
    return false;
  }

  template <protobuf Pb>
  bool receive(Pb& proto, int64_t timeout_ms, std::size_t buffer_size = 2048) const {
    if (std::string str_result; receive(str_result, timeout_ms, buffer_size)) {
      proto.ParseFromString(str_result);
      return true;
    }
    return false;
  }

 private:
  // A socket file descriptor (socket_fd) is an integer identifier that the operating system
  // assigns to a socket when it is created. The socket file descriptor is used by the
  // application to refer to the socket in subsequent operations, such as reading from or
  // writing to the socket.
  //
  // The socket system call returns a file descriptor that is used for all subsequent operations
  // on that socket, such as binding, sending, receiving, etc. It's important to note that the
  // socket file descriptor is specific to the process in which it is created. If you fork a new
  // process, the child process will have a separate copy of the file descriptor. Proper
  // management of file descriptors is crucial in network programming to avoid resource leaks
  // and unexpected behavior.
  int socket_fd_;
};

} // namespace robocin
