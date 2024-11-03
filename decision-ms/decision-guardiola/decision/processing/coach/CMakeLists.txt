robocin_cpp_library(
  NAME coach
  HDRS icoach.h
       coach.h
       tactical_plan/tactical_plan.h
  SRCS icoach.cpp
       coach.cpp
       tactical_plan/tactical_plan.cpp
  DEPS evaluators
)
