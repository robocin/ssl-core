robocin_cpp_library(
    NAME state_machine
    HDRS istate_machine.h
         goalkeeper/goalkeeper_state_machine.h
         goalkeeper/states/guard.h
    SRCS istate_machine.cpp
         goalkeeper/goalkeeper_state_machine.cpp
         goalkeeper/states/guard.cpp
    DEPS common::output
)
