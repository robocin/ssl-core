robocin_cpp_library(
    NAME messages
    HDRS communication/communication_message.h
         flags/flags.h
    SRCS communication/communication_message.cpp
         flags/flags.cpp
    DEPS common::utility
         common::output
         common::geometry
)
