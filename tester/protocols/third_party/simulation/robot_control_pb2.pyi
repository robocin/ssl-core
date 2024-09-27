from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotCommand(_message.Message):
    __slots__ = ("id", "move_command", "kick_speed", "kick_angle", "dribbler_speed")
    ID_FIELD_NUMBER: _ClassVar[int]
    MOVE_COMMAND_FIELD_NUMBER: _ClassVar[int]
    KICK_SPEED_FIELD_NUMBER: _ClassVar[int]
    KICK_ANGLE_FIELD_NUMBER: _ClassVar[int]
    DRIBBLER_SPEED_FIELD_NUMBER: _ClassVar[int]
    id: int
    move_command: RobotMoveCommand
    kick_speed: float
    kick_angle: float
    dribbler_speed: float
    def __init__(self, id: _Optional[int] = ..., move_command: _Optional[_Union[RobotMoveCommand, _Mapping]] = ..., kick_speed: _Optional[float] = ..., kick_angle: _Optional[float] = ..., dribbler_speed: _Optional[float] = ...) -> None: ...

class RobotMoveCommand(_message.Message):
    __slots__ = ("wheel_velocity", "local_velocity", "global_velocity")
    WHEEL_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    LOCAL_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    GLOBAL_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    wheel_velocity: MoveWheelVelocity
    local_velocity: MoveLocalVelocity
    global_velocity: MoveGlobalVelocity
    def __init__(self, wheel_velocity: _Optional[_Union[MoveWheelVelocity, _Mapping]] = ..., local_velocity: _Optional[_Union[MoveLocalVelocity, _Mapping]] = ..., global_velocity: _Optional[_Union[MoveGlobalVelocity, _Mapping]] = ...) -> None: ...

class MoveWheelVelocity(_message.Message):
    __slots__ = ("front_right", "back_right", "back_left", "front_left")
    FRONT_RIGHT_FIELD_NUMBER: _ClassVar[int]
    BACK_RIGHT_FIELD_NUMBER: _ClassVar[int]
    BACK_LEFT_FIELD_NUMBER: _ClassVar[int]
    FRONT_LEFT_FIELD_NUMBER: _ClassVar[int]
    front_right: float
    back_right: float
    back_left: float
    front_left: float
    def __init__(self, front_right: _Optional[float] = ..., back_right: _Optional[float] = ..., back_left: _Optional[float] = ..., front_left: _Optional[float] = ...) -> None: ...

class MoveLocalVelocity(_message.Message):
    __slots__ = ("forward", "left", "angular")
    FORWARD_FIELD_NUMBER: _ClassVar[int]
    LEFT_FIELD_NUMBER: _ClassVar[int]
    ANGULAR_FIELD_NUMBER: _ClassVar[int]
    forward: float
    left: float
    angular: float
    def __init__(self, forward: _Optional[float] = ..., left: _Optional[float] = ..., angular: _Optional[float] = ...) -> None: ...

class MoveGlobalVelocity(_message.Message):
    __slots__ = ("x", "y", "angular")
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    ANGULAR_FIELD_NUMBER: _ClassVar[int]
    x: float
    y: float
    angular: float
    def __init__(self, x: _Optional[float] = ..., y: _Optional[float] = ..., angular: _Optional[float] = ...) -> None: ...

class RobotControl(_message.Message):
    __slots__ = ("robot_commands",)
    ROBOT_COMMANDS_FIELD_NUMBER: _ClassVar[int]
    robot_commands: _containers.RepeatedCompositeFieldContainer[RobotCommand]
    def __init__(self, robot_commands: _Optional[_Iterable[_Union[RobotCommand, _Mapping]]] = ...) -> None: ...
