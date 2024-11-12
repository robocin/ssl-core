robocin_cpp_library(
  NAME motion_parser
  HDRS motion_parser.h
  SRCS motion_parser.cpp
  DEPS protocols::protobufs
       parameters
       angular
       common::geometry
       navigation_utils
       navigation_entities
       common::utility
       messages
)
