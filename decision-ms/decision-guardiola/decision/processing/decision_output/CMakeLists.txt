robocin_cpp_library(
    NAME decision_output
    HDRS mappers/decision_output_mapper.h
    SRCS mappers/decision_output_mapper.cpp
    DEPS common::output
         protocols::protobufs
)
