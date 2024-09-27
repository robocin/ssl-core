from protocols.common import robot_id_pb2 as _robot_id_pb2
from protocols.common import geometry_pb2 as _geometry_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Decision(_message.Message):
    __slots__ = ("behavior", "plan")
    BEHAVIOR_FIELD_NUMBER: _ClassVar[int]
    PLAN_FIELD_NUMBER: _ClassVar[int]
    behavior: _containers.RepeatedCompositeFieldContainer[Behavior]
    plan: TacticalPlan
    def __init__(self, behavior: _Optional[_Iterable[_Union[Behavior, _Mapping]]] = ..., plan: _Optional[_Union[TacticalPlan, _Mapping]] = ...) -> None: ...

class Behavior(_message.Message):
    __slots__ = ("id", "robot_id", "target")
    ID_FIELD_NUMBER: _ClassVar[int]
    ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
    TARGET_FIELD_NUMBER: _ClassVar[int]
    id: int
    robot_id: _robot_id_pb2.RobotId
    target: _geometry_pb2.Point2Df
    def __init__(self, id: _Optional[int] = ..., robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., target: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ...) -> None: ...

class TacticalPlan(_message.Message):
    __slots__ = ("offensive", "defensive")
    OFFENSIVE_FIELD_NUMBER: _ClassVar[int]
    DEFENSIVE_FIELD_NUMBER: _ClassVar[int]
    offensive: OffensivePlan
    defensive: DefensivePlan
    def __init__(self, offensive: _Optional[_Union[OffensivePlan, _Mapping]] = ..., defensive: _Optional[_Union[DefensivePlan, _Mapping]] = ...) -> None: ...

class DefensivePlan(_message.Message):
    __slots__ = ()
    def __init__(self) -> None: ...

class OffensivePlan(_message.Message):
    __slots__ = ()
    def __init__(self) -> None: ...
