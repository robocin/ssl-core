robocin_cpp_library(
    NAME processing
    HDRS decision_processor.h
    SRCS decision_processor.cpp
    DEPS common::output
         coach
         role_manager
         evaluators
         analyzers
         messages
         entities
)
