robocin_cpp_library(
  NAME navigation_entities
  HDRS robot_move.h
       world.h
       move_state.h
  SRCS robot_move.cpp
       world.cpp
       move_state.cpp
  DEPS common::geometry 
       protocols::protobufs
)
