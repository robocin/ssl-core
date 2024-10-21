#include "rotate_on_self_parser.h"

#include <protocols/navigation/motion.pb.h>

namespace navigation {

RobotMove RotateOnSelfParser::parse(::protocols::navigation::RotateOnSelf& motion, 
                                    ::protocols::referee::GameStatus& game_status, 
                                    ::protocols::perception::Detection& detection) {
  RobotMove move;
  // PROCESSAMENTO DO ROTATEONSELF
  return move;
}

} // namespace navigation
