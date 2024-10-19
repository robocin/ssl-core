#ifndef NAVIGATION_PROCESSING_MOVE_TASK_STATE_H
#define NAVIGATION_PROCESSING_MOVE_TASK_STATE_H

#include <protocols/navigation/motion.pb.h>
#include "navigation/parameters/parameters.h"
#include "common/cpp/robocin/geometry/geometry.h"
#include <robocin/detection_util/elapsed_timer.h>
#include <protocols/perception/detection.pb.h>
#include <robocin/geometry/point2d.h>
namespace navigation {

namespace rc {
  using ::protocols::navigation::GoToPoint;
  using ::protocols::navigation::PathNode;
  using ::protocols::perception::Robot;
  using ::protocols::common::GameCommand;
  using ::robocin::Point2Df;
  using ::robocin::detection_util;
} // namespace rc

enum class SkillMoveState { Unknown, Started, Running, Finished, ChangedTarget };
class MoveTaskState {
  private:
    inline static constexpr double TOLERANCE_TO_CONSIDER_SAME_TARGET = 50;
    double estimateTimeToTarget;
    rc::detection_util::ElapsedTimer runningToTarget;
    rc::detection_util::ElapsedTimer globalRunningToTarget;
    rc::Point2Df currentTarget;
    rc::Point2Df currentDesiredTarget;

    SkillMoveState m_state = SkillMoveState::Unknown;

    inline static bool refereeRequestFinish(const rc::GameCommand& command);

    inline static bool checkFinishState(const rc::Point2Df& allyPosition,
                                        const rc::GoToPoint& goToPointTask,
                                        const rc::Point2Df& lastPosition) ;

    [[nodiscard]] inline bool checkChangeTarget(const rc::GoToPoint& goToPointTask);

  public:
    inline MoveTaskState() = default;

    inline void updateState(const rc::Robot& ally,
                            const rc::GameCommand& command,
                            const rc::GoToPoint& goToPointTask,
                            const rc::PathNode& lastNode);

    [[nodiscard]] inline SkillMoveState currentState();

    inline void initialSetupState(rc::PathNode lastNode);

    inline void resetRunningToTargetTimer();

    inline double executionTimeError(const rc::PathNode& lastNode);
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOVE_TASK_STATE_H
