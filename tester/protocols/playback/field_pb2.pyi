from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class Field(_message.Message):
    __slots__ = ("length", "width", "goal_depth", "goal_width", "penalty_area_depth", "penalty_area_width", "boundary_width", "goal_center_to_penalty_mark")
    LENGTH_FIELD_NUMBER: _ClassVar[int]
    WIDTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_DEPTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_WIDTH_FIELD_NUMBER: _ClassVar[int]
    PENALTY_AREA_DEPTH_FIELD_NUMBER: _ClassVar[int]
    PENALTY_AREA_WIDTH_FIELD_NUMBER: _ClassVar[int]
    BOUNDARY_WIDTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_CENTER_TO_PENALTY_MARK_FIELD_NUMBER: _ClassVar[int]
    length: float
    width: float
    goal_depth: float
    goal_width: float
    penalty_area_depth: float
    penalty_area_width: float
    boundary_width: float
    goal_center_to_penalty_mark: float
    def __init__(self, length: _Optional[float] = ..., width: _Optional[float] = ..., goal_depth: _Optional[float] = ..., goal_width: _Optional[float] = ..., penalty_area_depth: _Optional[float] = ..., penalty_area_width: _Optional[float] = ..., boundary_width: _Optional[float] = ..., goal_center_to_penalty_mark: _Optional[float] = ...) -> None: ...
