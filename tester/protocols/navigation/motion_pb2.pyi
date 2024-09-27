from protocols.common import geometry_pb2 as _geometry_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class PrecisionToTarget(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    High: _ClassVar[PrecisionToTarget]
    Normal: _ClassVar[PrecisionToTarget]

class MovingProfile(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    SafeInStopSpeed: _ClassVar[MovingProfile]
    BalancedInApproachBallSpeed: _ClassVar[MovingProfile]
    BalancedInCarryBallSpeed: _ClassVar[MovingProfile]
    BalancedInCarryBallLowSpeed: _ClassVar[MovingProfile]
    DirectApproachBallSpeed: _ClassVar[MovingProfile]
    DirectSafeKickBallSpeed: _ClassVar[MovingProfile]
    DirectBalancedKickBallSpeed: _ClassVar[MovingProfile]
    DirectKickBallwithEnemyClose: _ClassVar[MovingProfile]
    gotoBallWithEnemy: _ClassVar[MovingProfile]
    PushBallInPenalty: _ClassVar[MovingProfile]
    TOTOZINHO: _ClassVar[MovingProfile]
    BalancedInSlowSpeed: _ClassVar[MovingProfile]
    BalancedInMedianSpeed: _ClassVar[MovingProfile]
    BalancedInDefaultSpeed: _ClassVar[MovingProfile]
    BalancedInHighSpeed: _ClassVar[MovingProfile]
    GoalkeeperInTopSpeed: _ClassVar[MovingProfile]
    PenaltyPushBall: _ClassVar[MovingProfile]
High: PrecisionToTarget
Normal: PrecisionToTarget
SafeInStopSpeed: MovingProfile
BalancedInApproachBallSpeed: MovingProfile
BalancedInCarryBallSpeed: MovingProfile
BalancedInCarryBallLowSpeed: MovingProfile
DirectApproachBallSpeed: MovingProfile
DirectSafeKickBallSpeed: MovingProfile
DirectBalancedKickBallSpeed: MovingProfile
DirectKickBallwithEnemyClose: MovingProfile
gotoBallWithEnemy: MovingProfile
PushBallInPenalty: MovingProfile
TOTOZINHO: MovingProfile
BalancedInSlowSpeed: MovingProfile
BalancedInMedianSpeed: MovingProfile
BalancedInDefaultSpeed: MovingProfile
BalancedInHighSpeed: MovingProfile
GoalkeeperInTopSpeed: MovingProfile
PenaltyPushBall: MovingProfile

class DiscretizedPath(_message.Message):
    __slots__ = ("path", "go_to_point")
    PATH_FIELD_NUMBER: _ClassVar[int]
    GO_TO_POINT_FIELD_NUMBER: _ClassVar[int]
    path: _containers.RepeatedCompositeFieldContainer[PathNode]
    go_to_point: GoToPoint
    def __init__(self, path: _Optional[_Iterable[_Union[PathNode, _Mapping]]] = ..., go_to_point: _Optional[_Union[GoToPoint, _Mapping]] = ...) -> None: ...

class PathNode(_message.Message):
    __slots__ = ("position", "velocity", "time")
    POSITION_FIELD_NUMBER: _ClassVar[int]
    VELOCITY_FIELD_NUMBER: _ClassVar[int]
    TIME_FIELD_NUMBER: _ClassVar[int]
    position: _geometry_pb2.Point2Df
    velocity: _geometry_pb2.Point2Df
    time: float
    def __init__(self, position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., time: _Optional[float] = ...) -> None: ...

class RotateInPoint(_message.Message):
    __slots__ = ("target", "target_angle", "clockwise", "orbit_radius", "rotate_velocity", "min_velocity", "approach_kp", "angle_kp")
    TARGET_FIELD_NUMBER: _ClassVar[int]
    TARGET_ANGLE_FIELD_NUMBER: _ClassVar[int]
    CLOCKWISE_FIELD_NUMBER: _ClassVar[int]
    ORBIT_RADIUS_FIELD_NUMBER: _ClassVar[int]
    ROTATE_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    MIN_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    APPROACH_KP_FIELD_NUMBER: _ClassVar[int]
    ANGLE_KP_FIELD_NUMBER: _ClassVar[int]
    target: _geometry_pb2.Point2Df
    target_angle: float
    clockwise: bool
    orbit_radius: float
    rotate_velocity: float
    min_velocity: float
    approach_kp: float
    angle_kp: float
    def __init__(self, target: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., target_angle: _Optional[float] = ..., clockwise: bool = ..., orbit_radius: _Optional[float] = ..., rotate_velocity: _Optional[float] = ..., min_velocity: _Optional[float] = ..., approach_kp: _Optional[float] = ..., angle_kp: _Optional[float] = ...) -> None: ...

class RotateOnSelf(_message.Message):
    __slots__ = ("target_angle", "velocity", "kp")
    TARGET_ANGLE_FIELD_NUMBER: _ClassVar[int]
    VELOCITY_FIELD_NUMBER: _ClassVar[int]
    KP_FIELD_NUMBER: _ClassVar[int]
    target_angle: float
    velocity: _geometry_pb2.Point2Df
    kp: float
    def __init__(self, target_angle: _Optional[float] = ..., velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., kp: _Optional[float] = ...) -> None: ...

class GoToPoint(_message.Message):
    __slots__ = ("target", "target_angle", "moving_profile", "precision_to_target", "sync_rotate_with_linear_movement")
    TARGET_FIELD_NUMBER: _ClassVar[int]
    TARGET_ANGLE_FIELD_NUMBER: _ClassVar[int]
    MOVING_PROFILE_FIELD_NUMBER: _ClassVar[int]
    PRECISION_TO_TARGET_FIELD_NUMBER: _ClassVar[int]
    SYNC_ROTATE_WITH_LINEAR_MOVEMENT_FIELD_NUMBER: _ClassVar[int]
    target: _geometry_pb2.Point2Df
    target_angle: float
    moving_profile: MovingProfile
    precision_to_target: PrecisionToTarget
    sync_rotate_with_linear_movement: bool
    def __init__(self, target: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., target_angle: _Optional[float] = ..., moving_profile: _Optional[_Union[MovingProfile, str]] = ..., precision_to_target: _Optional[_Union[PrecisionToTarget, str]] = ..., sync_rotate_with_linear_movement: bool = ...) -> None: ...

class GoToPointWithTrajectory(_message.Message):
    __slots__ = ("go_to_point", "path_config")
    GO_TO_POINT_FIELD_NUMBER: _ClassVar[int]
    PATH_CONFIG_FIELD_NUMBER: _ClassVar[int]
    go_to_point: GoToPoint
    path_config: PathConfig
    def __init__(self, go_to_point: _Optional[_Union[GoToPoint, _Mapping]] = ..., path_config: _Optional[_Union[PathConfig, _Mapping]] = ...) -> None: ...

class PathConfig(_message.Message):
    __slots__ = ("target_velocity", "avoid_ball", "avoid_ball_placement", "avoid_ally_penalty_area", "avoid_enemy_penalty_area", "avoid_ally_robots", "avoid_enemy_robots", "ally_skipped", "enemy_skipped")
    TARGET_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    AVOID_BALL_FIELD_NUMBER: _ClassVar[int]
    AVOID_BALL_PLACEMENT_FIELD_NUMBER: _ClassVar[int]
    AVOID_ALLY_PENALTY_AREA_FIELD_NUMBER: _ClassVar[int]
    AVOID_ENEMY_PENALTY_AREA_FIELD_NUMBER: _ClassVar[int]
    AVOID_ALLY_ROBOTS_FIELD_NUMBER: _ClassVar[int]
    AVOID_ENEMY_ROBOTS_FIELD_NUMBER: _ClassVar[int]
    ALLY_SKIPPED_FIELD_NUMBER: _ClassVar[int]
    ENEMY_SKIPPED_FIELD_NUMBER: _ClassVar[int]
    target_velocity: _geometry_pb2.Point2Df
    avoid_ball: bool
    avoid_ball_placement: bool
    avoid_ally_penalty_area: bool
    avoid_enemy_penalty_area: bool
    avoid_ally_robots: bool
    avoid_enemy_robots: bool
    ally_skipped: _containers.RepeatedScalarFieldContainer[int]
    enemy_skipped: _containers.RepeatedScalarFieldContainer[int]
    def __init__(self, target_velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., avoid_ball: bool = ..., avoid_ball_placement: bool = ..., avoid_ally_penalty_area: bool = ..., avoid_enemy_penalty_area: bool = ..., avoid_ally_robots: bool = ..., avoid_enemy_robots: bool = ..., ally_skipped: _Optional[_Iterable[int]] = ..., enemy_skipped: _Optional[_Iterable[int]] = ...) -> None: ...
