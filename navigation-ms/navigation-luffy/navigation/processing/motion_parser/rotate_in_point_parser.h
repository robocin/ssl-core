#ifndef NAVIGATION_PROCESSING_ROTATE_IN_POINT_PARSER_H
#define NAVIGATION_PROCESSING_ROTATE_IN_POINT_PARSER_H

#include "../IMotionParser.h"

namespace navigation {

class RotateInPointParser : public IMotionParser<::protocols::navigation::RotateInPoint> {
 public:
  RobotMove parse(const ::protocols::navigation::RotateInPoint& motion,
                  ::protocols::referee::GameStatus& game_status,
                  ::protocols::perception::Detection& detection) override;

 private:
  //   std::optional<::protocols::perception::Detection> last_detection_;
  //   std::unique_ptr<ICameraFilter::Factory> camera_filter_factory_;
  //   // TODO(joseviccruz): replace by absl::flat_hash_map
  //   std::unordered_map<int, std::unique_ptr<ICameraFilter>> camera_filters_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_ROTATE_IN_POINT_PARSER_H
