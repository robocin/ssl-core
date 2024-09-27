from protocols.common import geometry_pb2 as _geometry_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotVelocity(_message.Message):
    __slots__ = ("velocity", "angular_velocity")
    VELOCITY_FIELD_NUMBER: _ClassVar[int]
    ANGULAR_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    velocity: _geometry_pb2.Point2Df
    angular_velocity: float
    def __init__(self, velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angular_velocity: _Optional[float] = ...) -> None: ...
