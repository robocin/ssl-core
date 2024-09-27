from protocols.common import peripheral_actuation_pb2 as _peripheral_actuation_pb2
from protocols.navigation import motion_pb2 as _motion_pb2
from protocols.navigation import navigation_pb2 as _navigation_pb2
from protocols.navigation import planning_pb2 as _planning_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Behavior(_message.Message):
    __slots__ = ("motion", "planning", "navigation")
    MOTION_FIELD_NUMBER: _ClassVar[int]
    PLANNING_FIELD_NUMBER: _ClassVar[int]
    NAVIGATION_FIELD_NUMBER: _ClassVar[int]
    motion: Motion
    planning: _planning_pb2.Planning
    navigation: _navigation_pb2.Navigation
    def __init__(self, motion: _Optional[_Union[Motion, _Mapping]] = ..., planning: _Optional[_Union[_planning_pb2.Planning, _Mapping]] = ..., navigation: _Optional[_Union[_navigation_pb2.Navigation, _Mapping]] = ...) -> None: ...

class Motion(_message.Message):
    __slots__ = ("go_to_point", "go_to_point_with_trajectory", "rotate_in_point", "rotate_on_self", "peripheral_actuation")
    GO_TO_POINT_FIELD_NUMBER: _ClassVar[int]
    GO_TO_POINT_WITH_TRAJECTORY_FIELD_NUMBER: _ClassVar[int]
    ROTATE_IN_POINT_FIELD_NUMBER: _ClassVar[int]
    ROTATE_ON_SELF_FIELD_NUMBER: _ClassVar[int]
    PERIPHERAL_ACTUATION_FIELD_NUMBER: _ClassVar[int]
    go_to_point: _motion_pb2.GoToPoint
    go_to_point_with_trajectory: _motion_pb2.GoToPointWithTrajectory
    rotate_in_point: _motion_pb2.RotateInPoint
    rotate_on_self: _motion_pb2.RotateOnSelf
    peripheral_actuation: _peripheral_actuation_pb2.PeripheralActuation
    def __init__(self, go_to_point: _Optional[_Union[_motion_pb2.GoToPoint, _Mapping]] = ..., go_to_point_with_trajectory: _Optional[_Union[_motion_pb2.GoToPointWithTrajectory, _Mapping]] = ..., rotate_in_point: _Optional[_Union[_motion_pb2.RotateInPoint, _Mapping]] = ..., rotate_on_self: _Optional[_Union[_motion_pb2.RotateOnSelf, _Mapping]] = ..., peripheral_actuation: _Optional[_Union[_peripheral_actuation_pb2.PeripheralActuation, _Mapping]] = ...) -> None: ...
