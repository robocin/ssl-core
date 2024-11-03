robocin_cpp_library(
  NAME navigation_utils
  HDRS moving_profile_util.h
  SRCS moving_profile_util.cpp
  DEPS common::geometry 
       protocols::protobufs
       parameters
)
