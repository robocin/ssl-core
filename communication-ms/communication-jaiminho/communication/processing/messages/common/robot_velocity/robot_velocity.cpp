#include "communication/processing/messages/common/robot_velocity/robot_velocity.h"

namespace communication {

RobotVelocityMessage::RobotVelocityMessage(std::optional<robocin::Point2D<float>> velocity,
                                           std::optional<float> angular_velocity) :
    velocity{std::move(velocity)},
    angular_velocity{std::move(angular_velocity)} {}

} // namespace communication
