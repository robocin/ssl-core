from protocols.common import geometry_pb2 as _geometry_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotPose(_message.Message):
    __slots__ = ("position", "orientation")
    POSITION_FIELD_NUMBER: _ClassVar[int]
    ORIENTATION_FIELD_NUMBER: _ClassVar[int]
    position: _geometry_pb2.Point2Df
    orientation: float
    def __init__(self, position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., orientation: _Optional[float] = ...) -> None: ...
