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

  [[nodiscard]] protocols::common::RobotDribbler_DribblerCommand toProto() const override;

  void fromProto(const protocols::common::RobotDribbler_DribblerCommand& dribbler_command) override;

  std::optional<double> dribbler_speed;
  std::optional<bool> is_active;
};

class RobotDribblerMessage : public robocin::IProtoConvertible<protocols::common::RobotDribbler> {
 public:
  explicit RobotDribblerMessage(DribblerCommandMessage dribbler_command = DribblerCommandMessage{});

  [[nodiscard]] protocols::common::RobotDribbler toProto() const override;

  void fromProto(const protocols::common::RobotDribbler& robot_dribbler) override;

  DribblerCommandMessage dribbler_command;
};

} // namespace communication

#endif // COMMUNICATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_ROBOT_DRIBBLER_H
