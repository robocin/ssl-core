robocin_cpp_library(
    NAME network_interface_utility
    HDRS network_interface_utility.h
    SRCS network_interface_utility.cpp
)

robocin_cpp_library(
    NAME multicast_udp_receiver_socket
    HDRS multicast_udp_receiver_socket.h
    SRCS multicast_udp_receiver_socket.cpp
    DEPS common::concepts
         network_interface_utility
)

robocin_cpp_executable(
    NAME vision
    SRCS vision_main.cpp
    DEPS absl::time
         absl::synchronization
         absl::random_random
         absl::strings
         common::utility
         common::zmq_publish_subscribe
         protobuf::libprotobuf
         network_interface_utility
         multicast_udp_receiver_socket
)

robocin_cpp_executable(
    NAME bst
    SRCS bst_main.cpp
)
