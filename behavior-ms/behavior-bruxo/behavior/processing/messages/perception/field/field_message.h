#ifndef BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H
#define BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H

#include "behavior/parameters/parameters.h"

#include <cstdint>
#include <optional>
#include <protocols/perception/detection.pb.h>
#include <robocin/geometry/point2d.h>
#include <robocin/utility/iproto_convertible.h>

namespace behavior {

class FieldMessage : public robocin::IProtoConvertible<protocols::perception::Field> {
 public:
  std::optional<uint64_t> serial_id;
  std::optional<float> length;
  std::optional<float> width;
  std::optional<float> goal_depth;
  std::optional<float> goal_width;
  std::optional<float> penalty_area_depth;
  std::optional<float> penalty_area_width;
  std::optional<float> boundary_width;
  std::optional<float> goal_center_to_penalty_mark;

  explicit FieldMessage(std::optional<uint64_t> serial_id = std::nullopt,
                        std::optional<float> length = std::nullopt,
                        std::optional<float> width = std::nullopt,
                        std::optional<float> goal_depth = std::nullopt,
                        std::optional<float> goal_width = std::nullopt,
                        std::optional<float> penalty_area_depth = std::nullopt,
                        std::optional<float> penalty_area_width = std::nullopt,
                        std::optional<float> boundary_width = std::nullopt,
                        std::optional<float> goal_center_to_penalty_mark = std::nullopt);

  explicit FieldMessage(const protocols::perception::Field& field_proto);

  [[nodiscard]] protocols::perception::Field toProto() const override {
    return protocols::perception::Field{};
  }

  void fromProto(const protocols::perception::Field& field_proto) override;

  // min is the left-lower position without the goal depth.
  [[nodiscard]] robocin::Point2Df min() const {
    return robocin::Point2Df(-(*length / 2), -(*width / 2));
  }

  // center in (0, 0).
  [[nodiscard]] robocin::Point2Df center() const { return robocin::Point2Df(0, 0); }

  // max is the right-upper position without the goal depth.
  [[nodiscard]] robocin::Point2Df max() const {
    return robocin::Point2Df(+(*length / 2), +(*width / 2));
  }

  // field corners:

  // equals to min().
  [[nodiscard]] robocin::Point2Df bottomLeft() const { return min(); }

  [[nodiscard]] robocin::Point2Df bottomCenter() const {
    return robocin::Point2Df(center().x, min().y);
  }

  [[nodiscard]] robocin::Point2Df bottomRight() const {
    return robocin::Point2Df(max().x, min().y);
  }

  [[nodiscard]] robocin::Point2Df topLeft() const { return robocin::Point2Df(min().x, max().y); }

  [[nodiscard]] robocin::Point2Df topCenter() const {
    return robocin::Point2Df(center().x, max().y);
  }

  // equals to max().
  [[nodiscard]] robocin::Point2Df topRight() const { return max(); }

  // goal inside bottom:

  // left goalkeeper goal inside bottom.
  [[nodiscard]] robocin::Point2Df leftGoalInsideBottom() const {
    return robocin::Point2Df(min().x - *goal_depth, center().y - (*goal_width / 2));
  }

  // right goalkeeper goal inside bottom.
  [[nodiscard]] robocin::Point2Df rightGoalInsideBottom() const {
    return robocin::Point2Df(max().x + *goal_depth, center().y - (*goal_width / 2));
  }

  // our goalkeeper goal inside bottom.
  [[nodiscard]] robocin::Point2Df allyGoalInsideBottom() const {
    return isAttackingToRight() ? leftGoalInsideBottom() : rightGoalInsideBottom();
  }

  // enemy goalkeeper goal inside bottom.
  [[nodiscard]] robocin::Point2Df enemyGoalInsideBottom() const {
    return isAttackingToRight() ? rightGoalInsideBottom() : leftGoalInsideBottom();
  }

  // goal inside center:

  // left goalkeeper goal inside center.
  [[nodiscard]] robocin::Point2Df leftGoalInsideCenter() const {
    return robocin::Point2Df(min().x - *goal_depth, center().y);
  }

  // right goalkeeper goal inside center.
  [[nodiscard]] robocin::Point2Df rightGoalInsideCenter() const {
    return robocin::Point2Df(max().x + *goal_depth, center().y);
  }

  // our goalkeeper goal inside center.
  [[nodiscard]] robocin::Point2Df allyGoalInsideCenter() const {
    return isAttackingToRight() ? leftGoalInsideCenter() : rightGoalInsideCenter();
  }

  // enemy goalkeeper goal inside center.
  [[nodiscard]] robocin::Point2Df enemyGoalInsideCenter() const {
    return isAttackingToRight() ? rightGoalInsideCenter() : leftGoalInsideCenter();
  }

  // goal inside top:

  // left goalkeeper goal inside top.
  [[nodiscard]] robocin::Point2Df leftGoalInsideTop() const {
    return robocin::Point2Df(min().x - *goal_depth, center().y + (*goal_width / 2));
  }

  // right goalkeeper goal inside top.
  [[nodiscard]] robocin::Point2Df rightGoalInsideTop() const {
    return robocin::Point2Df(max().x + *goal_depth, center().y + (*goal_width / 2));
  }

  // our goalkeeper goal inside top.
  [[nodiscard]] robocin::Point2Df allyGoalInsideTop() const {
    return isAttackingToRight() ? leftGoalInsideTop() : rightGoalInsideTop();
  }

  // enemy goalkeeper goal inside top.
  [[nodiscard]] robocin::Point2Df enemyGoalInsideTop() const {
    return isAttackingToRight() ? rightGoalInsideTop() : leftGoalInsideTop();
  }

  // goal outside bottom:

  // left goalkeeper goal outside bottom.
  [[nodiscard]] robocin::Point2Df leftGoalOutsideBottom() const {
    return robocin::Point2Df(min().x, center().y - (*goal_width / 2));
  }

  // right goalkeeper goal outside Bottom.
  [[nodiscard]] robocin::Point2Df rightGoalOutsideBottom() const {
    return robocin::Point2Df(max().x, center().y - (*goal_width / 2));
  }

  // our goalkeeper goal outside bottom.
  [[nodiscard]] robocin::Point2Df allyGoalOutsideBottom() const {
    return isAttackingToRight() ? leftGoalOutsideBottom() : rightGoalOutsideBottom();
  }

  // enemy goalkeeper goal outside bottom.
  [[nodiscard]] robocin::Point2Df enemyGoalOutsideBottom() const {
    return isAttackingToRight() ? rightGoalOutsideBottom() : leftGoalOutsideBottom();
  }

  // goal outside center:

  // left goalkeeper goal outside center.
  [[nodiscard]] robocin::Point2Df leftGoalOutsideCenter() const {
    return robocin::Point2Df(min().x, center().y);
  }

  // right goalkeeper goal outside center.
  [[nodiscard]] robocin::Point2Df rightGoalOutsideCenter() const {
    return robocin::Point2Df(max().x, center().y);
  }

  // our goalkeeper goal outside center.
  [[nodiscard]] robocin::Point2Df allyGoalOutsideCenter() const {
    return isAttackingToRight() ? leftGoalOutsideCenter() : rightGoalOutsideCenter();
  }

  // enemy goalkeeper goal outside center.
  [[nodiscard]] robocin::Point2Df enemyGoalOutsideCenter() const {
    return isAttackingToRight() ? rightGoalOutsideCenter() : leftGoalOutsideCenter();
  }

  // goal outside top:

  // left goalkeeper goal outside top.
  [[nodiscard]] robocin::Point2Df leftGoalOutsideTop() const {
    return robocin::Point2Df(min().x, center().y + (*goal_width / 2));
  }

  // right goalkeeper goal outside top.
  [[nodiscard]] robocin::Point2Df rightGoalOutsideTop() const {
    return robocin::Point2Df(max().x, center().y + (*goal_width / 2));
  }

  // our goalkeeper goal outside top.
  [[nodiscard]] robocin::Point2Df allyGoalOutsideTop() const {
    return isAttackingToRight() ? leftGoalOutsideTop() : rightGoalOutsideTop();
  }

  // enemy goalkeeper goal outside top.
  [[nodiscard]] robocin::Point2Df enemyGoalOutsideTop() const {
    return isAttackingToRight() ? rightGoalOutsideTop() : leftGoalOutsideTop();
  }

  // penalty area corner bottom:

  // left goalkeeper penalty area corner bottom.
  [[nodiscard]] robocin::Point2Df leftPenaltyAreaCornerBottom() const {
    return robocin::Point2Df(min().x + *penalty_area_depth, center().y - (*penalty_area_width / 2));
  }

  // right goalkeeper penalty area corner bottom.
  [[nodiscard]] robocin::Point2Df rightPenaltyAreaCornerBottom() const {
    return robocin::Point2Df(max().x - *penalty_area_depth, center().y - (*penalty_area_width / 2));
  }

  // our goalkeeper penalty area corner bottom.
  [[nodiscard]] robocin::Point2Df allyPenaltyAreaCornerBottom() const {
    return isAttackingToRight() ? leftPenaltyAreaCornerBottom() : rightPenaltyAreaCornerBottom();
  }

  // enemy goalkeeper penalty area corner bottom.
  [[nodiscard]] robocin::Point2Df enemyPenaltyAreaCornerBottom() const {
    return isAttackingToRight() ? rightPenaltyAreaCornerBottom() : leftPenaltyAreaCornerBottom();
  }

  // penalty area center:

  // left goalkeeper penalty area center.
  [[nodiscard]] robocin::Point2Df leftPenaltyAreaCenter() const {
    return robocin::Point2Df(min().x + *penalty_area_depth, center().y);
  }

  // right goalkeeper penalty area center.
  [[nodiscard]] robocin::Point2Df rightPenaltyAreaCenter() const {
    return robocin::Point2Df(max().x - *penalty_area_depth, center().y);
  }

  // our goalkeeper penalty area center.
  [[nodiscard]] robocin::Point2Df allyPenaltyAreaCenter() const {
    return isAttackingToRight() ? leftPenaltyAreaCenter() : rightPenaltyAreaCenter();
  }

  // enemy goalkeeper penalty area center.
  [[nodiscard]] robocin::Point2Df enemyPenaltyAreaCenter() const {
    return isAttackingToRight() ? rightPenaltyAreaCenter() : leftPenaltyAreaCenter();
  }

  // penalty area corner top:

  // left goalkeeper penalty area corner top.
  [[nodiscard]] robocin::Point2Df leftPenaltyAreaCornerTop() const {
    return robocin::Point2Df(min().x + *penalty_area_depth, center().y + (*penalty_area_width / 2));
  }

  // right goalkeeper penalty area corner top.
  [[nodiscard]] robocin::Point2Df rightPenaltyAreaCornerTop() const {
    return robocin::Point2Df(max().x - *penalty_area_depth, center().y + (*penalty_area_width / 2));
  }

  // our goalkeeper penalty area corner top.
  [[nodiscard]] robocin::Point2Df allyPenaltyAreaCornerTop() const {
    return isAttackingToRight() ? leftPenaltyAreaCornerTop() : rightPenaltyAreaCornerTop();
  }

  // enemy goalkeeper penalty area corner top.
  [[nodiscard]] robocin::Point2Df enemyPenaltyAreaCornerTop() const {
    return isAttackingToRight() ? rightPenaltyAreaCornerTop() : leftPenaltyAreaCornerTop();
  }

  // penalty area goal corner top:

  // left goalkeeper penalty area goal corner top.
  [[nodiscard]] robocin::Point2Df leftPenaltyAreaGoalCornerTop() const {
    return robocin::Point2Df(min().x, (*penalty_area_width / 2));
  }

  // right goalkeeper penalty area goal corner top.
  [[nodiscard]] robocin::Point2Df rightPenaltyAreaGoalCornerTop() const {
    return robocin::Point2Df(max().x, (*penalty_area_width / 2));
  }

  // our goalkeeper penalty area goal corner top.
  [[nodiscard]] robocin::Point2Df allyPenaltyAreaGoalCornerTop() const {
    return isAttackingToRight() ? leftPenaltyAreaGoalCornerTop() : rightPenaltyAreaGoalCornerTop();
  }

  // enemy goalkeeper penalty area goal corner top.
  [[nodiscard]] robocin::Point2Df enemyPenaltyAreaGoalCornerTop() const {
    return isAttackingToRight() ? rightPenaltyAreaGoalCornerTop() : leftPenaltyAreaGoalCornerTop();
  }

  // penalty area goal corner bottom:

  // left goalkeeper penalty area goal corner bottom.
  [[nodiscard]] robocin::Point2Df leftPenaltyAreaGoalCornerBottom() const {
    return robocin::Point2Df(min().x, -(*penalty_area_width / 2));
  }

  // right goalkeeper penalty area goal corner bottom.
  [[nodiscard]] robocin::Point2Df rightPenaltyAreaGoalCornerBottom() const {
    return robocin::Point2Df(max().x, -(*penalty_area_width / 2));
  }

  // our goalkeeper penalty area goal corner bottom.
  [[nodiscard]] robocin::Point2Df allyPenaltyAreaGoalCornerBottom() const {
    return isAttackingToRight() ? leftPenaltyAreaGoalCornerBottom() :
                                  rightPenaltyAreaGoalCornerBottom();
  }

  // enemy goalkeeper penalty area goal corner bottom.
  [[nodiscard]] robocin::Point2Df enemyPenaltyAreaGoalCornerBottom() const {
    return isAttackingToRight() ? rightPenaltyAreaGoalCornerBottom() :
                                  leftPenaltyAreaGoalCornerBottom();
  }

  static robocin::Point2Df leftDirection() { return robocin::Point2Df(-1, 0); }

  static robocin::Point2Df rightDirection() { return robocin::Point2Df(+1, 0); }

  [[nodiscard]] robocin::Point2Df attackDirection() const {
    return isAttackingToRight() ? rightDirection() : leftDirection();
  }

  [[nodiscard]] robocin::Point2Df defendDirection() const {
    return isAttackingToRight() ? leftDirection() : rightDirection();
  }
};
} // namespace behavior
#endif // BEHAVIOR_PROCESSING_MESSAGES_PERCEPTION_FIELD_FIELD_MESSAGE_H
