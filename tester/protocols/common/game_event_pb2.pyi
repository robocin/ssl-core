from google.protobuf import duration_pb2 as _duration_pb2
from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.common import geometry_pb2 as _geometry_pb2
from protocols.common import robot_id_pb2 as _robot_id_pb2
from protocols.common import team_pb2 as _team_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class GameEvent(_message.Message):
    __slots__ = ("sources", "timestamp", "ball_left_field_touch_line", "ball_left_field_goal_line", "ball_left_field_boundary", "aimless_kick", "goalkeeper_held_ball", "robot_too_close_to_defense_area", "robot_in_defense_area", "robot_pushed_robot", "robot_held_ball_deliberately", "robot_dribbled_ball_too_far", "robot_tipped_over", "robot_touched_ball_in_defense_area", "robot_kicked_ball_too_fast", "robot_crash_unique", "robot_crash_drawn", "robot_too_fast_in_stop", "robot_too_close_to_kick_point", "robot_interfered_ball_placement", "robot_double_touched_ball", "no_progress_in_game", "multiple_cards", "multiple_fouls", "too_many_robots", "ball_placement_succeeded", "ball_placement_failed", "penalty_kick_failed", "possible_goal", "goal", "invalid_goal", "robot_substitution", "challenge_flag", "emergency_stop", "unsporting_behavior_minor", "unsporting_behavior_major")
    class BallLeftField(_message.Message):
        __slots__ = ("by_team", "by_robot", "left_field_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        LEFT_FIELD_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        left_field_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., left_field_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class BallLeftFieldBoundary(_message.Message):
        __slots__ = ("by_team", "left_field_boundary_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        LEFT_FIELD_BOUNDARY_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        left_field_boundary_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., left_field_boundary_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class AimlessKick(_message.Message):
        __slots__ = ("by_team", "by_robot", "left_field_position", "kick_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        LEFT_FIELD_POSITION_FIELD_NUMBER: _ClassVar[int]
        KICK_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        left_field_position: _geometry_pb2.Point2Df
        kick_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., left_field_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., kick_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class GoalkeeperHeldBall(_message.Message):
        __slots__ = ("by_team", "ball_position", "duration")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        DURATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        ball_position: _geometry_pb2.Point2Df
        duration: _duration_pb2.Duration
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., duration: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class RobotTooCloseToDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position", "distance_to_defense_area", "ball_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_TO_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        distance_to_defense_area: float
        ball_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., distance_to_defense_area: _Optional[float] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class RobotInDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position", "distance_to_nearest_point_outside_area")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_TO_NEAREST_POINT_OUTSIDE_AREA_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        distance_to_nearest_point_outside_area: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., distance_to_nearest_point_outside_area: _Optional[float] = ...) -> None: ...
    class RobotPushedRobot(_message.Message):
        __slots__ = ("by_team", "violator_robot", "victim_robot", "position", "pushed_distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        VIOLATOR_ROBOT_FIELD_NUMBER: _ClassVar[int]
        VICTIM_ROBOT_FIELD_NUMBER: _ClassVar[int]
        POSITION_FIELD_NUMBER: _ClassVar[int]
        PUSHED_DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        violator_robot: _robot_id_pb2.RobotId
        victim_robot: _robot_id_pb2.RobotId
        position: _geometry_pb2.Point2Df
        pushed_distance: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., violator_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., victim_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., pushed_distance: _Optional[float] = ...) -> None: ...
    class RobotHeldBallDeliberately(_message.Message):
        __slots__ = ("by_team", "by_robot", "ball_position", "duration")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        DURATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        ball_position: _geometry_pb2.Point2Df
        duration: _duration_pb2.Duration
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., duration: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class RobotDribbledBallTooFar(_message.Message):
        __slots__ = ("by_team", "by_robot", "start_position", "end_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        START_POSITION_FIELD_NUMBER: _ClassVar[int]
        END_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        start_position: _geometry_pb2.Point2Df
        end_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., start_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., end_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class RobotTippedOver(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position", "ball_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        ball_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class RobotTouchedBallInDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position", "distance_to_nearest_point_outside_area")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_TO_NEAREST_POINT_OUTSIDE_AREA_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        distance_to_nearest_point_outside_area: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., distance_to_nearest_point_outside_area: _Optional[float] = ...) -> None: ...
    class RobotKickedBallTooFast(_message.Message):
        __slots__ = ("by_team", "by_robot", "ball_at_highest_speed_position", "initial_ball_speed", "was_chipped_kick")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        BALL_AT_HIGHEST_SPEED_POSITION_FIELD_NUMBER: _ClassVar[int]
        INITIAL_BALL_SPEED_FIELD_NUMBER: _ClassVar[int]
        WAS_CHIPPED_KICK_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        ball_at_highest_speed_position: _geometry_pb2.Point2Df
        initial_ball_speed: float
        was_chipped_kick: bool
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., ball_at_highest_speed_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., initial_ball_speed: _Optional[float] = ..., was_chipped_kick: bool = ...) -> None: ...
    class RobotCrashUnique(_message.Message):
        __slots__ = ("by_team", "violator_robot", "victim_robot", "crash_position", "crash_speed", "speed_difference", "crash_angle")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        VIOLATOR_ROBOT_FIELD_NUMBER: _ClassVar[int]
        VICTIM_ROBOT_FIELD_NUMBER: _ClassVar[int]
        CRASH_POSITION_FIELD_NUMBER: _ClassVar[int]
        CRASH_SPEED_FIELD_NUMBER: _ClassVar[int]
        SPEED_DIFFERENCE_FIELD_NUMBER: _ClassVar[int]
        CRASH_ANGLE_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        violator_robot: _robot_id_pb2.RobotId
        victim_robot: _robot_id_pb2.RobotId
        crash_position: _geometry_pb2.Point2Df
        crash_speed: float
        speed_difference: float
        crash_angle: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., violator_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., victim_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., crash_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., crash_speed: _Optional[float] = ..., speed_difference: _Optional[float] = ..., crash_angle: _Optional[float] = ...) -> None: ...
    class RobotCrashDrawn(_message.Message):
        __slots__ = ("home_robot_id", "away_robot_id", "crash_position", "crash_speed", "speed_difference", "crash_angle")
        HOME_ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
        AWAY_ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
        CRASH_POSITION_FIELD_NUMBER: _ClassVar[int]
        CRASH_SPEED_FIELD_NUMBER: _ClassVar[int]
        SPEED_DIFFERENCE_FIELD_NUMBER: _ClassVar[int]
        CRASH_ANGLE_FIELD_NUMBER: _ClassVar[int]
        home_robot_id: _robot_id_pb2.RobotId
        away_robot_id: _robot_id_pb2.RobotId
        crash_position: _geometry_pb2.Point2Df
        crash_speed: float
        speed_difference: float
        crash_angle: float
        def __init__(self, home_robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., away_robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., crash_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., crash_speed: _Optional[float] = ..., speed_difference: _Optional[float] = ..., crash_angle: _Optional[float] = ...) -> None: ...
    class RobotTooFastInStop(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position", "robot_speed")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        ROBOT_SPEED_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        robot_speed: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., robot_speed: _Optional[float] = ...) -> None: ...
    class RobotTooCloseToKickPoint(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position", "robot_distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        ROBOT_DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        robot_distance: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., robot_distance: _Optional[float] = ...) -> None: ...
    class RobotInterferedBallPlacement(_message.Message):
        __slots__ = ("by_team", "by_robot", "robot_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        robot_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class RobotDoubleTouchedBall(_message.Message):
        __slots__ = ("by_team", "by_robot", "ball_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_ROBOT_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        by_robot: _robot_id_pb2.RobotId
        ball_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., by_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class NoProgressInGame(_message.Message):
        __slots__ = ("ball_position", "duration")
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        DURATION_FIELD_NUMBER: _ClassVar[int]
        ball_position: _geometry_pb2.Point2Df
        duration: _duration_pb2.Duration
        def __init__(self, ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., duration: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class MultipleCards(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ...) -> None: ...
    class MultipleFouls(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ...) -> None: ...
    class TooManyRobots(_message.Message):
        __slots__ = ("by_team", "num_robots_allowed", "num_robots_on_field", "ball_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        NUM_ROBOTS_ALLOWED_FIELD_NUMBER: _ClassVar[int]
        NUM_ROBOTS_ON_FIELD_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        num_robots_allowed: int
        num_robots_on_field: int
        ball_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., num_robots_allowed: _Optional[int] = ..., num_robots_on_field: _Optional[int] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class BallPlacementSucceeded(_message.Message):
        __slots__ = ("by_team", "duration", "distance_to_placement_target", "distance_from_start_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        DURATION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_TO_PLACEMENT_TARGET_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FROM_START_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        duration: _duration_pb2.Duration
        distance_to_placement_target: float
        distance_from_start_position: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., duration: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ..., distance_to_placement_target: _Optional[float] = ..., distance_from_start_position: _Optional[float] = ...) -> None: ...
    class BallPlacementFailed(_message.Message):
        __slots__ = ("by_team", "remaining_distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        REMAINING_DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        remaining_distance: float
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., remaining_distance: _Optional[float] = ...) -> None: ...
    class PenaltyKickFailed(_message.Message):
        __slots__ = ("by_team", "ball_position")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        ball_position: _geometry_pb2.Point2Df
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., ball_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...
    class Goal(_message.Message):
        __slots__ = ("by_team", "kicking_team", "kicking_robot", "ball_position_when_scored", "kick_position", "max_ball_height", "num_of_robots_of_scoring_team", "last_touch_by_scoring_team_timestamp", "message")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        KICKING_TEAM_FIELD_NUMBER: _ClassVar[int]
        KICKING_ROBOT_FIELD_NUMBER: _ClassVar[int]
        BALL_POSITION_WHEN_SCORED_FIELD_NUMBER: _ClassVar[int]
        KICK_POSITION_FIELD_NUMBER: _ClassVar[int]
        MAX_BALL_HEIGHT_FIELD_NUMBER: _ClassVar[int]
        NUM_OF_ROBOTS_OF_SCORING_TEAM_FIELD_NUMBER: _ClassVar[int]
        LAST_TOUCH_BY_SCORING_TEAM_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
        MESSAGE_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        kicking_team: _team_pb2.Team
        kicking_robot: _robot_id_pb2.RobotId
        ball_position_when_scored: _geometry_pb2.Point2Df
        kick_position: _geometry_pb2.Point2Df
        max_ball_height: float
        num_of_robots_of_scoring_team: int
        last_touch_by_scoring_team_timestamp: _timestamp_pb2.Timestamp
        message: str
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., kicking_team: _Optional[_Union[_team_pb2.Team, str]] = ..., kicking_robot: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., ball_position_when_scored: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., kick_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., max_ball_height: _Optional[float] = ..., num_of_robots_of_scoring_team: _Optional[int] = ..., last_touch_by_scoring_team_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., message: _Optional[str] = ...) -> None: ...
    class RobotSubstitution(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ...) -> None: ...
    class ChallengeFlag(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ...) -> None: ...
    class EmergencyStop(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ...) -> None: ...
    class UnsportingBehaviorMinor(_message.Message):
        __slots__ = ("by_team", "reason")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        REASON_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        reason: str
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., reason: _Optional[str] = ...) -> None: ...
    class UnsportingBehaviorMajor(_message.Message):
        __slots__ = ("by_team", "reason")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        REASON_FIELD_NUMBER: _ClassVar[int]
        by_team: _team_pb2.Team
        reason: str
        def __init__(self, by_team: _Optional[_Union[_team_pb2.Team, str]] = ..., reason: _Optional[str] = ...) -> None: ...
    SOURCES_FIELD_NUMBER: _ClassVar[int]
    TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    BALL_LEFT_FIELD_TOUCH_LINE_FIELD_NUMBER: _ClassVar[int]
    BALL_LEFT_FIELD_GOAL_LINE_FIELD_NUMBER: _ClassVar[int]
    BALL_LEFT_FIELD_BOUNDARY_FIELD_NUMBER: _ClassVar[int]
    AIMLESS_KICK_FIELD_NUMBER: _ClassVar[int]
    GOALKEEPER_HELD_BALL_FIELD_NUMBER: _ClassVar[int]
    ROBOT_TOO_CLOSE_TO_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    ROBOT_IN_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    ROBOT_PUSHED_ROBOT_FIELD_NUMBER: _ClassVar[int]
    ROBOT_HELD_BALL_DELIBERATELY_FIELD_NUMBER: _ClassVar[int]
    ROBOT_DRIBBLED_BALL_TOO_FAR_FIELD_NUMBER: _ClassVar[int]
    ROBOT_TIPPED_OVER_FIELD_NUMBER: _ClassVar[int]
    ROBOT_TOUCHED_BALL_IN_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    ROBOT_KICKED_BALL_TOO_FAST_FIELD_NUMBER: _ClassVar[int]
    ROBOT_CRASH_UNIQUE_FIELD_NUMBER: _ClassVar[int]
    ROBOT_CRASH_DRAWN_FIELD_NUMBER: _ClassVar[int]
    ROBOT_TOO_FAST_IN_STOP_FIELD_NUMBER: _ClassVar[int]
    ROBOT_TOO_CLOSE_TO_KICK_POINT_FIELD_NUMBER: _ClassVar[int]
    ROBOT_INTERFERED_BALL_PLACEMENT_FIELD_NUMBER: _ClassVar[int]
    ROBOT_DOUBLE_TOUCHED_BALL_FIELD_NUMBER: _ClassVar[int]
    NO_PROGRESS_IN_GAME_FIELD_NUMBER: _ClassVar[int]
    MULTIPLE_CARDS_FIELD_NUMBER: _ClassVar[int]
    MULTIPLE_FOULS_FIELD_NUMBER: _ClassVar[int]
    TOO_MANY_ROBOTS_FIELD_NUMBER: _ClassVar[int]
    BALL_PLACEMENT_SUCCEEDED_FIELD_NUMBER: _ClassVar[int]
    BALL_PLACEMENT_FAILED_FIELD_NUMBER: _ClassVar[int]
    PENALTY_KICK_FAILED_FIELD_NUMBER: _ClassVar[int]
    POSSIBLE_GOAL_FIELD_NUMBER: _ClassVar[int]
    GOAL_FIELD_NUMBER: _ClassVar[int]
    INVALID_GOAL_FIELD_NUMBER: _ClassVar[int]
    ROBOT_SUBSTITUTION_FIELD_NUMBER: _ClassVar[int]
    CHALLENGE_FLAG_FIELD_NUMBER: _ClassVar[int]
    EMERGENCY_STOP_FIELD_NUMBER: _ClassVar[int]
    UNSPORTING_BEHAVIOR_MINOR_FIELD_NUMBER: _ClassVar[int]
    UNSPORTING_BEHAVIOR_MAJOR_FIELD_NUMBER: _ClassVar[int]
    sources: _containers.RepeatedScalarFieldContainer[str]
    timestamp: _timestamp_pb2.Timestamp
    ball_left_field_touch_line: GameEvent.BallLeftField
    ball_left_field_goal_line: GameEvent.BallLeftField
    ball_left_field_boundary: GameEvent.BallLeftFieldBoundary
    aimless_kick: GameEvent.AimlessKick
    goalkeeper_held_ball: GameEvent.GoalkeeperHeldBall
    robot_too_close_to_defense_area: GameEvent.RobotTooCloseToDefenseArea
    robot_in_defense_area: GameEvent.RobotInDefenseArea
    robot_pushed_robot: GameEvent.RobotPushedRobot
    robot_held_ball_deliberately: GameEvent.RobotHeldBallDeliberately
    robot_dribbled_ball_too_far: GameEvent.RobotDribbledBallTooFar
    robot_tipped_over: GameEvent.RobotTippedOver
    robot_touched_ball_in_defense_area: GameEvent.RobotTouchedBallInDefenseArea
    robot_kicked_ball_too_fast: GameEvent.RobotKickedBallTooFast
    robot_crash_unique: GameEvent.RobotCrashUnique
    robot_crash_drawn: GameEvent.RobotCrashDrawn
    robot_too_fast_in_stop: GameEvent.RobotTooFastInStop
    robot_too_close_to_kick_point: GameEvent.RobotTooCloseToKickPoint
    robot_interfered_ball_placement: GameEvent.RobotInterferedBallPlacement
    robot_double_touched_ball: GameEvent.RobotDoubleTouchedBall
    no_progress_in_game: GameEvent.NoProgressInGame
    multiple_cards: GameEvent.MultipleCards
    multiple_fouls: GameEvent.MultipleFouls
    too_many_robots: GameEvent.TooManyRobots
    ball_placement_succeeded: GameEvent.BallPlacementSucceeded
    ball_placement_failed: GameEvent.BallPlacementFailed
    penalty_kick_failed: GameEvent.PenaltyKickFailed
    possible_goal: GameEvent.Goal
    goal: GameEvent.Goal
    invalid_goal: GameEvent.Goal
    robot_substitution: GameEvent.RobotSubstitution
    challenge_flag: GameEvent.ChallengeFlag
    emergency_stop: GameEvent.EmergencyStop
    unsporting_behavior_minor: GameEvent.UnsportingBehaviorMinor
    unsporting_behavior_major: GameEvent.UnsportingBehaviorMajor
    def __init__(self, sources: _Optional[_Iterable[str]] = ..., timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., ball_left_field_touch_line: _Optional[_Union[GameEvent.BallLeftField, _Mapping]] = ..., ball_left_field_goal_line: _Optional[_Union[GameEvent.BallLeftField, _Mapping]] = ..., ball_left_field_boundary: _Optional[_Union[GameEvent.BallLeftFieldBoundary, _Mapping]] = ..., aimless_kick: _Optional[_Union[GameEvent.AimlessKick, _Mapping]] = ..., goalkeeper_held_ball: _Optional[_Union[GameEvent.GoalkeeperHeldBall, _Mapping]] = ..., robot_too_close_to_defense_area: _Optional[_Union[GameEvent.RobotTooCloseToDefenseArea, _Mapping]] = ..., robot_in_defense_area: _Optional[_Union[GameEvent.RobotInDefenseArea, _Mapping]] = ..., robot_pushed_robot: _Optional[_Union[GameEvent.RobotPushedRobot, _Mapping]] = ..., robot_held_ball_deliberately: _Optional[_Union[GameEvent.RobotHeldBallDeliberately, _Mapping]] = ..., robot_dribbled_ball_too_far: _Optional[_Union[GameEvent.RobotDribbledBallTooFar, _Mapping]] = ..., robot_tipped_over: _Optional[_Union[GameEvent.RobotTippedOver, _Mapping]] = ..., robot_touched_ball_in_defense_area: _Optional[_Union[GameEvent.RobotTouchedBallInDefenseArea, _Mapping]] = ..., robot_kicked_ball_too_fast: _Optional[_Union[GameEvent.RobotKickedBallTooFast, _Mapping]] = ..., robot_crash_unique: _Optional[_Union[GameEvent.RobotCrashUnique, _Mapping]] = ..., robot_crash_drawn: _Optional[_Union[GameEvent.RobotCrashDrawn, _Mapping]] = ..., robot_too_fast_in_stop: _Optional[_Union[GameEvent.RobotTooFastInStop, _Mapping]] = ..., robot_too_close_to_kick_point: _Optional[_Union[GameEvent.RobotTooCloseToKickPoint, _Mapping]] = ..., robot_interfered_ball_placement: _Optional[_Union[GameEvent.RobotInterferedBallPlacement, _Mapping]] = ..., robot_double_touched_ball: _Optional[_Union[GameEvent.RobotDoubleTouchedBall, _Mapping]] = ..., no_progress_in_game: _Optional[_Union[GameEvent.NoProgressInGame, _Mapping]] = ..., multiple_cards: _Optional[_Union[GameEvent.MultipleCards, _Mapping]] = ..., multiple_fouls: _Optional[_Union[GameEvent.MultipleFouls, _Mapping]] = ..., too_many_robots: _Optional[_Union[GameEvent.TooManyRobots, _Mapping]] = ..., ball_placement_succeeded: _Optional[_Union[GameEvent.BallPlacementSucceeded, _Mapping]] = ..., ball_placement_failed: _Optional[_Union[GameEvent.BallPlacementFailed, _Mapping]] = ..., penalty_kick_failed: _Optional[_Union[GameEvent.PenaltyKickFailed, _Mapping]] = ..., possible_goal: _Optional[_Union[GameEvent.Goal, _Mapping]] = ..., goal: _Optional[_Union[GameEvent.Goal, _Mapping]] = ..., invalid_goal: _Optional[_Union[GameEvent.Goal, _Mapping]] = ..., robot_substitution: _Optional[_Union[GameEvent.RobotSubstitution, _Mapping]] = ..., challenge_flag: _Optional[_Union[GameEvent.ChallengeFlag, _Mapping]] = ..., emergency_stop: _Optional[_Union[GameEvent.EmergencyStop, _Mapping]] = ..., unsporting_behavior_minor: _Optional[_Union[GameEvent.UnsportingBehaviorMinor, _Mapping]] = ..., unsporting_behavior_major: _Optional[_Union[GameEvent.UnsportingBehaviorMajor, _Mapping]] = ...) -> None: ...
