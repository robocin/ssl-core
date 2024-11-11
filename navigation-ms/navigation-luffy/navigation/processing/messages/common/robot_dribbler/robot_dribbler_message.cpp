#include "navigation/processing/messages/common/robot_dribbler/robot_dribbler_message.h"

#include <algorithm>

namespace navigation {

// DribblerCommandMessage
void DribblerCommandMessage::fromProto(
    const protocols::common::RobotDribbler::DribblerCommand& dribbler_command_proto) {

  dribbler_speed = dribbler_command_proto.dribbler_speed();
  is_active = dribbler_command_proto.is_active();
}

DribblerCommandMessage::DribblerCommandMessage(
    const protocols::common::RobotDribbler::DribblerCommand& dribbler_command_proto) {
  DribblerCommandMessage::fromProto(dribbler_command_proto);
}

DribblerCommandMessage::DribblerCommandMessage(double dribbler_speed, bool is_active) :
    dribbler_speed(dribbler_speed),
    is_active(is_active) {}

protocols::common::RobotDribbler::DribblerCommand DribblerCommandMessage::toProto() const {
  protocols::common::RobotDribbler::DribblerCommand command_proto;
  if (dribbler_speed.has_value()) {
    command_proto.set_dribbler_speed(dribbler_speed.value());
  }
  if (is_active.has_value()) {
    command_proto.set_is_active(is_active.value());
  }
  return command_proto;
};
void DribblerInfoMessage::fromProto(
    const protocols::common::RobotDribbler::DribblerInfo& dribbler_info_proto) {
  dribbler_speed = dribbler_info_proto.dribbler_speed();
  dribbler_current = dribbler_info_proto.dribbler_current();
  is_ball_detected = dribbler_info_proto.is_ball_detected();
}

// DribblerInfoMessage
DribblerInfoMessage::DribblerInfoMessage(
    const protocols::common::RobotDribbler::DribblerInfo& dribbler_info_proto) {
  DribblerInfoMessage::fromProto(dribbler_info_proto);
}

DribblerInfoMessage::DribblerInfoMessage(std::optional<double> dribbler_speed,
                                         std::optional<double> dribbler_current,
                                         std::optional<bool> is_ball_detected) :
    dribbler_speed(dribbler_speed),
    dribbler_current(dribbler_current),
    is_ball_detected(is_ball_detected) {}

protocols::common::RobotDribbler::DribblerInfo DribblerInfoMessage::toProto() const {
  protocols::common::RobotDribbler::DribblerInfo info_proto;
  if (dribbler_speed.has_value()) {
    info_proto.set_dribbler_speed(dribbler_speed.value());
  }
  if (dribbler_current.has_value()) {
    info_proto.set_dribbler_current(dribbler_current.value());
  }
  if (is_ball_detected.has_value()) {
    info_proto.set_is_ball_detected(is_ball_detected.value());
  }

  return info_proto;
};

// RobotDribblerMessage
void RobotDribblerMessage::fromProto(const protocols::common::RobotDribbler& robot_dribbler_proto) {
  if (robot_dribbler_proto.has_dribbler_command()) {
    dribbler_command = DribblerCommandMessage(robot_dribbler_proto.dribbler_command());
  }

  if (robot_dribbler_proto.has_dribbler_info()) {
    dribbler_info = DribblerInfoMessage(robot_dribbler_proto.dribbler_info());
  }
}

RobotDribblerMessage::RobotDribblerMessage(
    const protocols::common::RobotDribbler& robot_dribbler_proto) {
  RobotDribblerMessage::fromProto(robot_dribbler_proto);
}

RobotDribblerMessage::RobotDribblerMessage(std::optional<DribblerCommandMessage> dribbler_command,
                                           std::optional<DribblerInfoMessage> dribbler_info) :

    dribbler_command(std::move(dribbler_command)),
    dribbler_info(std::move(dribbler_info)) {}

protocols::common::RobotDribbler RobotDribblerMessage::toProto() const {
  protocols::common::RobotDribbler dribbler_proto;
  if (dribbler_command.has_value()) {
    dribbler_proto.mutable_dribbler_command()->CopyFrom(dribbler_command->toProto());
  }
  if (dribbler_info.has_value()) {
    dribbler_proto.mutable_dribbler_info()->CopyFrom(dribbler_info->toProto());
  }
  return dribbler_proto;
};

} // namespace navigation
