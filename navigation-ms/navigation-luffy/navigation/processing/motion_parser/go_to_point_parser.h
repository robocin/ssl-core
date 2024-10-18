#ifndef NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
#define NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H

#include <navigation/processing/motion_parser/motion_parser.h>

namespace navigation {

class GoToPointParser : public IMotionParser {
 public:
  RobotMove parse(const ::protocols::navigation::Navigation& navigation) override;

 private:
  //   std::optional<::protocols::perception::Detection> last_detection_;
  //   std::unique_ptr<ICameraFilter::Factory> camera_filter_factory_;
  //   // TODO(joseviccruz): replace by absl::flat_hash_map
  //   std::unordered_map<int, std::unique_ptr<ICameraFilter>> camera_filters_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
