#ifndef NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_DRIBBLER_MESSAGE_H
#define NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_DRIBBLER_MESSAGE_H

#include <optional>
#include <protocols/common/robot_dribbler.pb.h>
#include <robocin/utility/iproto_convertible.h>

namespace navigation {

class DribblerCommandMessage
    : public robocin::IProtoConvertible<protocols::common::RobotDribbler::DribblerCommand> {
 public:
  explicit DribblerCommandMessage(double dribbler_speed, bool is_active);
  explicit DribblerCommandMessage(
      const protocols::common::RobotDribbler::DribblerCommand& dribbler_command_proto);
  std::optional<double> dribbler_speed;
  std::optional<bool> is_active;

  [[nodiscard]] protocols::common::RobotDribbler::DribblerCommand toProto() const override;

  void fromProto(
      const protocols::common::RobotDribbler::DribblerCommand& dribbler_command_proto) override;
};

class DribblerInfoMessage
    : public robocin::IProtoConvertible<protocols::common::RobotDribbler::DribblerInfo> {
 public:
  std::optional<double> dribbler_speed = 0;
  std::optional<double> dribbler_current = 0;
  std::optional<bool> is_ball_detected = false;

  explicit DribblerInfoMessage(std::optional<double> dribbler_speed = std::nullopt,
                               std::optional<double> dribbler_current = std::nullopt,
                               std::optional<bool> is_ball_detected = std::nullopt);

  explicit DribblerInfoMessage(
      const protocols::common::RobotDribbler::DribblerInfo& dribbler_info_proto);

  [[nodiscard]] protocols::common::RobotDribbler::DribblerInfo toProto() const override;

  void
  fromProto(const protocols::common::RobotDribbler::DribblerInfo& dribbler_info_proto) override;
};

class RobotDribblerMessage : public robocin::IProtoConvertible<protocols::common::RobotDribbler> {
 public:
  explicit RobotDribblerMessage();
  explicit RobotDribblerMessage(std::optional<DribblerCommandMessage> dribbler_command
                                = std::nullopt,
                                std::optional<DribblerInfoMessage> dribbler_info = std::nullopt);

  explicit RobotDribblerMessage(const protocols::common::RobotDribbler& robot_dribbler_proto);

  std::optional<DribblerCommandMessage> dribbler_command;
  std::optional<DribblerInfoMessage> dribbler_info;

  [[nodiscard]] protocols::common::RobotDribbler toProto() const override;

  void fromProto(const protocols::common::RobotDribbler& robot_dribbler_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_DRIBBLER_MESSAGE_H
