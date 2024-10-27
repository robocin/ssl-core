#include "communication/processing/messages/communication/communication_message.h"

namespace communication {

CommandMessage::CommandMessage(MessageTypeMessage message_type,
                               RobotIdMessage robot_id,
                               RobotVelocityMessage robot_velocity,
                               RobotKickMessage robot_kick,
                               RobotDribblerMessage robot_dribbler,
                               FlagsMessage robot_flags) :
    message_type(std::move(message_type)),
    robot_id(std::move(robot_id)),
    robot_velocity(std::move(robot_velocity)),
    robot_kick(std::move(robot_kick)),
    robot_dribbler(std::move(robot_dribbler)),
    robot_flags(std::move(robot_flags)) {}

OutputMessage::OutputMessage(CommandMessage command) : command(std::move(command)) {}

CommunicationMessage::CommunicationMessage(std::vector<OutputMessage> output_message) :
    output_messages(std::move(output_message)) {}

} // namespace communication
