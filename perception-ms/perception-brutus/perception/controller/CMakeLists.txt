robocin_cpp_library(
  NAME controller
  HDRS icontroller.h
       producer_controller.h
       consumer_controller.h
  SRCS icontroller.cpp
       producer_controller.cpp
       consumer_controller.cpp
  DEPS common::parameters
       common::concurrency
       common::memory
       common::output
       messaging_receiver
       messaging_sender
       processing
)
