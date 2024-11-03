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
  double dribbler_speed;
  bool is_active;

  [[nodiscard]] protocols::common::RobotDribbler::DribblerCommand toProto() const override;

  void fromProto(
      const protocols::common::RobotDribbler::DribblerCommand& dribbler_command_proto) override;
};

class DribblerInfoMessage
    : public robocin::IProtoConvertible<protocols::common::RobotDribbler::DribblerInfo> {
 public:
  explicit DribblerInfoMessage(double dribbler_speed,
                               double dribbler_current,
                               bool is_ball_detected);
  double dribbler_speed;
  double dribbler_current;
  bool is_ball_detected;

  [[nodiscard]] protocols::common::RobotDribbler::DribblerInfo toProto() const override;

  void
  fromProto(const protocols::common::RobotDribbler::DribblerInfo& dribbler_info_proto) override;
};

class RobotDribblerMessage : public robocin::IProtoConvertible<protocols::common::RobotDribbler> {
 public:
  explicit RobotDribblerMessage(std::optional<DribblerCommandMessage> dribbler_command,
                                std::optional<DribblerInfoMessage> dribbler_info);

  std::optional<DribblerCommandMessage> dribbler_command;
  std::optional<DribblerInfoMessage> dribbler_info;

  [[nodiscard]] protocols::common::RobotDribbler toProto() const override;

  void fromProto(const protocols::common::RobotDribbler& robot_dribbler_proto) override;
};
} // namespace navigation

#endif // NAVIGATION_PROCESSING_MESSAGES_COMMON_ROBOT_DRIBBLER_DRIBBLER_MESSAGE_H
