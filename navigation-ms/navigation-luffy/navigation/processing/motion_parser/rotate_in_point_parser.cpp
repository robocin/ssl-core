#include "navigation/processing/motion_parser/rotate_in_point_parser.h"

#include <protocols/navigation/motion.pb.h>

namespace navigation {

RobotMove RotateInPointParser::parse(const ::protocols::navigation::Navigation& navigation) {
  if (navigation.motion_case() != ::protocols::navigation::Navigation::kRotateInPoint) {
    return RobotMove{};
  }

  const ::protocols::navigation::RotateInPoint& rotateInPoint = navigation.rotate_in_point();

  RobotMove move;
  // PROCESSAMENTO DO ROTATEINPOINT
  return move;
}

} // namespace navigation
