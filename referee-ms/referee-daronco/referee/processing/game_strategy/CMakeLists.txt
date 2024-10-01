robocin_cpp_library(
    NAME game_strategy_mapper
    HDRS game_strategy_mapper.h
    SRCS game_strategy_mapper.cpp
    DEPS common::memory protocols::protobufs
)

robocin_cpp_test(
    NAME game_strategy_mapper_test
    SRCS game_strategy_mapper_test.cpp
    DEPS game_strategy_mapper
)
