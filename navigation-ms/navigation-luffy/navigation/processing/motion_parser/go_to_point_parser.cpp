#include "navigation/processing/motion_parser/go_to_point_parser.h"

#include <protocols/navigation/motion.pb.h>
#include <protocols/perception/detection.pb.h>
#include "navigation/processing/utils/move_task_state.h"
#include <regex>
#include "navigation/parameters/parameters.h"
#include "robocin/geometry/point2d.h"

namespace navigation {

explicit GoToPointParser::GoToPointParser(std::any world) : 
  world_(std::move(world)) {}

RobotMove GoToPointParser::parse(const ::protocols::navigation::GoToPoint& go_to_point,
                                 const ::protocols::perception::Robot& robot) const {
  
    Point2D robot_position = Point2D(robot.position().x(), robot.position().y());
    Point2D target_position = Point2D(go_to_point.target().x(), go_to_point.target().y());
  
    double distanceToGoal = robot_position.distanceTo(target_position);
    double max_velocity = 2.2;

    auto smallestAngleDiff = [](double lhs, double rhs) {
        double angle = fmod(rhs - lhs, 2 * PI);
        if (angle >= PI) {
            return angle - 2 * PI;
        } else if (angle < -PI) {
            return angle + 2 * PI;
        }
        return angle;
    };

    auto fromPolar = [](auto length, auto angle) {
        return std::make_pair(std::cos(angle) * length, std::sin(angle) * length);
    };

    if (distanceToGoal > 50) {
        Point2D theta = (target_position - robot_position).angle();

        auto dTheta = smallestAngleDiff(robot.angle(), go_to_point.target_angle());
        auto v_prop = std::abs(smallestAngleDiff(PI - 0.1, dTheta)) * max_velocity / (PI - 0.1);

        return RobotMove(fromPolar(v_prop, theta), 5 * dTheta);

    } else {
        // anglePID()
        auto dTheta = smallestAngleDiff(robot.angle(), go_to_point.target_angle());

        return RobotMove(5 * dTheta);
    }
}

} // namespace navigation
