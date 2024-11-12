robocin_cpp_library(
    NAME impl
    HDRS impl.h
    SRCS impl.cpp
    DEPS common::utility
         common::output
         common::geometry
         protocols::protobufs
)
