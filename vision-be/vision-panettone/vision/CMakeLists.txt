add_subdirectory(network)

robocin_cpp_executable(
  NAME vision_main
  SRCS vision_main.cpp
  DEPS cppzmq network absl::time protocols::third_party
)
