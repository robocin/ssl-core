#ifndef NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
#define NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H

#include "IMotionParser.h"

#include <protocols/navigation/motion.pb>
#include <utility>

namespace navigation {

namespace rc {
using ::protocols::navigation::MovingProfile;
}
class GoToPointParser : public IMotionParser<::protocols::navigation::GoToPoint> {
 public:
  GoToPointParser() = default;

  RobotMove parse(const ::protocols::navigation::GoToPoint& motion,
                  ::protocols::referee::GameStatus& game_status,
                  ::protocols::perception::Detection& detection) override;

 private:
  ::protocols::perception::Robot matchAlly(::protocols::navigation::GoToPoint& motion,
                                           ::protocols::referee::GameStatus& game_status,
                                           ::protocols::perception::Detection& detection);

  inline static std::pair<double, double> minAndMaxVelocityToProfile(rc::MovingProfile& profile);

  inline static double propDistanceToProfile(rc::MovingProfile& profile);

  //   std::optional<::protocols::perception::Detection> last_detection_;
  //   std::unique_ptr<ICameraFilter::Factory> camera_filter_factory_;
  //   // TODO(joseviccruz): replace by absl::flat_hash_map
  //   std::unordered_map<int, std::unique_ptr<ICameraFilter>> camera_filters_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
