from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from typing import ClassVar as _ClassVar

DESCRIPTOR: _descriptor.FileDescriptor

class Team(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    TEAM_UNSPECIFIED: _ClassVar[Team]
    TEAM_HOME: _ClassVar[Team]
    TEAM_AWAY: _ClassVar[Team]
TEAM_UNSPECIFIED: Team
TEAM_HOME: Team
TEAM_AWAY: Team
