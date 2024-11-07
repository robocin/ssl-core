robocin_cpp_library(
  NAME analyzers
  HDRS field_analyzer.h
       ball_analyzer.h
  SRCS field_analyzer.cpp
       ball_analyzer.cpp
  DEPS common::geometry
)
