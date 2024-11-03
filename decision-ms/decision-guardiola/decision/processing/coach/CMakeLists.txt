robocin_cpp_library(
  NAME coach
  HDRS icoach.h
       coach.h
       tactical_plan/tactical_plan.h
       role_manager/role_manager.h
       role_manager/roles/goalkeeper.h
  SRCS icoach.cpp
       coach.cpp
       tactical_plan/tactical_plan.cpp
       role_manager/role_manager.cpp
       role_manager/roles/goalkeeper.cpp
  DEPS evaluators
)
