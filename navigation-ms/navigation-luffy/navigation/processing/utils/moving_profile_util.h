#ifndef NAVIGATION_PROCESSING_MOVING_PROFILE_UTIL_H
#define NAVIGATION_PROCESSING_MOVING_PROFILE_UTIL_H

#include "navigation/processing/messages/motion/motion_message.h"

#include <navigation/parameters/parameters.h>
#include <protocols/behavior/motion.pb.h>
#include <utility>

namespace navigation {

class MovingProfileUtil {

 public:
  static std::pair<double, double>
  minAndMaxVelocityToProfile(GoToPointMessage::MovingProfile profile);

  static double propDistanceToProfile(GoToPointMessage::MovingProfile profile);
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOVING_PROFILE_UTIL_H
