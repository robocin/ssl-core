#ifndef DECISION_PROCESSING_MESSAGES_PERCEPTION_BALL_BALL_MESSAGE_H
#define DECISION_PROCESSING_MESSAGES_PERCEPTION_BALL_BALL_MESSAGE_H

#include "decision/processing/messages/common/robot_id/robot_id_message.h"

#include <cstdint>
#include <google/protobuf/timestamp.pb.h>
#include <optional>
#include <protocols/perception/detection.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/geometry/point3d.h>
#include <sys/types.h>
#include <vector>

namespace decision {

class KickInformationMessage
    : public IProtoConvertible<protocols::perception::Ball::KickInformation> {
 public:
  std::optional<RobotIdMessage> robot_id;
  std::optional<robocin::Point2Df> start_position;
  std::optional<robocin::Point3Df> start_velocity;
  std::optional<uint32_t>
      start_timestamp; // todo(fnap): discuss what to do with timestamp translation
  std::optional<robocin::Point2Df> predicted_stop_position;
  std::optional<uint32_t>
      predicted_stop_timestamp; // todo(fnap): discuss what to do with timestamp translation

  explicit KickInformationMessage(std::optional<RobotIdMessage> robot_id = std::nullopt,
                                  std::optional<robocin::Point2Df> start_position = std::nullopt,
                                  std::optional<robocin::Point3Df> start_velocity = std::nullopt,
                                  std::optional<uint32_t> start_timestamp = std::nullopt,
                                  std::optional<robocin::Point2Df> predicted_stop_position
                                  = std::nullopt,
                                  std::optional<uint32_t> predicted_stop_timestamp = std::nullopt);

  explicit KickInformationMessage(
      const protocols::perception::Ball::KickInformation& kick_information_proto);

  [[nodiscard]] protocols::perception::Ball::KickInformation toProto() const override {
    return protocols::perception::Ball::KickInformation{};
  }

  void fromProto(const protocols::perception::Ball::KickInformation& kick_information_proto);
};

class BallMessage : public IProtoConvertible<protocols::perception::Ball> {
 public:
  std::optional<float> confidence;
  std::optional<robocin::Point3Df> position;
  std::optional<robocin::Point3Df> velocity;
  std::optional<KickInformationMessage> kick_information;

  explicit BallMessage(std::optional<float> confidence = std::nullopt,
                       std::optional<robocin::Point3Df> position = std::nullopt,
                       std::optional<robocin::Point3Df> velocity = std::nullopt,
                       std::optional<KickInformationMessage> kick_information = std::nullopt);

  explicit BallMessage(const protocols::perception::Ball& ball_proto);

  [[nodiscard]] protocols::perception::Ball toProto() const override {
    return protocols::perception::Ball{};
  }

  void fromProto(const protocols::perception::Ball& ball_proto);
};
} // namespace decision

#endif // DECISION_PROCESSING_MESSAGES_PERCEPTION_BALL_BALL_MESSAGE_H
