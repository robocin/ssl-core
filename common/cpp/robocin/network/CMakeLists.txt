robocin_cpp_library(
  NAME network
  HDRS udp_multicast_socket_receiver.h
        zmq_datagram.h
        zmq_subscriber_socket.h
        zmq_publisher_socket.h
        zmq_poller.h
  SRCS udp_multicast_socket_receiver.cpp
        zmq_datagram.cpp
        zmq_subscriber_socket.cpp
        zmq_publisher_socket.cpp
        zmq_poller.cpp
  DEPS cppzmq-static
)

robocin_cpp_test(
  NAME zmq_datagram_test
  SRCS zmq_datagram_test.cpp
  DEPS network
)

robocin_cpp_test(
  NAME zmq_publisher_socket_test
  SRCS zmq_publisher_socket_test.cpp
  DEPS network
)

robocin_cpp_test(
  NAME zmq_subscriber_socket_test
  SRCS zmq_subscriber_socket_test.cpp
  DEPS network
)
