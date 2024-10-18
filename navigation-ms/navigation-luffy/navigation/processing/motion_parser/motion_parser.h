#ifndef NAVIGATION_PROCESSING_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_MOTION_PARSER_H

#include <navigation/processing/utils/robot_move.h>
#include <protocols/navigation/navigation.pb.h>

namespace navigation {

class IMotionParser {
 public:
  IMotionParser() = default;

  IMotionParser(const IMotionParser& other) = delete;
  IMotionParser& operator=(const IMotionParser& other) = delete;
  IMotionParser(IMotionParser&& other) = default;
  IMotionParser& operator=(IMotionParser&& other) = default;

  virtual ~IMotionParser() = default;

  virtual RobotMove parse(const ::protocols::navigation::Navigation& navigation) = 0;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOTION_PARSER_H
