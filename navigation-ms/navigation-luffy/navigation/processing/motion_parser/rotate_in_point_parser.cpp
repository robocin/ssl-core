#include "navigation/processing/motion_parser/rotate_in_point_parser.h"

#include <protocols/navigation/motion.pb.h>

namespace navigation {

RobotMove RotateInPointParser::parse(::protocols::navigation::RotateInPoint& motion, 
                  ::protocols::referee::GameStatus& game_status, 
                  ::protocols::perception::Detection& detection) {
  RobotMove move;
  // PROCESSAMENTO DO ROTATEINPOINT
  return move;
}

} // namespace navigation
