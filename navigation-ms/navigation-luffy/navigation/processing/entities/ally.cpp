// ally.cpp

#include "navigation/processing/entities/ally.h"

namespace navigation {

Ally::Ally(RobotMessage robot) : RobotMessage(std::move(robot)) {}

void Ally::update(RobotMessage& ally) {
  this->angle = ally.angle;
  this->angular_velocity = ally.angular_velocity;
  this->velocity = ally.velocity;
  this->position = ally.position;
  this->confidence = ally.confidence;
  this->feedback = std::move(ally.feedback);
}

} // namespace navigation
