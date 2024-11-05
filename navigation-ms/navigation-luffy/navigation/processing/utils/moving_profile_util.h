#ifndef NAVIGATION_PROCESSING_MOVING_PROFILE_UTIL_H
#define NAVIGATION_PROCESSING_MOVING_PROFILE_UTIL_H

#include <navigation/parameters/parameters.h>
#include <protocols/behavior/motion.pb.h>
#include <utility>

namespace navigation {

class MovingProfileUtil {

 public:
  static std::pair<double, double>
  minAndMaxVelocityToProfile(::protocols::behavior::MovingProfile profile);

  static double propDistanceToProfile(::protocols::behavior::MovingProfile profile);
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOVING_PROFILE_UTIL_H
