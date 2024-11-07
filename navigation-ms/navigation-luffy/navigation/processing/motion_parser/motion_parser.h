#ifndef NAVIGATION_PROCESSING_MOTION_PARSER_H
#define NAVIGATION_PROCESSING_MOTION_PARSER_H

#include "navigation/processing/messages/motion/motion_message.h"
#include "navigation/processing/messages/perception/robot/robot_message.h"

#include <navigation/processing/entities/robot_move.h>
#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/behavior/motion.pb.h>
#include <protocols/perception/detection.pb.h>

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

  virtual RobotMove fromGoToPoint(const GoToPointMessage& go_to_point, const RobotMessage& robot)
      = 0;

  virtual RobotMove fromRotateInPoint(const RotateInPointMessage& rotate_in_point,
                                      const RobotMessage& robot)
      = 0;

  virtual RobotMove fromRotateOnSelf(const RotateOnSelfMessage& rotate_on_self,
                                     const RobotMessage& robot)
      = 0;
};

class MotionParser : public IMotionParser {
 public:
  MotionParser();

  RobotMove fromGoToPoint(const GoToPointMessage& go_to_point, const RobotMessage& robot) override;

  RobotMove fromRotateInPoint(const RotateInPointMessage& rotate_in_point,
                              const RobotMessage& robot) override;

  RobotMove fromRotateOnSelf(const RotateOnSelfMessage& rotate_on_self,
                             const RobotMessage& robot) override;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOTION_PARSER_H
