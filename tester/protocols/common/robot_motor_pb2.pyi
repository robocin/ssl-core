from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotMotor(_message.Message):
    __slots__ = ("motor",)
    class Motor(_message.Message):
        __slots__ = ("motor_id", "motor_speed", "motor_current")
        MOTOR_ID_FIELD_NUMBER: _ClassVar[int]
        MOTOR_SPEED_FIELD_NUMBER: _ClassVar[int]
        MOTOR_CURRENT_FIELD_NUMBER: _ClassVar[int]
        motor_id: int
        motor_speed: float
        motor_current: float
        def __init__(self, motor_id: _Optional[int] = ..., motor_speed: _Optional[float] = ..., motor_current: _Optional[float] = ...) -> None: ...
    MOTOR_FIELD_NUMBER: _ClassVar[int]
    motor: _containers.RepeatedCompositeFieldContainer[RobotMotor.Motor]
    def __init__(self, motor: _Optional[_Iterable[_Union[RobotMotor.Motor, _Mapping]]] = ...) -> None: ...
