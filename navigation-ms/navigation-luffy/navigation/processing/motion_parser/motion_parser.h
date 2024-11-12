#ifndef NAVIGATION_PROCESSING_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_MOTION_PARSER_H

#include "navigation/processing/entities/world.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/navigation/navigation_message.h"

#include <cstdint>
#include <navigation/processing/entities/robot_move.h>

#define PI 3.14159265358979323846

namespace navigation {

class IMotionParser {
 public:
  IMotionParser() = default;

  IMotionParser(const IMotionParser& other) = delete;
  IMotionParser& operator=(const IMotionParser& other) = delete;
  IMotionParser(IMotionParser&& other) = default;
  IMotionParser& operator=(IMotionParser&& other) = default;

  virtual ~IMotionParser() = default;

  virtual NavigationOutputMessage parseMotion(std::unique_ptr<World>& world) = 0;

 private:
  virtual RobotMove fromGoToPoint(std::unique_ptr<World>& world) = 0;

  virtual RobotMove fromRotateInPoint(std::unique_ptr<World>& world) = 0;

  virtual RobotMove fromRotateOnSelf(std::unique_ptr<World>& world) = 0;

  virtual std::optional<DiscretizedPathMessage>
  fromGoToPointWithTrajectory(std::unique_ptr<World>& world);
};

class MotionParser : public IMotionParser {
 public:
  MotionParser();

  NavigationOutputMessage parseMotion(std::unique_ptr<World>& world) override;

 private:
  RobotMove fromGoToPoint(std::unique_ptr<World>& world) override;

  RobotMove fromRotateInPoint(std::unique_ptr<World>& world) override;

  RobotMove fromRotateOnSelf(std::unique_ptr<World>& world) override;

  std::optional<DiscretizedPathMessage>
  fromGoToPointWithTrajectory(std::unique_ptr<World>& world) override;

  int8_t sequence_number_ = 0;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOTION_PARSER_H
