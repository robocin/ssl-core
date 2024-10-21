robocin_cpp_library(
  NAME motion_parser
  HDRS IMotionParser.h
       go_to_point_parser.h
       rotate_in_point_parser.h
       rotate_on_self_parser.h
  SRCS go_to_point_parser.cpp
       rotate_in_point_parser.cpp
       rotate_on_self_parser.cpp
  DEPS parameters protocols::protobufs geometry navigation_utils
)
