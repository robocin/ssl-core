#include "decision/processing/messages/perception/ball/ball_message.h"

#include "decision/processing/messages/common/robot_id/robot_id_message.h"

#include <robocin/geometry/point2d.h>

namespace decision {

KickInformationMessage::KickInformationMessage(
    std::optional<RobotIdMessage> robot_id,
    std::optional<robocin::Point2Df> start_position,
    std::optional<robocin::Point3Df> start_velocity,
    std::optional<uint32_t> start_timestamp,
    std::optional<robocin::Point2Df> predicted_stop_position,
    std::optional<uint32_t> predicted_stop_timestamp) :
    robot_id(std::move(robot_id)),
    start_position(start_position),
    start_velocity(start_velocity),
    start_timestamp(start_timestamp),
    predicted_stop_position(predicted_stop_position),
    predicted_stop_timestamp(predicted_stop_timestamp) {}

KickInformationMessage::KickInformationMessage(
    const protocols::perception::Ball::KickInformation& kick_information_proto) {
  KickInformationMessage::fromProto(kick_information_proto);
}

void KickInformationMessage::fromProto(
    const protocols::perception::Ball::KickInformation& kick_information_proto) {
  if (kick_information_proto.has_robot_id()) {
    robot_id = RobotIdMessage(kick_information_proto.robot_id());
  }

  if (kick_information_proto.has_start_position()) {
    start_position = robocin::Point2Df(kick_information_proto.start_position().x(),
                                       kick_information_proto.start_position().y());
  }

  if (kick_information_proto.has_start_velocity()) {
    start_velocity = robocin::Point3Df(kick_information_proto.start_velocity().x(),
                                       kick_information_proto.start_velocity().y(),
                                       kick_information_proto.start_velocity().z());
  }

  if (kick_information_proto.has_predicted_stop_position()) {
    predicted_stop_position
        = robocin::Point2Df(kick_information_proto.predicted_stop_position().x(),
                            kick_information_proto.predicted_stop_position().y());
  }

  start_timestamp = kick_information_proto.start_timestamp()
                        .seconds(); // todo(fnap): discuss how to use this field

  predicted_stop_timestamp = kick_information_proto.predicted_stop_timestamp()
                                 .seconds(); // todo(fnap): discuss how to use this field
}

BallMessage::BallMessage(std::optional<float> confidence,
                         std::optional<robocin::Point3Df> position,
                         std::optional<robocin::Point3Df> velocity,
                         std::optional<KickInformationMessage> kick_information) :
    confidence(confidence),
    position(position),
    velocity(velocity),
    kick_information(std::move(kick_information)) {}

BallMessage::BallMessage(const protocols::perception::Ball& ball_proto) {
  BallMessage::fromProto(ball_proto);
}

void BallMessage::fromProto(const protocols::perception::Ball& ball_proto) {
  confidence = ball_proto.confidence();
  position = robocin::Point3Df(ball_proto.position().x(),
                               ball_proto.position().y(),
                               ball_proto.position().z());

  velocity = robocin::Point3Df(ball_proto.velocity().x(),
                               ball_proto.velocity().y(),
                               ball_proto.velocity().z());

  if (ball_proto.has_kick_information()) {
    if (!kick_information.has_value()) {
      kick_information.emplace();
    }

    kick_information->fromProto(ball_proto.kick_information());
  }
};
} // namespace decision
