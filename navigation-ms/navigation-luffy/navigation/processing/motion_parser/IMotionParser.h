#ifndef NAVIGATION_PROCESSING_I_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_I_MOTION_PARSER_H

#include <type_traits>
#include <concepts>
#include <optional>
#include "../utils/robot_move.h"
#include <protocols/navigation/navigation.pb.h>
#include <protocols/navigation/motion.pb.h>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/perception/detection.pb.h>
#include <protocols/referee/game_status.pb.h>

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

    virtual RobotMove parse(const T& motion, 
                            ::protocols::referee::GameStatus& game_status, 
                            ::protocols::perception::Detection& detection) = 0;
  private:
    // std::optional<T> motion_ = {};
    // std::optional<::protocols::referee::GameStatus> game_status_ = {};
    // std::optional<::protocols::perception::Detection> detection_ = {};
    // std::optional<::protocols::perception::Robot> ally_ = {};

};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_I_MOTION_PARSER_H
