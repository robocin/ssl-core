robocin_cpp_library(
  NAME processing
  HDRS navigation_processor.h
  SRCS navigation_processor.cpp
  DEPS navigation_entities
       navigation_utils
       motion_parser
       messages
)
