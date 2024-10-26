robocin_cpp_library(
     NAME messages
     HDRS iproto_convertible.h
          behavior/behavior_message.h
          common/peripheral_actuation/peripheral_actuation.h
          common/robot_id/robot_id.h
          common/robot_kick/kick_command.h
          decision/decision_message.h
          motion/motion_message.h
          planning/planning_message.h
          perception/robot/robot_message.h
          perception/ball/ball_message.h
          perception/field/field_message.h
     SRCS iproto_convertible.cpp
          iproto_convertible.cpp
          behavior/behavior_message.cpp
          common/peripheral_actuation/peripheral_actuation.cpp
          common/robot_id/robot_id.cpp
          common/robot_kick/kick_command.cpp
          decision/decision_message.cpp
          motion/motion_message.cpp
          planning/planning_message.cpp
          perception/robot/robot_message.cpp
          perception/ball/ball_message.cpp
          perception/field/field_message.cpp
     DEPS common::output
          protocols::protobufs
)
