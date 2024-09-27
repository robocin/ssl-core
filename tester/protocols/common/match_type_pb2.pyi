from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from typing import ClassVar as _ClassVar

DESCRIPTOR: _descriptor.FileDescriptor

class MatchType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    MATCH_TYPE_UNSPECIFIED: _ClassVar[MatchType]
    MATCH_TYPE_GROUP_PHASE: _ClassVar[MatchType]
    MATCH_TYPE_ELIMINATION_PHASE: _ClassVar[MatchType]
    MATCH_TYPE_FRIENDLY: _ClassVar[MatchType]
MATCH_TYPE_UNSPECIFIED: MatchType
MATCH_TYPE_GROUP_PHASE: MatchType
MATCH_TYPE_ELIMINATION_PHASE: MatchType
MATCH_TYPE_FRIENDLY: MatchType
