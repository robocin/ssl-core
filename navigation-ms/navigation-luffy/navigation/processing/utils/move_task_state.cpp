#include "move_task_state.h"

namespace navigation {

namespace rc {
  using ::protocols::navigation::GoToPoint;
  using ::protocols::navigation::PathNode;
  using ::protocols::perception::Robot;
  using ::protocols::common::GameCommand;
  using ::robocin::Point2Df;
  using ::robocin::detection_util;
} // namespace rc

inline static bool MoveTaskState::refereeRequestFinish(const rc::GameCommand& command) {
return std::holds_alternative<GameStatus::StateType::Halt>(command);
}

inline static bool MoveTaskState::checkFinishState(const rc::Point2Df& allyPosition,
                                    const rc::GoToPoint& goToPointTask,
                                    const rc::Point2Df& lastPosition) {
bool robotCloseToDestinationInTask
    = goToPointTask.target().distanceTo(allyPosition) < TOLERANCE_TO_CONSIDER_SAME_TARGET;
bool finishPathToTask = lastPosition.distanceTo(allyPosition) < TOLERANCE_TO_CONSIDER_SAME_TARGET;

return robotCloseToDestinationInTask || finishPathToTask;
}

[[nodiscard]] inline bool MoveTaskState::checkChangeTarget(const rc::GoToPoint& goToPointTask) const {

return currentDesiredTarget().distanceTo(goToPointTask.target())
        > TOLERANCE_TO_CONSIDER_SAME_TARGET;
}


inline void MoveTaskState::updateState(const rc::Robot& ally,
                        const rc::GameCommand& command,
                        const rc::GoToPoint& goToPointTask,
                        const rc::PathNode& lastNode) {

rc::Point2Df lastPositionInPath = lastNode.position() * M_TO_MM();

if (!refereeRequestFinish(command)) {
    if (m_state != SkillMoveState::Unknown
        && checkFinishState(ally.position(), goToPointTask, lastPositionInPath)) {
    m_state = SkillMoveState::Finished;
    set_currentDesiredTarget(std::nullopt);
    } else {
    if (!has_currentDesiredTarget()) {
        m_state = SkillMoveState::Started;
        set_currentTarget(lastNode.position());
        set_estimateTimeToTarget(lastNode.time());
        runningToTarget.restart();
        set_currentDesiredTarget(goToPointTask.target());
        globalRunningToTarget.restart();
    } else if (checkChangeTarget(goToPointTask)) {
        m_state = SkillMoveState::ChangedTarget;
        set_currentDesiredTarget(goToPointTask.target());
    } else {
        m_state = SkillMoveState::Running;
    }
    }
} else {
    m_state = SkillMoveState::Unknown;
}
}

[[nodiscard]] inline SkillMoveState MoveTaskState::currentState() const { return m_state; }

inline void initialSetupState(rc::PathNode lastNode) {
set_currentTarget(lastNode.position());
set_estimateTimeToTarget(lastNode.time());
runningToTarget.restart();
};

inline void MoveTaskState::resetRunningToTargetTimer() {
if (runningToTarget.isValid()) {
    runningToTarget.invalidate();
}
}

inline double MoveTaskState::executionTimeError(const rc::PathNode& lastNode) {
return estimateTimeToTarget()
        - (static_cast<double>(runningToTarget.elapsed()) / 1e9 + lastNode.time());
}
} // namespace navigation