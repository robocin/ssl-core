robocin_cpp_library(
    NAME parser
    HDRS parser.h
    SRCS parser.cpp
    DEPS common::memory protocols::protobufs
)

robocin_cpp_test(
    NAME parser_test
    SRCS parser_test.cpp
    DEPS parser
)
