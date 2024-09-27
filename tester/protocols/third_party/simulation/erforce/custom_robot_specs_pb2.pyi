from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class RobotSpecErForce(_message.Message):
    __slots__ = ("shoot_radius", "dribbler_width")
    SHOOT_RADIUS_FIELD_NUMBER: _ClassVar[int]
    DRIBBLER_WIDTH_FIELD_NUMBER: _ClassVar[int]
    shoot_radius: float
    dribbler_width: float
    def __init__(self, shoot_radius: _Optional[float] = ..., dribbler_width: _Optional[float] = ...) -> None: ...
