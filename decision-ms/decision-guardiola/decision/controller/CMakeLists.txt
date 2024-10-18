robocin_cpp_library(
  NAME controller
  HDRS icontroller.h
       producer_controller.h
  SRCS icontroller.cpp
       producer_controller.cpp
  DEPS common::concurrency
       common::memory
       common::output
       common::detection_util
       common::parameters
       messaging_receiver
)
