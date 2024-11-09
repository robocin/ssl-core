robocin_cpp_library(
  NAME navigation_entities
  HDRS robot_move.h
       world.h
  SRCS robot_move.cpp
       world.cpp
  DEPS common::geometry 
       protocols::protobufs
)
