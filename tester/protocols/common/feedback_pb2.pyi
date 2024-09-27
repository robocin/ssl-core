from protocols.common import robot_id_pb2 as _robot_id_pb2
from protocols.common import robot_pose_pb2 as _robot_pose_pb2
from protocols.common import robot_kick_pb2 as _robot_kick_pb2
from protocols.common import robot_velocity_pb2 as _robot_velocity_pb2
from protocols.common import robot_motor_pb2 as _robot_motor_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Feedback(_message.Message):
    __slots__ = ("telemetry", "pose")
    class Telemetry(_message.Message):
        __slots__ = ("robot_id", "robot_velocity", "robot_motor", "kick_info")
        ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
        ROBOT_VELOCITY_FIELD_NUMBER: _ClassVar[int]
        ROBOT_MOTOR_FIELD_NUMBER: _ClassVar[int]
        KICK_INFO_FIELD_NUMBER: _ClassVar[int]
        robot_id: _robot_id_pb2.RobotId
        robot_velocity: _robot_velocity_pb2.RobotVelocity
        robot_motor: _robot_motor_pb2.RobotMotor
        kick_info: _robot_kick_pb2.RobotKick.KickInfo
        def __init__(self, robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., robot_velocity: _Optional[_Union[_robot_velocity_pb2.RobotVelocity, _Mapping]] = ..., robot_motor: _Optional[_Union[_robot_motor_pb2.RobotMotor, _Mapping]] = ..., kick_info: _Optional[_Union[_robot_kick_pb2.RobotKick.KickInfo, _Mapping]] = ...) -> None: ...
    TELEMETRY_FIELD_NUMBER: _ClassVar[int]
    POSE_FIELD_NUMBER: _ClassVar[int]
    telemetry: Feedback.Telemetry
    pose: _robot_pose_pb2.RobotPose
    def __init__(self, telemetry: _Optional[_Union[Feedback.Telemetry, _Mapping]] = ..., pose: _Optional[_Union[_robot_pose_pb2.RobotPose, _Mapping]] = ...) -> None: ...
