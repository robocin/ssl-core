#ifndef NAVIGATION_PROCESSING_ALLY_H
#define NAVIGATION_PROCESSING_ALLY_H

#include "navigation/processing/messages/perception/robot/robot_message.h"

namespace navigation {
/*!
@brief This class extends the RobotMessage class in order to gather other important data about the
robot throughout navigation and planning processing.
*/
class Ally : public RobotMessage {
 public:
  explicit Ally(RobotMessage robot = RobotMessage{});

  void update(RobotMessage& ally);

  // Ally will have planning dependencies
};

} // namespace navigation
#endif // NAVIGATION_PROCESSING_ALLY_H
