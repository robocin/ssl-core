#ifndef NAVIGATION_PROCESSING_I_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_I_MOTION_PARSER_H

#include <algorithm>
#include <any>
#include <navigation/processing/utils/robot_move.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/navigation/motion.pb.h>
#include <type_traits>

namespace navigation {

template<typename T>
concept MotionType = std::is_same_v<T, ::protocols::navigation::GoToPoint> 
                    || std::is_same_v<T, ::protocols::navigation::RotateInPoint> 
                    || std::is_same_v<T, ::protocols::navigation::RotateOnSelf>;

template<MotionType T>
class IMotionParser {
  public:
    IMotionParser() = default;

    IMotionParser(const IMotionParser& other) = delete;
    IMotionParser& operator=(const IMotionParser& other) = delete;
    IMotionParser(IMotionParser&& other) = default;
    IMotionParser& operator=(IMotionParser&& other) = default;

    virtual ~IMotionParser() = default;

    virtual RobotMove parse(const T& motion) = 0;
  private:
    std::any world_;

};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_I_MOTION_PARSER_H
