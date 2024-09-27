from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotId(_message.Message):
    __slots__ = ("color", "number")
    class Color(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        COLOR_UNSPECIFIED: _ClassVar[RobotId.Color]
        COLOR_YELLOW: _ClassVar[RobotId.Color]
        COLOR_BLUE: _ClassVar[RobotId.Color]
    COLOR_UNSPECIFIED: RobotId.Color
    COLOR_YELLOW: RobotId.Color
    COLOR_BLUE: RobotId.Color
    COLOR_FIELD_NUMBER: _ClassVar[int]
    NUMBER_FIELD_NUMBER: _ClassVar[int]
    color: RobotId.Color
    number: int
    def __init__(self, color: _Optional[_Union[RobotId.Color, str]] = ..., number: _Optional[int] = ...) -> None: ...
