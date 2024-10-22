#include "rotate_in_point_parser.h"

#include <protocols/behavior/motion.pb.h>

namespace navigation {

RobotMove RotateInPointParser::parse(const ::protocols::behavior::RotateInPoint& motion,
                                     ::protocols::referee::GameStatus& game_status,
                                     ::protocols::perception::Detection& detection) {
  RobotMove move(0);
  // PROCESSAMENTO DO ROTATEINPOINT
  return move;
}

} // namespace navigation
