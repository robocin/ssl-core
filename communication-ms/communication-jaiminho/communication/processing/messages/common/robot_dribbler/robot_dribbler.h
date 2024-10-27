#ifndef COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_ROBOT_DRIBBLER_H
#define COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_ROBOT_DRIBBLER_H

#include <optional>
#include <protocols/common/robot_dribbler.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace communication {

class DribblerCommandMessage
    : public robocin::IProtoConvertible<protocols::common::RobotDribbler_DribblerCommand> {
 public:
  explicit DribblerCommandMessage(std::optional<double> dribbler_speed = std::nullopt,
                                  std::optional<bool> is_active = std::nullopt);

  [[nodiscard]] protocols::common::RobotDribbler_DribblerCommand toProto() const override {
    protocols::common::RobotDribbler_DribblerCommand dribbler_command;
    dribbler_command.set_dribbler_speed(dribbler_speed.value_or(0));
    dribbler_command.set_is_active(is_active.value_or(false));

    return dribbler_command;
  };

  void fromProto(protocols::common::RobotDribbler_DribblerCommand dribbler_command) override {
    dribbler_speed = dribbler_command.dribbler_speed();
    is_active = dribbler_command.is_active();
  };

  std::optional<double> dribbler_speed;
  std::optional<bool> is_active;
};

class RobotDribblerMessage : public robocin::IProtoConvertible<protocols::common::RobotDribbler> {
 public:
  explicit RobotDribblerMessage(DribblerCommandMessage dribbler_command = DribblerCommandMessage{});

  [[nodiscard]] protocols::common::RobotDribbler toProto() const override {
    protocols::common::RobotDribbler robot_dribbler;

    robot_dribbler.mutable_dribbler_command()->CopyFrom(dribbler_command.toProto());
    return robot_dribbler;
  };

  void fromProto(protocols::common::RobotDribbler robot_dribbler) override {};

  DribblerCommandMessage dribbler_command;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_ROBOT_DRIBBLER_H
