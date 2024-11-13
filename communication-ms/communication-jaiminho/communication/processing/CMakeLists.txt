robocin_cpp_library(
  NAME processing
  HDRS communication_processor.h
  SRCS communication_processor.cpp
  DEPS messages
       protocols::protobufs
)
