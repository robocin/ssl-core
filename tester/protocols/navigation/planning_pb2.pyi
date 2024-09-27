from protocols.navigation import motion_pb2 as _motion_pb2
from protocols.common import peripheral_actuation_pb2 as _peripheral_actuation_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Planning(_message.Message):
    __slots__ = ("discretized_path", "go_to_point", "rotate_in_point", "rotate_on_self", "peripheral_actuation")
    DISCRETIZED_PATH_FIELD_NUMBER: _ClassVar[int]
    GO_TO_POINT_FIELD_NUMBER: _ClassVar[int]
    ROTATE_IN_POINT_FIELD_NUMBER: _ClassVar[int]
    ROTATE_ON_SELF_FIELD_NUMBER: _ClassVar[int]
    PERIPHERAL_ACTUATION_FIELD_NUMBER: _ClassVar[int]
    discretized_path: _motion_pb2.DiscretizedPath
    go_to_point: _motion_pb2.GoToPoint
    rotate_in_point: _motion_pb2.RotateInPoint
    rotate_on_self: _motion_pb2.RotateOnSelf
    peripheral_actuation: _peripheral_actuation_pb2.PeripheralActuation
    def __init__(self, discretized_path: _Optional[_Union[_motion_pb2.DiscretizedPath, _Mapping]] = ..., go_to_point: _Optional[_Union[_motion_pb2.GoToPoint, _Mapping]] = ..., rotate_in_point: _Optional[_Union[_motion_pb2.RotateInPoint, _Mapping]] = ..., rotate_on_self: _Optional[_Union[_motion_pb2.RotateOnSelf, _Mapping]] = ..., peripheral_actuation: _Optional[_Union[_peripheral_actuation_pb2.PeripheralActuation, _Mapping]] = ...) -> None: ...
