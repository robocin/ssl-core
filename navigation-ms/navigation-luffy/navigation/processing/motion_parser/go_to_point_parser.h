#ifndef NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
#define NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H

#include "IMotionParser.h"

namespace navigation {

class GoToPointParser : public IMotionParser<::protocols::navigation::GoToPoint> {
 public:
  explicit GoToPointParser(const ::protocols::navigation::GoToPoint& motion,
                          std::optional<::protocols::referee::GameStatus> game_status,
                          std::optional<::protocols::perception::Detection> detection);
                          
  RobotMove parse(const ::protocols::navigation::GoToPoint& motion, 
                  ::protocols::referee::GameStatus& game_status, 
                  ::protocols::perception::Detection& detection) override;

 private:
  std::optional<::protocols::navigation::GoToPoint> motion_;
  std::optional<::protocols::referee::GameStatus> game_status_;
  std::optional<::protocols::perception::Detection> detection_;
  std::optional<::protocols::perception::Robot> ally_;
  //   std::optional<::protocols::perception::Detection> last_detection_;
  //   std::unique_ptr<ICameraFilter::Factory> camera_filter_factory_;
  //   // TODO(joseviccruz): replace by absl::flat_hash_map
  //   std::unordered_map<int, std::unique_ptr<ICameraFilter>> camera_filters_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_GO_TO_POINT_PARSER_H
