from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from typing import ClassVar as _ClassVar

DESCRIPTOR: _descriptor.FileDescriptor

class GameStage(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    GAME_STAGE_UNSPECIFIED: _ClassVar[GameStage]
    GAME_STAGE_NORMAL_FIRST_HALF_PRE: _ClassVar[GameStage]
    GAME_STAGE_NORMAL_FIRST_HALF: _ClassVar[GameStage]
    GAME_STAGE_NORMAL_HALF_TIME: _ClassVar[GameStage]
    GAME_STAGE_NORMAL_SECOND_HALF_PRE: _ClassVar[GameStage]
    GAME_STAGE_NORMAL_SECOND_HALF: _ClassVar[GameStage]
    GAME_STAGE_EXTRA_TIME_BREAK: _ClassVar[GameStage]
    GAME_STAGE_EXTRA_FIRST_HALF_PRE: _ClassVar[GameStage]
    GAME_STAGE_EXTRA_FIRST_HALF: _ClassVar[GameStage]
    GAME_STAGE_EXTRA_HALF_TIME: _ClassVar[GameStage]
    GAME_STAGE_EXTRA_SECOND_HALF_PRE: _ClassVar[GameStage]
    GAME_STAGE_EXTRA_SECOND_HALF: _ClassVar[GameStage]
    GAME_STAGE_PENALTY_SHOOTOUT_BREAK: _ClassVar[GameStage]
    GAME_STAGE_PENALTY_SHOOTOUT: _ClassVar[GameStage]
    GAME_STAGE_POST_GAME: _ClassVar[GameStage]
GAME_STAGE_UNSPECIFIED: GameStage
GAME_STAGE_NORMAL_FIRST_HALF_PRE: GameStage
GAME_STAGE_NORMAL_FIRST_HALF: GameStage
GAME_STAGE_NORMAL_HALF_TIME: GameStage
GAME_STAGE_NORMAL_SECOND_HALF_PRE: GameStage
GAME_STAGE_NORMAL_SECOND_HALF: GameStage
GAME_STAGE_EXTRA_TIME_BREAK: GameStage
GAME_STAGE_EXTRA_FIRST_HALF_PRE: GameStage
GAME_STAGE_EXTRA_FIRST_HALF: GameStage
GAME_STAGE_EXTRA_HALF_TIME: GameStage
GAME_STAGE_EXTRA_SECOND_HALF_PRE: GameStage
GAME_STAGE_EXTRA_SECOND_HALF: GameStage
GAME_STAGE_PENALTY_SHOOTOUT_BREAK: GameStage
GAME_STAGE_PENALTY_SHOOTOUT: GameStage
GAME_STAGE_POST_GAME: GameStage
