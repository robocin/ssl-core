#ifndef MOTIONPARSER_H
#define MOTIONPARSER_H

namespace navigation {
  namespace rc {
    using ::robocin::Point2Df;
    using ::protocols::navigation::GoToPoint;
    using ::protocols::navigation::RotateInPoint;
    using ::protocols::navigation::RotateOnSelf;
    using ::protocols::navigation::GoToPointWithTrajectory;
  } // namespace rc

  class MotionParser {
   public:
    MotionParser(){}
    
    RobotMove parse(const Motion& motion) {
      if (motion == GoToPoint) {
        return goToPointParser.parse(motion);
      } else if (motion == RotateInPoint) {
        return rotateInPointParser.parse(motion);
      } else if (motion == RotateOnSelf) {
        return rotateOnSelfParser.parse(motion);
      } else {
        return goToPointWithTrajectoryParser.parse(motion);
      }
    }
  }

    template <typename T>
    class IMotionParser {
      public:
        IMotionParser() = default;  
        IMotionParser(const IMotionParser&) = delete;
        IMotionParser& operator=(const IMotionParser&) = delete;
        IMotionParser(IMotionParser&&) = default;
        IMotionParser& operator=(IMotionParser&&) = default;  
        virtual ~IMotionParser() = default;  
        virtual RobotMove parse(const T& motion) = 0;
    };

    class RobotMove {
      rc::Point2Df velocity_;
      double angularVelocity_;

    public:
      RobotMove(rc::Point2Df velocity, double angularVelocity) : 
      velocity_(velocity), angularVelocity_(angularVelocity) {}
    };

    class MoveTaskState {
      inline static constexpr double TOLERANCE_TO_CONSIDER_SAME_TARGET = 50;
      double estimateTimeToTarget;
      QElapsedTimer runningToTarget;
      QElapsedTimer globalRunningToTarget;

      PROPERTY(Point, currentTarget);
      PROPERTY(Point, currentDesiredTarget);

      SkillMoveState m_state = SkillMoveState::Unknown;

      inline static bool refereeRequestFinish(const Referee::State& state) {
        return std::holds_alternative<Referee::StateType::Halt>(state);
      }

      inline static bool checkFinishState(const Point& allyPosition,
                                          const MotionType::GoToPoint& goToPointTask,
                                          const Point& lastPosition) {
        bool robotCloseToDestinationInTask =
            goToPointTask.target().distTo(allyPosition) < TOLERANCE_TO_CONSIDER_SAME_TARGET;
        bool finishPathToTask = lastPosition.distTo(allyPosition) < TOLERANCE_TO_CONSIDER_SAME_TARGET;

        return robotCloseToDestinationInTask || finishPathToTask;
      }

      [[nodiscard]] inline bool checkChangeTarget(const MotionType::GoToPoint& goToPointTask) const {
        return currentDesiredTarget().distTo(goToPointTask.target()) >
              TOLERANCE_TO_CONSIDER_SAME_TARGET;
      }

    public:
      inline MoveTaskState() = default;

      inline void updateState(const Ally& ally,
                              const Referee::State& state,
                              const MotionType::GoToPoint& goToPointTask,
                              const MotionType::PathNode& lastNode) {

        Point lastPositionInPath = lastNode.position() * Env::M_TO_MM;

        if (!refereeRequestFinish(state)) {
          if (m_state != SkillMoveState::Unknown &&
              checkFinishState(ally.position(), goToPointTask, lastPositionInPath)) {
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

      [[nodiscard]] inline SkillMoveState currentState() const {
        return m_state;
      }

      inline void initialSetupState(MotionType::PathNode lastNode) {
        set_currentTarget(lastNode.position());
        set_estimateTimeToTarget(lastNode.time());
        runningToTarget.restart();
      };

      inline void resetRunningToTargetTimer() {
        if (runningToTarget.isValid()) {
          runningToTarget.invalidate();
        }
      }

      inline double executionTimeError(const MotionType::PathNode& lastNode) {
        return estimateTimeToTarget() -
              (static_cast<double>(runningToTarget.nsecsElapsed()) / 1e9 + lastNode.time());
      }
    };
}

#endif /* MOTIONPARSER_H */
