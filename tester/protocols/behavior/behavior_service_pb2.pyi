from protocols.common import geometry_pb2 as _geometry_pb2
from protocols.common import robot_id_pb2 as _robot_id_pb2
from protocols.common import peripheral_actuation_pb2 as _peripheral_actuation_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Motion(_message.Message):
    __slots__ = ("target", "obstacles", "peripheral_actuation")
    TARGET_FIELD_NUMBER: _ClassVar[int]
    OBSTACLES_FIELD_NUMBER: _ClassVar[int]
    PERIPHERAL_ACTUATION_FIELD_NUMBER: _ClassVar[int]
    target: Target
    obstacles: Obstacles
    peripheral_actuation: _peripheral_actuation_pb2.PeripheralActuation
    def __init__(self, target: _Optional[_Union[Target, _Mapping]] = ..., obstacles: _Optional[_Union[Obstacles, _Mapping]] = ..., peripheral_actuation: _Optional[_Union[_peripheral_actuation_pb2.PeripheralActuation, _Mapping]] = ...) -> None: ...

class Target(_message.Message):
    __slots__ = ("position", "angle", "velocity")
    POSITION_FIELD_NUMBER: _ClassVar[int]
    ANGLE_FIELD_NUMBER: _ClassVar[int]
    VELOCITY_FIELD_NUMBER: _ClassVar[int]
    position: _geometry_pb2.Point2Df
    angle: float
    velocity: _geometry_pb2.Point2Df
    def __init__(self, position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angle: _Optional[float] = ..., velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...

class Obstacles(_message.Message):
    __slots__ = ("ball", "robots", "left_penalty_area", "right_penalty_area", "field_boundary", "left_goal_post", "right_goal_post")
    BALL_FIELD_NUMBER: _ClassVar[int]
    ROBOTS_FIELD_NUMBER: _ClassVar[int]
    LEFT_PENALTY_AREA_FIELD_NUMBER: _ClassVar[int]
    RIGHT_PENALTY_AREA_FIELD_NUMBER: _ClassVar[int]
    FIELD_BOUNDARY_FIELD_NUMBER: _ClassVar[int]
    LEFT_GOAL_POST_FIELD_NUMBER: _ClassVar[int]
    RIGHT_GOAL_POST_FIELD_NUMBER: _ClassVar[int]
    ball: bool
    robots: _containers.RepeatedCompositeFieldContainer[_robot_id_pb2.RobotId]
    left_penalty_area: bool
    right_penalty_area: bool
    field_boundary: bool
    left_goal_post: bool
    right_goal_post: bool
    def __init__(self, ball: bool = ..., robots: _Optional[_Iterable[_Union[_robot_id_pb2.RobotId, _Mapping]]] = ..., left_penalty_area: bool = ..., right_penalty_area: bool = ..., field_boundary: bool = ..., left_goal_post: bool = ..., right_goal_post: bool = ...) -> None: ...
