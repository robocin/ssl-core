from google.protobuf import any_pb2 as _any_pb2
from protocols.third_party.simulation import error_pb2 as _error_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class RobotFeedback(_message.Message):
    __slots__ = ("id", "dribbler_ball_contact", "custom")
    ID_FIELD_NUMBER: _ClassVar[int]
    DRIBBLER_BALL_CONTACT_FIELD_NUMBER: _ClassVar[int]
    CUSTOM_FIELD_NUMBER: _ClassVar[int]
    id: int
    dribbler_ball_contact: bool
    custom: _any_pb2.Any
    def __init__(self, id: _Optional[int] = ..., dribbler_ball_contact: bool = ..., custom: _Optional[_Union[_any_pb2.Any, _Mapping]] = ...) -> None: ...

class RobotControlResponse(_message.Message):
    __slots__ = ("errors", "feedback")
    ERRORS_FIELD_NUMBER: _ClassVar[int]
    FEEDBACK_FIELD_NUMBER: _ClassVar[int]
    errors: _containers.RepeatedCompositeFieldContainer[_error_pb2.SimulatorError]
    feedback: _containers.RepeatedCompositeFieldContainer[RobotFeedback]
    def __init__(self, errors: _Optional[_Iterable[_Union[_error_pb2.SimulatorError, _Mapping]]] = ..., feedback: _Optional[_Iterable[_Union[RobotFeedback, _Mapping]]] = ...) -> None: ...
