#ifndef NAVIGATION_PROCESSING_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_MOTION_PARSER_H

#include <navigation/processing/utils/robot_move.h>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/perception/detection.pb.h>

namespace navigation {

class IMotionParser {
 public:
  IMotionParser() = default;

  IMotionParser(const IMotionParser& other) = delete;
  IMotionParser& operator=(const IMotionParser& other) = delete;
  IMotionParser(IMotionParser&& other) = default;
  IMotionParser& operator=(IMotionParser&& other) = default;

  virtual ~IMotionParser() = default;

  virtual RobotMove parse(const ::protocols::behavior::unification::Motion& motion,
                          const ::protocols::perception::Robot& robot) = 0;
  virtual RobotMove parse(const ::protocols::navigation::GoToPoint& go_to_point,
                          const ::protocols::perception::Robot& robot) = 0;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOTION_PARSER_H
