#include "navigation/processing/motion_parser/rotate_on_self_parser.h"

#include <protocols/navigation/motion.pb.h>

namespace navigation {

RobotMove RotateOnSelfParser::parse(const ::protocols::navigation::Navigation& navigation) {
  if (navigation.motion_case() != ::protocols::navigation::Navigation::kRotateOnSelf) {
    return RobotMove{};
  }

  const ::protocols::navigation::RotateOnSelf& rotateOnSelf = navigation.rotate_on_self();

  RobotMove move;
  // PROCESSAMENTO DO ROTATEONSELF
  return move;
}

} // namespace navigation
