#ifndef COMMUNICATION_PROCESSING_ROBOT_COMMAND_ROBOT_COMMAND_MAPPER_H
#define COMMUNICATION_PROCESSING_ROBOT_COMMAND_ROBOT_COMMAND_MAPPER_H

// #include <protocols/common/team.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/communication/robot_info.pb.h>
#include <robocin/memory/object_ptr.h>

namespace communication {

class IRobotCommandMapper {
 public:
  IRobotCommandMapper() = default;

  IRobotCommandMapper(const IRobotCommandMapper&) = delete;
  IRobotCommandMapper& operator=(const IRobotCommandMapper&) = delete;
  IRobotCommandMapper(IRobotCommandMapper&&) = default;
  IRobotCommandMapper& operator=(IRobotCommandMapper&&) = default;

  virtual ~IRobotCommandMapper() = default;

  virtual ::protocols::communication::RoboComm fromNavigation(const ::protocols::navigation::Navigation& navigation) = 0;
};

class RobotCommandMapper : public IRobotCommandMapper {
 public:
  RobotCommandMapper() = default;

  ::protocols::referee::GameStatus fromNavigationAndReferee(
      const ::protocols::navigation::Navigation& navigation
      const ::protocols::thirdy) override;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_ROBOT_COMMAND_ROBOT_COMMAND_MAPPER_H
