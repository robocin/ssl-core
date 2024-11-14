robocin_cpp_library(
  NAME analyzers
  HDRS field_analyzer.h
       ball_analyzer.h
       ally_analyzer.h
       enemy_analyzer.h
  SRCS field_analyzer.cpp
       ball_analyzer.cpp
       ally_analyzer.cpp
       enemy_analyzer.cpp
  DEPS common::geometry
       messages
       common::utility
)
