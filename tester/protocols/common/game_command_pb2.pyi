from google.protobuf import duration_pb2 as _duration_pb2
from protocols.common import geometry_pb2 as _geometry_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class GameCommand(_message.Message):
    __slots__ = ("halt", "in_game", "stop", "home_ball_placement", "away_ball_placement", "home_prepare_kickoff", "away_prepare_kickoff", "home_kickoff", "away_kickoff", "home_prepare_penalty", "away_prepare_penalty", "home_penalty", "away_penalty", "home_prepare_direct_free_kick", "away_prepare_direct_free_kick", "home_direct_free_kick", "away_direct_free_kick", "home_timeout", "away_timeout", "interval")
    class Halt(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class InGame(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class Stop(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class BallPlacement(_message.Message):
        __slots__ = ("position", "remaining_time")
        POSITION_FIELD_NUMBER: _ClassVar[int]
        REMAINING_TIME_FIELD_NUMBER: _ClassVar[int]
        position: _geometry_pb2.Point2Df
        remaining_time: _duration_pb2.Duration
        def __init__(self, position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., remaining_time: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class PrepareKickoff(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class Kickoff(_message.Message):
        __slots__ = ("remaining_time",)
        REMAINING_TIME_FIELD_NUMBER: _ClassVar[int]
        remaining_time: _duration_pb2.Duration
        def __init__(self, remaining_time: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class PreparePenalty(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class Penalty(_message.Message):
        __slots__ = ("remaining_time",)
        REMAINING_TIME_FIELD_NUMBER: _ClassVar[int]
        remaining_time: _duration_pb2.Duration
        def __init__(self, remaining_time: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class PrepareDirectFreeKick(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class DirectFreeKick(_message.Message):
        __slots__ = ("remaining_time",)
        REMAINING_TIME_FIELD_NUMBER: _ClassVar[int]
        remaining_time: _duration_pb2.Duration
        def __init__(self, remaining_time: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class Timeout(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    class Interval(_message.Message):
        __slots__ = ()
        def __init__(self) -> None: ...
    HALT_FIELD_NUMBER: _ClassVar[int]
    IN_GAME_FIELD_NUMBER: _ClassVar[int]
    STOP_FIELD_NUMBER: _ClassVar[int]
    HOME_BALL_PLACEMENT_FIELD_NUMBER: _ClassVar[int]
    AWAY_BALL_PLACEMENT_FIELD_NUMBER: _ClassVar[int]
    HOME_PREPARE_KICKOFF_FIELD_NUMBER: _ClassVar[int]
    AWAY_PREPARE_KICKOFF_FIELD_NUMBER: _ClassVar[int]
    HOME_KICKOFF_FIELD_NUMBER: _ClassVar[int]
    AWAY_KICKOFF_FIELD_NUMBER: _ClassVar[int]
    HOME_PREPARE_PENALTY_FIELD_NUMBER: _ClassVar[int]
    AWAY_PREPARE_PENALTY_FIELD_NUMBER: _ClassVar[int]
    HOME_PENALTY_FIELD_NUMBER: _ClassVar[int]
    AWAY_PENALTY_FIELD_NUMBER: _ClassVar[int]
    HOME_PREPARE_DIRECT_FREE_KICK_FIELD_NUMBER: _ClassVar[int]
    AWAY_PREPARE_DIRECT_FREE_KICK_FIELD_NUMBER: _ClassVar[int]
    HOME_DIRECT_FREE_KICK_FIELD_NUMBER: _ClassVar[int]
    AWAY_DIRECT_FREE_KICK_FIELD_NUMBER: _ClassVar[int]
    HOME_TIMEOUT_FIELD_NUMBER: _ClassVar[int]
    AWAY_TIMEOUT_FIELD_NUMBER: _ClassVar[int]
    INTERVAL_FIELD_NUMBER: _ClassVar[int]
    halt: GameCommand.Halt
    in_game: GameCommand.InGame
    stop: GameCommand.Stop
    home_ball_placement: GameCommand.BallPlacement
    away_ball_placement: GameCommand.BallPlacement
    home_prepare_kickoff: GameCommand.PrepareKickoff
    away_prepare_kickoff: GameCommand.PrepareKickoff
    home_kickoff: GameCommand.Kickoff
    away_kickoff: GameCommand.Kickoff
    home_prepare_penalty: GameCommand.PreparePenalty
    away_prepare_penalty: GameCommand.PreparePenalty
    home_penalty: GameCommand.Penalty
    away_penalty: GameCommand.Penalty
    home_prepare_direct_free_kick: GameCommand.PrepareDirectFreeKick
    away_prepare_direct_free_kick: GameCommand.PrepareDirectFreeKick
    home_direct_free_kick: GameCommand.DirectFreeKick
    away_direct_free_kick: GameCommand.DirectFreeKick
    home_timeout: GameCommand.Timeout
    away_timeout: GameCommand.Timeout
    interval: GameCommand.Interval
    def __init__(self, halt: _Optional[_Union[GameCommand.Halt, _Mapping]] = ..., in_game: _Optional[_Union[GameCommand.InGame, _Mapping]] = ..., stop: _Optional[_Union[GameCommand.Stop, _Mapping]] = ..., home_ball_placement: _Optional[_Union[GameCommand.BallPlacement, _Mapping]] = ..., away_ball_placement: _Optional[_Union[GameCommand.BallPlacement, _Mapping]] = ..., home_prepare_kickoff: _Optional[_Union[GameCommand.PrepareKickoff, _Mapping]] = ..., away_prepare_kickoff: _Optional[_Union[GameCommand.PrepareKickoff, _Mapping]] = ..., home_kickoff: _Optional[_Union[GameCommand.Kickoff, _Mapping]] = ..., away_kickoff: _Optional[_Union[GameCommand.Kickoff, _Mapping]] = ..., home_prepare_penalty: _Optional[_Union[GameCommand.PreparePenalty, _Mapping]] = ..., away_prepare_penalty: _Optional[_Union[GameCommand.PreparePenalty, _Mapping]] = ..., home_penalty: _Optional[_Union[GameCommand.Penalty, _Mapping]] = ..., away_penalty: _Optional[_Union[GameCommand.Penalty, _Mapping]] = ..., home_prepare_direct_free_kick: _Optional[_Union[GameCommand.PrepareDirectFreeKick, _Mapping]] = ..., away_prepare_direct_free_kick: _Optional[_Union[GameCommand.PrepareDirectFreeKick, _Mapping]] = ..., home_direct_free_kick: _Optional[_Union[GameCommand.DirectFreeKick, _Mapping]] = ..., away_direct_free_kick: _Optional[_Union[GameCommand.DirectFreeKick, _Mapping]] = ..., home_timeout: _Optional[_Union[GameCommand.Timeout, _Mapping]] = ..., away_timeout: _Optional[_Union[GameCommand.Timeout, _Mapping]] = ..., interval: _Optional[_Union[GameCommand.Interval, _Mapping]] = ...) -> None: ...
