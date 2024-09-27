from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotDribbler(_message.Message):
    __slots__ = ("dribbler_command", "dribbler_info")
    class DribblerCommand(_message.Message):
        __slots__ = ("dribbler_speed", "is_active")
        DRIBBLER_SPEED_FIELD_NUMBER: _ClassVar[int]
        IS_ACTIVE_FIELD_NUMBER: _ClassVar[int]
        dribbler_speed: float
        is_active: bool
        def __init__(self, dribbler_speed: _Optional[float] = ..., is_active: bool = ...) -> None: ...
    class DribblerInfo(_message.Message):
        __slots__ = ("dribbler_speed", "dribbler_current", "is_ball_detected")
        DRIBBLER_SPEED_FIELD_NUMBER: _ClassVar[int]
        DRIBBLER_CURRENT_FIELD_NUMBER: _ClassVar[int]
        IS_BALL_DETECTED_FIELD_NUMBER: _ClassVar[int]
        dribbler_speed: float
        dribbler_current: float
        is_ball_detected: bool
        def __init__(self, dribbler_speed: _Optional[float] = ..., dribbler_current: _Optional[float] = ..., is_ball_detected: bool = ...) -> None: ...
    DRIBBLER_COMMAND_FIELD_NUMBER: _ClassVar[int]
    DRIBBLER_INFO_FIELD_NUMBER: _ClassVar[int]
    dribbler_command: RobotDribbler.DribblerCommand
    dribbler_info: RobotDribbler.DribblerInfo
    def __init__(self, dribbler_command: _Optional[_Union[RobotDribbler.DribblerCommand, _Mapping]] = ..., dribbler_info: _Optional[_Union[RobotDribbler.DribblerInfo, _Mapping]] = ...) -> None: ...
