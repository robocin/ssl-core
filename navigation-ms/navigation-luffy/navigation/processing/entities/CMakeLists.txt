robocin_cpp_library(
  NAME navigation_entities
  HDRS robot_move.h
       ally.h
       world.h
       move_state.h
  SRCS robot_move.cpp
       ally.cpp
       world.cpp
       move_state.cpp
  DEPS common::geometry 
       protocols::protobufs
)
