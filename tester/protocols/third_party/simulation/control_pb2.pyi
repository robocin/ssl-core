from protocols.third_party.game_controller import common_pb2 as _common_pb2
from protocols.third_party.simulation import config_pb2 as _config_pb2
from protocols.third_party.simulation import error_pb2 as _error_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class TeleportBall(_message.Message):
    __slots__ = ("x", "y", "z", "vx", "vy", "vz", "teleport_safely", "roll", "by_force")
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    Z_FIELD_NUMBER: _ClassVar[int]
    VX_FIELD_NUMBER: _ClassVar[int]
    VY_FIELD_NUMBER: _ClassVar[int]
    VZ_FIELD_NUMBER: _ClassVar[int]
    TELEPORT_SAFELY_FIELD_NUMBER: _ClassVar[int]
    ROLL_FIELD_NUMBER: _ClassVar[int]
    BY_FORCE_FIELD_NUMBER: _ClassVar[int]
    x: float
    y: float
    z: float
    vx: float
    vy: float
    vz: float
    teleport_safely: bool
    roll: bool
    by_force: bool
    def __init__(self, x: _Optional[float] = ..., y: _Optional[float] = ..., z: _Optional[float] = ..., vx: _Optional[float] = ..., vy: _Optional[float] = ..., vz: _Optional[float] = ..., teleport_safely: bool = ..., roll: bool = ..., by_force: bool = ...) -> None: ...

class TeleportRobot(_message.Message):
    __slots__ = ("id", "x", "y", "orientation", "v_x", "v_y", "v_angular", "present", "by_force")
    ID_FIELD_NUMBER: _ClassVar[int]
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    ORIENTATION_FIELD_NUMBER: _ClassVar[int]
    V_X_FIELD_NUMBER: _ClassVar[int]
    V_Y_FIELD_NUMBER: _ClassVar[int]
    V_ANGULAR_FIELD_NUMBER: _ClassVar[int]
    PRESENT_FIELD_NUMBER: _ClassVar[int]
    BY_FORCE_FIELD_NUMBER: _ClassVar[int]
    id: _common_pb2.RobotId
    x: float
    y: float
    orientation: float
    v_x: float
    v_y: float
    v_angular: float
    present: bool
    by_force: bool
    def __init__(self, id: _Optional[_Union[_common_pb2.RobotId, _Mapping]] = ..., x: _Optional[float] = ..., y: _Optional[float] = ..., orientation: _Optional[float] = ..., v_x: _Optional[float] = ..., v_y: _Optional[float] = ..., v_angular: _Optional[float] = ..., present: bool = ..., by_force: bool = ...) -> None: ...

class SimulatorControl(_message.Message):
    __slots__ = ("teleport_ball", "teleport_robot", "simulation_speed")
    TELEPORT_BALL_FIELD_NUMBER: _ClassVar[int]
    TELEPORT_ROBOT_FIELD_NUMBER: _ClassVar[int]
    SIMULATION_SPEED_FIELD_NUMBER: _ClassVar[int]
    teleport_ball: TeleportBall
    teleport_robot: _containers.RepeatedCompositeFieldContainer[TeleportRobot]
    simulation_speed: float
    def __init__(self, teleport_ball: _Optional[_Union[TeleportBall, _Mapping]] = ..., teleport_robot: _Optional[_Iterable[_Union[TeleportRobot, _Mapping]]] = ..., simulation_speed: _Optional[float] = ...) -> None: ...

class SimulatorCommand(_message.Message):
    __slots__ = ("control", "config")
    CONTROL_FIELD_NUMBER: _ClassVar[int]
    CONFIG_FIELD_NUMBER: _ClassVar[int]
    control: SimulatorControl
    config: _config_pb2.SimulatorConfig
    def __init__(self, control: _Optional[_Union[SimulatorControl, _Mapping]] = ..., config: _Optional[_Union[_config_pb2.SimulatorConfig, _Mapping]] = ...) -> None: ...

class SimulatorResponse(_message.Message):
    __slots__ = ("errors",)
    ERRORS_FIELD_NUMBER: _ClassVar[int]
    errors: _containers.RepeatedCompositeFieldContainer[_error_pb2.SimulatorError]
    def __init__(self, errors: _Optional[_Iterable[_Union[_error_pb2.SimulatorError, _Mapping]]] = ...) -> None: ...
