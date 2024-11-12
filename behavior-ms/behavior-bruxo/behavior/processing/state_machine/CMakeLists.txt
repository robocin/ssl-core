robocin_cpp_library(
    NAME state_machine
    HDRS istate_machine.h
         goalkeeper/goalkeeper_state_machine.h
         goalkeeper/states/guard.h
         goalkeeper/states/other.h
         goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h
         goalkeeper_take_ball_away/states/go_to_ball.h
         goalkeeper_take_ball_away/states/go_to_safe_position.h
         goalkeeper_take_ball_away/states/kick_ball.h
         goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h
         goalkeeper_guard/goalkeeper_guard_state_machine.h
         goalkeeper_guard/states/defend_kick.h
         goalkeeper_guard/states/follow_ball_line.h
         goalkeeper_guard/states/follow_enemy_line.h
         goalkeeper_guard/common/goalkeeper_guard_common.h
    SRCS istate_machine.cpp
         goalkeeper/goalkeeper_state_machine.cpp
         goalkeeper/states/guard.cpp
         goalkeeper/states/other.cpp
         goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.cpp
         goalkeeper_take_ball_away/states/go_to_ball.cpp
         goalkeeper_take_ball_away/states/go_to_safe_position.cpp
         goalkeeper_take_ball_away/states/kick_ball.cpp
         goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.cpp
         goalkeeper_guard/goalkeeper_guard_state_machine.cpp
         goalkeeper_guard/states/defend_kick.cpp
         goalkeeper_guard/states/follow_ball_line.cpp
         goalkeeper_guard/states/follow_enemy_line.cpp
         goalkeeper_guard/common/goalkeeper_guard_common.cpp
    DEPS common::output               
         messages
)
