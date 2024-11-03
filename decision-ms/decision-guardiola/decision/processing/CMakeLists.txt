robocin_cpp_library(
    NAME processing
    HDRS decision_processor.h
    SRCS decision_processor.cpp
    DEPS common::output
         messages
         role_manager
         entities
         coach
)
