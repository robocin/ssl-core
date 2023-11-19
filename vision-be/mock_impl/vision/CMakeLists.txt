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
)
