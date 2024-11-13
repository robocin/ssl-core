#ifndef DECISION_PROCESSING_ANALYZER_FIELD_ANALYZER_H
#define DECISION_PROCESSING_ANALYZER_FIELD_ANALYZER_H

#include "decision/processing/messages/perception/field/field_message.h"

#include <robocin/geometry/point2d.h>
#include <behavior/parameters/parameters.h>

namespace decision {

class FieldAnalyzer {
 public:
  FieldAnalyzer();

  // goal contains:

  static bool
  leftGoalContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return contains(field.leftGoalInsideBottom(), field.leftGoalOutsideTop(), point, radius);
    } else {
      return contains(field.leftGoalInsideBottom(), field.leftGoalOutsideTop(), point);
    }
  }

  static bool
  rightGoalContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return contains(field.rightGoalOutsideBottom(), field.rightGoalInsideTop(), point, radius);
    } else {
      return contains(field.rightGoalOutsideBottom(), field.rightGoalInsideTop(), point);
    }
  }

  static bool
  allyGoalContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return isAttackingToRight() ? leftGoalContains(point, field, radius) :
                                  rightGoalContains(point, field, radius);
  }

  static bool
  enemyGoalContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return isAttackingToRight() ? rightGoalContains(point, field, radius) :
                                  leftGoalContains(point, field, radius);
  }

  // without goals contains:

  static bool
  withoutGoalsContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return contains(field.bottomLeft(), field.topRight(), point, radius);
    } else {
      return contains(field.bottomLeft(), field.topRight(), point);
    }
  }

  // contains:

  static bool contains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return leftGoalContains(point, field, radius) || withoutGoalsContains(point, field, radius)
           || rightGoalContains(point, field, radius);
  }

  // side contains:

  static bool
  leftSideContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return leftGoalContains(point, field, radius)
             || contains(field.bottomLeft(), field.topCenter(), point, radius);
    } else {
      return leftGoalContains(point, field, radius)
             || contains(field.bottomLeft(), field.topCenter(), point);
    }
  }

  static bool
  rightSideContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return contains(field.bottomCenter(), field.topRight(), point, radius)
             || rightGoalContains(point, field, radius);
    } else {
      return contains(field.bottomCenter(), field.topRight(), point)
             || rightGoalContains(point, field, radius);
    }
  }

  static bool
  allySideContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return isAttackingToRight() ? leftSideContains(point, field, radius) :
                                  rightSideContains(point, field, radius);
  }

  static bool
  enemySideContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return isAttackingToRight() ? rightSideContains(point, field, radius) :
                                  leftSideContains(point, field, radius);
  }

  // penalty area contains:

  static bool
  leftPenaltyAreaContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return contains(robocin::Point2Df(field.min().x, field.leftPenaltyAreaCornerBottom().y),
                      field.leftPenaltyAreaCornerTop(),
                      point,
                      radius);
    } else {
      return contains(robocin::Point2Df(field.min().x, field.leftPenaltyAreaCornerBottom().y),
                      field.leftPenaltyAreaCornerTop(),
                      point);
    }
  }

  static bool
  rightPenaltyAreaContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    if (radius) {
      return contains(field.rightPenaltyAreaCornerBottom(),
                      robocin::Point2Df(field.max().x, field.rightPenaltyAreaCornerTop().y),
                      point,
                      radius);
    } else {
      return contains(field.rightPenaltyAreaCornerBottom(),
                      robocin::Point2Df(field.max().x, field.rightPenaltyAreaCornerTop().y),
                      point);
    }
  }

  static bool
  allyPenaltyAreaContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return isAttackingToRight() ? leftPenaltyAreaContains(point, field, radius) :
                                  rightPenaltyAreaContains(point, field, radius);
  }

  static bool
  enemyPenaltyAreaContains(const robocin::Point2Df& point, FieldMessage& field, double radius = 0) {
    return isAttackingToRight() ? rightPenaltyAreaContains(point, field, radius) :
                                  leftPenaltyAreaContains(point, field, radius);
  }

  [[nodiscard]] constexpr robocin::Point2Df
  nearestPointInsideField(FieldMessage& field,robocin::Point2Df point, real_t margin = 2 * Env::ROBOT_RADIUS + MARGIN_EPS) const {
    return robocin::Point2Df{std::clamp(point.x, min().x() + margin, field.max().x() - margin),
                 std::clamp(point.y, field.min().y() + margin, field.max().y() - margin)};
  }

  [[nodiscard]] constexpr robocin::Point2Df nearestPointInsideFieldOutsidePenaltyAreas(
      FieldMessage& field,
      robocin::Point2Df point,
      real_t fieldMargin = 2 * Env::ROBOT_RADIUS + MARGIN_EPS,
      real_t allyPenaltyAreaMargin = 2 * Env::ROBOT_RADIUS + MARGIN_EPS,
      real_t enemyPenaltyAreaMargin = 2 * Env::ROBOT_RADIUS + MARGIN_EPS) const {

    point = nearestPointInsideField(point, fieldMargin); //TODO: nearestPointInsideField

    auto getClosestProjectedPoint = [point](const std::array<robocin::Point2Df, 4>& area) {
      robocin::Point2Df projected = point.projectOnSegment(area[0], area[1]);
      for (int i = 1; i < 3; ++i) {
        robocin::Point2Df current = point.projectOnSegment(area[i], area[i + 1]);
        if (current.distanceSquaredTo(point) < projected.distanceSquaredTo(point)) {
          projected = current;
        }
      }
      return projected;
    };

    if (auto penaltyMargin = allyPenaltyAreaMargin; allyPenaltyAreaContains(point, penaltyMargin)) {
      auto sign = isAttackingToRight() ? 1 : -1;
      const std::array area
          = {field.allyPenaltyAreaGoalCornerBottom() + robocin::Point2Df{sign * fieldMargin, -penaltyMargin},
             field.allyPenaltyAreaCornerBottom() + robocin::Point2Df{sign * penaltyMargin, -penaltyMargin},
             field.allyPenaltyAreaCornerTop() + robocin::Point2Df{sign * penaltyMargin, penaltyMargin},
             field.allyPenaltyAreaGoalCornerTop() + robocin::Point2Df{sign * fieldMargin, penaltyMargin}};

      return getClosestProjectedPoint(area);
    }

    if (auto penaltyMargin = enemyPenaltyAreaMargin;
        enemyPenaltyAreaContains(point, penaltyMargin)) {
      auto sign = isAttackingToRight() ? -1 : 1;
      const std::array area
          = {field.enemyPenaltyAreaGoalCornerBottom() + robocin::Point2Df{sign * fieldMargin, -penaltyMargin},
             field.enemyPenaltyAreaCornerBottom() + robocin::Point2Df{sign * penaltyMargin, -penaltyMargin},
             field.enemyPenaltyAreaCornerTop() + robocin::Point2Df{sign * penaltyMargin, penaltyMargin},
             field.enemyPenaltyAreaGoalCornerTop() + robocin::Point2Df{sign * fieldMargin, penaltyMargin}};

      return getClosestProjectedPoint(area);
    }

    return point;
  }

 protected:
  // strictly contains:
  static bool contains(const robocin::Point2Df& bottomLeft,
                       const robocin::Point2Df& topRight,
                       const robocin::Point2Df& point) {
    return (bottomLeft.x < point.x && point.x < topRight.x)
           && (bottomLeft.y < point.y && point.y < topRight.y);
  }

  static bool contains(const robocin::Point2Df& a1,
                       const robocin::Point2Df& a2,
                       const robocin::Point2Df& point,
                       double radius) {
    const robocin::Point2Df& b1(point - robocin::Point2Df(radius / 2, radius / 2));
    const robocin::Point2Df& b2(point + robocin::Point2Df(radius / 2, radius / 2));
    return ((b1.x < a2.x) && (a1.x < b2.x)) && ((b1.y < a2.y) && (a1.y < b2.y));
  }
};

} // namespace decision

#endif /* DECISION_PROCESSING_ANALYZER_FIELD_ANALYZER_H */
