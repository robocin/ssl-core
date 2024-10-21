#ifndef NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
#define NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H

#include <navigation/processing/motion_parser/motion_parser.h>

namespace navigation {

class GoToPointParser : public IMotionParser {
 public:
  GoToPointParser();

  RobotMove parse(const ::protocols::behavior::unification::Motion& motion,
                  const ::protocols::perception::Robot& robot) override;

  RobotMove parse(const ::protocols::behavior::GoToPoint& go_to_point,
                  const ::protocols::perception::Robot& robot) override;

 private:
  //   std::optional<::protocols::perception::Detection> last_detection_;
  //   std::unique_ptr<ICameraFilter::Factory> camera_filter_factory_;
  //   // TODO(joseviccruz): replace by absl::flat_hash_map
  //   std::unordered_map<int, std::unique_ptr<ICameraFilter>> camera_filters_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
