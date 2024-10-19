robocin_cpp_library(
  NAME controller
  HDRS icontroller.h
       consumer_controller.h
       producer_controller.h
  SRCS icontroller.cpp
       consumer_controller.cpp
       producer_controller.cpp
  DEPS common::parameters
       common::concurrency
       common::memory
       common::output
       messaging_receiver
)
