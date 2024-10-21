robocin_cpp_library(
  NAME IMotionParser
  HDRS IMotionParser.h
       go_to_point_parser.h
       rotate_in_point_parser.h
       rotate_on_self_parser.h
  SRCS go_to_point_parser.cpp
       rotate_in_point_parser.cpp
       rotate_on_self_parser.cpp
)