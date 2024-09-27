from protocols.common import geometry_pb2 as _geometry_pb2
from protocols.common import robot_id_pb2 as _robot_id_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RawDetection(_message.Message):
    __slots__ = ("cameras",)
    class Camera(_message.Message):
        __slots__ = ("camera_id", "serial_id", "balls", "robots")
        class Ball(_message.Message):
            __slots__ = ("confidence", "position")
            CONFIDENCE_FIELD_NUMBER: _ClassVar[int]
            POSITION_FIELD_NUMBER: _ClassVar[int]
            confidence: float
            position: _geometry_pb2.Point3Df
            def __init__(self, confidence: _Optional[float] = ..., position: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ...) -> None: ...
        class Robot(_message.Message):
            __slots__ = ("robot_id", "confidence", "position", "angle", "height")
            ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
            CONFIDENCE_FIELD_NUMBER: _ClassVar[int]
            POSITION_FIELD_NUMBER: _ClassVar[int]
            ANGLE_FIELD_NUMBER: _ClassVar[int]
            HEIGHT_FIELD_NUMBER: _ClassVar[int]
            robot_id: _robot_id_pb2.RobotId
            confidence: float
            position: _geometry_pb2.Point2Df
            angle: float
            height: float
            def __init__(self, robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., confidence: _Optional[float] = ..., position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angle: _Optional[float] = ..., height: _Optional[float] = ...) -> None: ...
        CAMERA_ID_FIELD_NUMBER: _ClassVar[int]
        SERIAL_ID_FIELD_NUMBER: _ClassVar[int]
        BALLS_FIELD_NUMBER: _ClassVar[int]
        ROBOTS_FIELD_NUMBER: _ClassVar[int]
        camera_id: int
        serial_id: int
        balls: _containers.RepeatedCompositeFieldContainer[RawDetection.Camera.Ball]
        robots: _containers.RepeatedCompositeFieldContainer[RawDetection.Camera.Robot]
        def __init__(self, camera_id: _Optional[int] = ..., serial_id: _Optional[int] = ..., balls: _Optional[_Iterable[_Union[RawDetection.Camera.Ball, _Mapping]]] = ..., robots: _Optional[_Iterable[_Union[RawDetection.Camera.Robot, _Mapping]]] = ...) -> None: ...
    CAMERAS_FIELD_NUMBER: _ClassVar[int]
    cameras: _containers.RepeatedCompositeFieldContainer[RawDetection.Camera]
    def __init__(self, cameras: _Optional[_Iterable[_Union[RawDetection.Camera, _Mapping]]] = ...) -> None: ...
