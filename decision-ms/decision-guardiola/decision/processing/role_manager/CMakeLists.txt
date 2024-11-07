robocin_cpp_library(
  NAME role_manager
  HDRS role_manager.h
       roles/goalkeeper.h
       roles/irole.h
  SRCS role_manager.cpp
       roles/goalkeeper.cpp
       roles/irole.cpp
  DEPS common::output
)
