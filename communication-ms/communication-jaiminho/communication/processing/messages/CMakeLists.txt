robocin_cpp_library(
    NAME messages
    HDRS communication/communication_message.h
         common/robot_id/robot_id.h
         common/robot_velocity/robot_velocity.h
         common/robot_kick/robot_kick.h
         common/robot_dribbler/robot_dribbler.h
         common/message_type/message_type.h
         flags/flags.h
    SRCS communication/communication_message.cpp
         common/robot_id/robot_id.cpp
         common/robot_velocity/robot_velocity.cpp
         common/robot_kick/robot_kick.cpp
         common/robot_dribbler/robot_dribbler.cpp
         common/message_type/message_type.cpp
         flags/flags.cpp
    DEPS common::utility
         common::output
         common::geometry
)
