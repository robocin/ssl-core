from protocols.common import robot_kick_pb2 as _robot_kick_pb2
from protocols.common import robot_dribbler_pb2 as _robot_dribbler_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class PeripheralActuation(_message.Message):
    __slots__ = ("kick_command", "robot_dribbler")
    KICK_COMMAND_FIELD_NUMBER: _ClassVar[int]
    ROBOT_DRIBBLER_FIELD_NUMBER: _ClassVar[int]
    kick_command: _robot_kick_pb2.RobotKick.KickCommand
    robot_dribbler: _robot_dribbler_pb2.RobotDribbler
    def __init__(self, kick_command: _Optional[_Union[_robot_kick_pb2.RobotKick.KickCommand, _Mapping]] = ..., robot_dribbler: _Optional[_Union[_robot_dribbler_pb2.RobotDribbler, _Mapping]] = ...) -> None: ...
