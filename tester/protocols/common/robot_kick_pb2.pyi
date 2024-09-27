from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotKick(_message.Message):
    __slots__ = ("kick_command", "kick_info")
    class KickCommand(_message.Message):
        __slots__ = ("kick_strength", "is_front", "is_chip", "charge_capacitor", "is_bypass_ir")
        KICK_STRENGTH_FIELD_NUMBER: _ClassVar[int]
        IS_FRONT_FIELD_NUMBER: _ClassVar[int]
        IS_CHIP_FIELD_NUMBER: _ClassVar[int]
        CHARGE_CAPACITOR_FIELD_NUMBER: _ClassVar[int]
        IS_BYPASS_IR_FIELD_NUMBER: _ClassVar[int]
        kick_strength: float
        is_front: bool
        is_chip: bool
        charge_capacitor: bool
        is_bypass_ir: bool
        def __init__(self, kick_strength: _Optional[float] = ..., is_front: bool = ..., is_chip: bool = ..., charge_capacitor: bool = ..., is_bypass_ir: bool = ...) -> None: ...
    class KickInfo(_message.Message):
        __slots__ = ("capacitor_charge", "is_ball_detected")
        CAPACITOR_CHARGE_FIELD_NUMBER: _ClassVar[int]
        IS_BALL_DETECTED_FIELD_NUMBER: _ClassVar[int]
        capacitor_charge: float
        is_ball_detected: bool
        def __init__(self, capacitor_charge: _Optional[float] = ..., is_ball_detected: bool = ...) -> None: ...
    KICK_COMMAND_FIELD_NUMBER: _ClassVar[int]
    KICK_INFO_FIELD_NUMBER: _ClassVar[int]
    kick_command: RobotKick.KickCommand
    kick_info: RobotKick.KickInfo
    def __init__(self, kick_command: _Optional[_Union[RobotKick.KickCommand, _Mapping]] = ..., kick_info: _Optional[_Union[RobotKick.KickInfo, _Mapping]] = ...) -> None: ...
