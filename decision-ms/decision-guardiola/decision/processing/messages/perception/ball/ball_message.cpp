#include "decision/processing/messages/perception/ball/ball_message.h"

namespace decision {

KickInformationMessage::KickInformationMessage(
    std::optional<RobotIdMessage> robot_id,
    std::optional<robocin::Point2Df> start_position,
    std::optional<robocin::Point3Df> start_velocity,
    std::optional<uint32_t> start_timestamp,
    std::optional<robocin::Point2Df> predicted_stop_position,
    std::optional<uint32_t> predicted_stop_timestamp) :
    robot_id(std::move(robot_id)),
    start_position(start_position),
    start_velocity(start_velocity),
    start_timestamp(start_timestamp),
    predicted_stop_position(predicted_stop_position),
    predicted_stop_timestamp(predicted_stop_timestamp) {}

BallMessage::BallMessage(std::optional<float> confidence,
                         std::optional<robocin::Point3Df> position,
                         std::optional<robocin::Point3Df> velocity,
                         std::optional<KickInformationMessage> kick_information) :
    confidence(confidence),
    position(position),
    velocity(velocity),
    kick_information(std::move(kick_information)) {}
} // namespace decision
