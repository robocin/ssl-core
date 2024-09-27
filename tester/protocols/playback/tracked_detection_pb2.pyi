from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.common import geometry_pb2 as _geometry_pb2
from protocols.common import robot_id_pb2 as _robot_id_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class TrackedDetection(_message.Message):
    __slots__ = ("source_unique_id", "source_software_name", "source_capabilities", "serial_id", "balls", "robots")
    class SourceCapability(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        SOURCE_CAPABILITY_UNSPECIFIED: _ClassVar[TrackedDetection.SourceCapability]
        SOURCE_CAPABILITY_DETECT_FLYING_BALLS: _ClassVar[TrackedDetection.SourceCapability]
        SOURCE_CAPABILITY_DETECT_MULTIPLE_BALLS: _ClassVar[TrackedDetection.SourceCapability]
        SOURCE_CAPABILITY_DETECT_KICKED_BALLS: _ClassVar[TrackedDetection.SourceCapability]
    SOURCE_CAPABILITY_UNSPECIFIED: TrackedDetection.SourceCapability
    SOURCE_CAPABILITY_DETECT_FLYING_BALLS: TrackedDetection.SourceCapability
    SOURCE_CAPABILITY_DETECT_MULTIPLE_BALLS: TrackedDetection.SourceCapability
    SOURCE_CAPABILITY_DETECT_KICKED_BALLS: TrackedDetection.SourceCapability
    class Ball(_message.Message):
        __slots__ = ("confidence", "position", "velocity", "kick_information")
        class KickInformation(_message.Message):
            __slots__ = ("robot_id", "start_position", "start_velocity", "start_timestamp", "predicted_stop_position", "predicted_stop_timestamp")
            ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
            START_POSITION_FIELD_NUMBER: _ClassVar[int]
            START_VELOCITY_FIELD_NUMBER: _ClassVar[int]
            START_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
            PREDICTED_STOP_POSITION_FIELD_NUMBER: _ClassVar[int]
            PREDICTED_STOP_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
            robot_id: _robot_id_pb2.RobotId
            start_position: _geometry_pb2.Point2Df
            start_velocity: _geometry_pb2.Point3Df
            start_timestamp: _timestamp_pb2.Timestamp
            predicted_stop_position: _geometry_pb2.Point2Df
            predicted_stop_timestamp: _timestamp_pb2.Timestamp
            def __init__(self, robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., start_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., start_velocity: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ..., start_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., predicted_stop_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., predicted_stop_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ...) -> None: ...
        CONFIDENCE_FIELD_NUMBER: _ClassVar[int]
        POSITION_FIELD_NUMBER: _ClassVar[int]
        VELOCITY_FIELD_NUMBER: _ClassVar[int]
        KICK_INFORMATION_FIELD_NUMBER: _ClassVar[int]
        confidence: float
        position: _geometry_pb2.Point3Df
        velocity: _geometry_pb2.Point3Df
        kick_information: TrackedDetection.Ball.KickInformation
        def __init__(self, confidence: _Optional[float] = ..., position: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ..., velocity: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ..., kick_information: _Optional[_Union[TrackedDetection.Ball.KickInformation, _Mapping]] = ...) -> None: ...
    class Robot(_message.Message):
        __slots__ = ("robot_id", "confidence", "position", "angle", "velocity", "angular_velocity")
        ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
        CONFIDENCE_FIELD_NUMBER: _ClassVar[int]
        POSITION_FIELD_NUMBER: _ClassVar[int]
        ANGLE_FIELD_NUMBER: _ClassVar[int]
        VELOCITY_FIELD_NUMBER: _ClassVar[int]
        ANGULAR_VELOCITY_FIELD_NUMBER: _ClassVar[int]
        robot_id: _robot_id_pb2.RobotId
        confidence: float
        position: _geometry_pb2.Point2Df
        angle: float
        velocity: _geometry_pb2.Point2Df
        angular_velocity: float
        def __init__(self, robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., confidence: _Optional[float] = ..., position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angle: _Optional[float] = ..., velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angular_velocity: _Optional[float] = ...) -> None: ...
    SOURCE_UNIQUE_ID_FIELD_NUMBER: _ClassVar[int]
    SOURCE_SOFTWARE_NAME_FIELD_NUMBER: _ClassVar[int]
    SOURCE_CAPABILITIES_FIELD_NUMBER: _ClassVar[int]
    SERIAL_ID_FIELD_NUMBER: _ClassVar[int]
    BALLS_FIELD_NUMBER: _ClassVar[int]
    ROBOTS_FIELD_NUMBER: _ClassVar[int]
    source_unique_id: str
    source_software_name: str
    source_capabilities: _containers.RepeatedScalarFieldContainer[TrackedDetection.SourceCapability]
    serial_id: int
    balls: _containers.RepeatedCompositeFieldContainer[TrackedDetection.Ball]
    robots: _containers.RepeatedCompositeFieldContainer[TrackedDetection.Robot]
    def __init__(self, source_unique_id: _Optional[str] = ..., source_software_name: _Optional[str] = ..., source_capabilities: _Optional[_Iterable[_Union[TrackedDetection.SourceCapability, str]]] = ..., serial_id: _Optional[int] = ..., balls: _Optional[_Iterable[_Union[TrackedDetection.Ball, _Mapping]]] = ..., robots: _Optional[_Iterable[_Union[TrackedDetection.Robot, _Mapping]]] = ...) -> None: ...
