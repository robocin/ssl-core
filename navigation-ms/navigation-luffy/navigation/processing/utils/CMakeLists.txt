robocin_cpp_library(
  NAME navigation_utils
  HDRS move_task_state.h
       robot_move.h
  SRCS move_task_state.h
       robot_move.cpp
  DEPS protocols::protobufs common::detection_util parameters geometry
)
