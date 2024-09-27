from google.protobuf import any_pb2 as _any_pb2
from protocols.third_party.detection import geometry_pb2 as _geometry_pb2
from protocols.third_party.game_controller import common_pb2 as _common_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotLimits(_message.Message):
    __slots__ = ("acc_speedup_absolute_max", "acc_speedup_angular_max", "acc_brake_absolute_max", "acc_brake_angular_max", "vel_absolute_max", "vel_angular_max")
    ACC_SPEEDUP_ABSOLUTE_MAX_FIELD_NUMBER: _ClassVar[int]
    ACC_SPEEDUP_ANGULAR_MAX_FIELD_NUMBER: _ClassVar[int]
    ACC_BRAKE_ABSOLUTE_MAX_FIELD_NUMBER: _ClassVar[int]
    ACC_BRAKE_ANGULAR_MAX_FIELD_NUMBER: _ClassVar[int]
    VEL_ABSOLUTE_MAX_FIELD_NUMBER: _ClassVar[int]
    VEL_ANGULAR_MAX_FIELD_NUMBER: _ClassVar[int]
    acc_speedup_absolute_max: float
    acc_speedup_angular_max: float
    acc_brake_absolute_max: float
    acc_brake_angular_max: float
    vel_absolute_max: float
    vel_angular_max: float
    def __init__(self, acc_speedup_absolute_max: _Optional[float] = ..., acc_speedup_angular_max: _Optional[float] = ..., acc_brake_absolute_max: _Optional[float] = ..., acc_brake_angular_max: _Optional[float] = ..., vel_absolute_max: _Optional[float] = ..., vel_angular_max: _Optional[float] = ...) -> None: ...

class RobotWheelAngles(_message.Message):
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

class RobotSpecs(_message.Message):
    __slots__ = ("id", "radius", "height", "mass", "max_linear_kick_speed", "max_chip_kick_speed", "center_to_dribbler", "limits", "wheel_angles", "custom")
    ID_FIELD_NUMBER: _ClassVar[int]
    RADIUS_FIELD_NUMBER: _ClassVar[int]
    HEIGHT_FIELD_NUMBER: _ClassVar[int]
    MASS_FIELD_NUMBER: _ClassVar[int]
    MAX_LINEAR_KICK_SPEED_FIELD_NUMBER: _ClassVar[int]
    MAX_CHIP_KICK_SPEED_FIELD_NUMBER: _ClassVar[int]
    CENTER_TO_DRIBBLER_FIELD_NUMBER: _ClassVar[int]
    LIMITS_FIELD_NUMBER: _ClassVar[int]
    WHEEL_ANGLES_FIELD_NUMBER: _ClassVar[int]
    CUSTOM_FIELD_NUMBER: _ClassVar[int]
    id: _common_pb2.RobotId
    radius: float
    height: float
    mass: float
    max_linear_kick_speed: float
    max_chip_kick_speed: float
    center_to_dribbler: float
    limits: RobotLimits
    wheel_angles: RobotWheelAngles
    custom: _containers.RepeatedCompositeFieldContainer[_any_pb2.Any]
    def __init__(self, id: _Optional[_Union[_common_pb2.RobotId, _Mapping]] = ..., radius: _Optional[float] = ..., height: _Optional[float] = ..., mass: _Optional[float] = ..., max_linear_kick_speed: _Optional[float] = ..., max_chip_kick_speed: _Optional[float] = ..., center_to_dribbler: _Optional[float] = ..., limits: _Optional[_Union[RobotLimits, _Mapping]] = ..., wheel_angles: _Optional[_Union[RobotWheelAngles, _Mapping]] = ..., custom: _Optional[_Iterable[_Union[_any_pb2.Any, _Mapping]]] = ...) -> None: ...

class RealismConfig(_message.Message):
    __slots__ = ("custom",)
    CUSTOM_FIELD_NUMBER: _ClassVar[int]
    custom: _containers.RepeatedCompositeFieldContainer[_any_pb2.Any]
    def __init__(self, custom: _Optional[_Iterable[_Union[_any_pb2.Any, _Mapping]]] = ...) -> None: ...

class SimulatorConfig(_message.Message):
    __slots__ = ("geometry", "robot_specs", "realism_config", "vision_port")
    GEOMETRY_FIELD_NUMBER: _ClassVar[int]
    ROBOT_SPECS_FIELD_NUMBER: _ClassVar[int]
    REALISM_CONFIG_FIELD_NUMBER: _ClassVar[int]
    VISION_PORT_FIELD_NUMBER: _ClassVar[int]
    geometry: _geometry_pb2.SSL_GeometryData
    robot_specs: _containers.RepeatedCompositeFieldContainer[RobotSpecs]
    realism_config: RealismConfig
    vision_port: int
    def __init__(self, geometry: _Optional[_Union[_geometry_pb2.SSL_GeometryData, _Mapping]] = ..., robot_specs: _Optional[_Iterable[_Union[RobotSpecs, _Mapping]]] = ..., realism_config: _Optional[_Union[RealismConfig, _Mapping]] = ..., vision_port: _Optional[int] = ...) -> None: ...
