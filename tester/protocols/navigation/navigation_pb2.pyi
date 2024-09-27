from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.common import geometry_pb2 as _geometry_pb2
from protocols.common import robot_pose_pb2 as _robot_pose_pb2
from protocols.navigation import motion_pb2 as _motion_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Navigation(_message.Message):
    __slots__ = ("id", "timestamp", "forward_velocity", "left_velocity", "angular_velocity", "custom_command", "sequence_number", "output_global_linear_velocity", "go_to_point", "rotate_in_point", "rotate_on_self", "robot_pose")
    ID_FIELD_NUMBER: _ClassVar[int]
    TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    FORWARD_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    LEFT_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    ANGULAR_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    CUSTOM_COMMAND_FIELD_NUMBER: _ClassVar[int]
    SEQUENCE_NUMBER_FIELD_NUMBER: _ClassVar[int]
    OUTPUT_GLOBAL_LINEAR_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    GO_TO_POINT_FIELD_NUMBER: _ClassVar[int]
    ROTATE_IN_POINT_FIELD_NUMBER: _ClassVar[int]
    ROTATE_ON_SELF_FIELD_NUMBER: _ClassVar[int]
    ROBOT_POSE_FIELD_NUMBER: _ClassVar[int]
    id: int
    timestamp: _timestamp_pb2.Timestamp
    forward_velocity: float
    left_velocity: float
    angular_velocity: float
    custom_command: int
    sequence_number: int
    output_global_linear_velocity: _geometry_pb2.Point2Df
    go_to_point: _motion_pb2.GoToPoint
    rotate_in_point: _motion_pb2.RotateInPoint
    rotate_on_self: _motion_pb2.RotateOnSelf
    robot_pose: _robot_pose_pb2.RobotPose
    def __init__(self, id: _Optional[int] = ..., timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., forward_velocity: _Optional[float] = ..., left_velocity: _Optional[float] = ..., angular_velocity: _Optional[float] = ..., custom_command: _Optional[int] = ..., sequence_number: _Optional[int] = ..., output_global_linear_velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., go_to_point: _Optional[_Union[_motion_pb2.GoToPoint, _Mapping]] = ..., rotate_in_point: _Optional[_Union[_motion_pb2.RotateInPoint, _Mapping]] = ..., rotate_on_self: _Optional[_Union[_motion_pb2.RotateOnSelf, _Mapping]] = ..., robot_pose: _Optional[_Union[_robot_pose_pb2.RobotPose, _Mapping]] = ...) -> None: ...
