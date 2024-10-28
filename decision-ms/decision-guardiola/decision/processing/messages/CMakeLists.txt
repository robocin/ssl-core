robocin_cpp_library(
     NAME messages
     HDRS iproto_convertible.h
          behavior/behavior_message.h
          common/peripheral_actuation/peripheral_actuation.h
          common/robot_id/robot_id_message.h
          common/robot_kick/kick_command.h
          common/game_command/game_command_message.h
          common/game_event/game_event_message.h
          decision/decision_message.h
          motion/motion_message.h
          planning/planning_message.h
          perception/robot/robot_message.h
          perception/ball/ball_message.h
          perception/field/field_message.h
          perception/detection/detection_message.h
          referee/game_status_message.h
     SRCS iproto_convertible.cpp
          iproto_convertible.cpp
          behavior/behavior_message.cpp
          common/peripheral_actuation/peripheral_actuation.cpp
          common/robot_id/robot_id_message.cpp
          common/robot_kick/kick_command.cpp
          common/game_command/game_command_message.cpp
          common/game_event/game_event_message.cpp
          decision/decision_message.cpp
          motion/motion_message.cpp
          planning/planning_message.cpp
          perception/robot/robot_message.cpp
          perception/ball/ball_message.cpp
          perception/field/field_message.cpp
          perception/detection/detection_message.cpp
          referee/game_status_message.cpp
     DEPS common::output
          protocols::protobufs
)
