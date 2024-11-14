robocin_cpp_library(
    NAME state_machine
    HDRS istate_machine.h
         goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.h
         goalkeeper_take_ball_away/states/go_to_ball_gk.h
         goalkeeper_take_ball_away/states/go_to_safe_position.h
         goalkeeper_take_ball_away/states/kick_ball_gk.h
         goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.h
         goalkeeper_guard/goalkeeper_guard_state_machine.h
         goalkeeper_guard/states/defend_kick.h
         goalkeeper_guard/states/follow_ball_line.h
         goalkeeper_guard/states/follow_enemy_line.h
         goalkeeper_guard/common/goalkeeper_guard_common.h
         forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.h
         forward_follow_and_kick_ball/states/align.h
         forward_follow_and_kick_ball/states/go_to_ball.h
         forward_follow_and_kick_ball/states/kick_ball.h
         forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.h

    SRCS istate_machine.cpp
         goalkeeper_take_ball_away/goalkeeper_take_ball_away_state_machine.cpp
         goalkeeper_take_ball_away/states/go_to_ball_gk.cpp
         goalkeeper_take_ball_away/states/go_to_safe_position.cpp
         goalkeeper_take_ball_away/states/kick_ball_gk.cpp
         goalkeeper_take_ball_away/common/goalkeeper_take_ball_away_common.cpp
         goalkeeper_guard/goalkeeper_guard_state_machine.cpp
         goalkeeper_guard/states/defend_kick.cpp
         goalkeeper_guard/states/follow_ball_line.cpp
         goalkeeper_guard/states/follow_enemy_line.cpp
         goalkeeper_guard/common/goalkeeper_guard_common.cpp
         forward_follow_and_kick_ball/forward_follow_and_kick_ball_state_machine.cpp
         forward_follow_and_kick_ball/states/align.cpp
         forward_follow_and_kick_ball/states/go_to_ball.cpp
         forward_follow_and_kick_ball/states/kick_ball.cpp
         forward_follow_and_kick_ball/common/forward_follow_and_kick_ball_common.cpp
    DEPS common::output               
         messages
         analyzers
)
