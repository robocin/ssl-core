#include "navigation/processing/motion_parser/go_to_point_parser.h"

#include <protocols/navigation/motion.pb.h>

namespace navigation {

RobotMove GoToPointParser::parse(const ::protocols::navigation::Navigation& navigation) {
  if (navigation.motion_case() != ::protocols::navigation::Navigation::kGoToPoint) {
    return RobotMove{};
  }

  const ::protocols::navigation::GoToPoint& goToPoint = navigation.go_to_point();

  RobotMove move;
  // PROCESSAMENTO DO GOTOPOINT
  return move;
}

} // namespace navigation
