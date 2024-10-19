#ifndef NAVIGATION_PROCESSING_MOVE_TASK_STATE_H
#define NAVIGATION_PROCESSING_MOVE_TASK_STATE_H

#include <protocols/navigation/motion.pb.h>
#include <protocols/perception/detection.pb.h>
#include <robocin/geometry/point2d.h>
namespace navigation {

namespace rc {
using ::protocols::navigation::GoToPoint;
using ::protocols::navigation::PathNode;
using ::protocols::perception::Robot;
using ::robocin::Point2Df;
} // namespace rc

class MoveTaskState {
  inline static constexpr double TOLERANCE_TO_CONSIDER_SAME_TARGET = 50;
  double estimateTimeToTarget;
  QElapsedTimer runningToTarget;
  QElapsedTimer globalRunningToTarget;
  rc::Point2Df currentTarget;
  rc::Point2Df currentDesiredTarget;

  SkillMoveState m_state = SkillMoveState::Unknown;

  // TODO: fazer escutar do referee ou receber essa informação de alguma forma
  inline static bool refereeRequestFinish(const Referee::State& state) {
    return std::holds_alternative<Referee::StateType::Halt>(state);
  }

  inline static bool checkFinishState(const rc::Point2Df& allyPosition,
                                      const rc::GoToPoint& goToPointTask,
                                      const rc::Point2Df& lastPosition) {
    // TODO: Adaptar função
    bool robotCloseToDestinationInTask
        = goToPointTask.target().distTo(allyPosition) < TOLERANCE_TO_CONSIDER_SAME_TARGET;
    bool finishPathToTask = lastPosition.distTo(allyPosition) < TOLERANCE_TO_CONSIDER_SAME_TARGET;

    return robotCloseToDestinationInTask || finishPathToTask;
  }

  [[nodiscard]] inline bool checkChangeTarget(const rc::GoToPoint& goToPointTask) const {
    // TODO: Adaptar função
    return currentDesiredTarget().distTo(goToPointTask.target())
           > TOLERANCE_TO_CONSIDER_SAME_TARGET;
  }

 public:
  inline MoveTaskState() = default;

  inline void updateState(const rc::Robot& ally,
                          const Referee::State& state,
                          const rc::GoToPoint& goToPointTask,
                          const rc::PathNode& lastNode) {
    // TODO: Adaptar função
    const int M_TO_MM = 1e3; // TODO: transformar em constante do software
    rc::Point2Df lastPositionInPath
        = lastNode.position() * M_TO_MM; // TODO: fazer operações com point

    if (!refereeRequestFinish(state)) {
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

  [[nodiscard]] inline SkillMoveState currentState() const { return m_state; }

  inline void initialSetupState(rc::PathNode lastNode) {
    set_currentTarget(lastNode.position());
    set_estimateTimeToTarget(lastNode.time());
    runningToTarget.restart();
  };

  inline void resetRunningToTargetTimer() {
    if (runningToTarget.isValid()) {
      runningToTarget.invalidate();
    }
  }

  inline double executionTimeError(const rc::PathNode& lastNode) {
    return estimateTimeToTarget()
           - (static_cast<double>(runningToTarget.nsecsElapsed()) / 1e9 + lastNode.time());
  }
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_MOVE_TASK_STATE_H
