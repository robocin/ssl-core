#ifndef NAVIGATION_PROCESSING_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_MOTION_PARSER_H

#include "navigation/processing/entities/world.h"
#include "navigation/processing/messages/behavior/behavior_message.h"
#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/navigation/navigation_message.h"
#include "navigation/processing/messages/perception/detection/detection_message.h"
#include "navigation/processing/messages/referee/game_status_message.h"

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

  virtual NavigationOutputMessage parseMotion() = 0;

  virtual void setWorld(const OutputMessage& behavior,
                        const DetectionMessage& detection,
                        const GameStatusMessage& game_status)
      = 0;

 private:
  virtual RobotMove fromGoToPoint(const GoToPointMessage& go_to_point) = 0;

  virtual RobotMove fromRotateInPoint(const RotateInPointMessage& rotate_in_point) = 0;

  virtual RobotMove fromRotateOnSelf(const RotateOnSelfMessage& rotate_on_self) = 0;
};

class MotionParser : public IMotionParser {
 public:
  MotionParser();

  NavigationOutputMessage parseMotion() override;

  void setWorld(const OutputMessage& behavior,
                const DetectionMessage& detection,
                const GameStatusMessage& game_status) override;

 private:
  RobotMove fromGoToPoint(const GoToPointMessage& go_to_point) override;

  RobotMove fromRotateInPoint(const RotateInPointMessage& rotate_in_point) override;

  RobotMove fromRotateOnSelf(const RotateOnSelfMessage& rotate_on_self) override;

  World world_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOTION_PARSER_H
