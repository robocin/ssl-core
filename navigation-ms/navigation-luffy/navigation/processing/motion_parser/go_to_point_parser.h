#ifndef NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
#define NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H

#include "IMotionParser.h"

namespace navigation {

class GoToPointParser : public IMotionParser<::protocols::navigation::GoToPoint> {
 public:
  explicit GoToPointParser(std::any world);
<<<<<<< HEAD
  RobotMove parse(const ::protocols::navigation::GoToPoint& motion) override;
=======
  RobotMove parse(const ::protocols::navigation::GoToPoint& go_to_point) override;
>>>>>>> origin/feat/navigation_processor

 private:
  std::any world_;
  //   std::optional<::protocols::perception::Detection> last_detection_;
  //   std::unique_ptr<ICameraFilter::Factory> camera_filter_factory_;
  //   // TODO(joseviccruz): replace by absl::flat_hash_map
  //   std::unordered_map<int, std::unique_ptr<ICameraFilter>> camera_filters_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
