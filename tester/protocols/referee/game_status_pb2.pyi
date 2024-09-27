from google.protobuf import duration_pb2 as _duration_pb2
from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.common import game_command_pb2 as _game_command_pb2
from protocols.common import game_event_pb2 as _game_event_pb2
from protocols.common import game_stage_pb2 as _game_stage_pb2
from protocols.common import match_type_pb2 as _match_type_pb2
from protocols.common import robot_id_pb2 as _robot_id_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class GameStatus(_message.Message):
    __slots__ = ("source_id", "description", "timestamp", "match_type", "home_team", "away_team", "game_stage", "game_stage_time_left", "total_commands_issued", "command_issued_timestamp", "command", "next_command", "game_events", "game_events_proposals")
    class Team(_message.Message):
        __slots__ = ("name", "score", "robot_ids", "goalkeeper_id", "yellow_cards", "time_to_expire_active_yellow_cards", "red_cards", "timeouts_left", "total_timeout_time_left", "total_fouls_committed", "consecutive_ball_placement_failures", "is_ball_placement_enabled", "has_ball_placement_failures_reached_maximum", "maximum_allowed_robots", "is_robot_substitution_requested", "is_robot_substitution_allowed", "robot_substitutions_left", "robot_substitution_time_left")
        NAME_FIELD_NUMBER: _ClassVar[int]
        SCORE_FIELD_NUMBER: _ClassVar[int]
        ROBOT_IDS_FIELD_NUMBER: _ClassVar[int]
        GOALKEEPER_ID_FIELD_NUMBER: _ClassVar[int]
        YELLOW_CARDS_FIELD_NUMBER: _ClassVar[int]
        TIME_TO_EXPIRE_ACTIVE_YELLOW_CARDS_FIELD_NUMBER: _ClassVar[int]
        RED_CARDS_FIELD_NUMBER: _ClassVar[int]
        TIMEOUTS_LEFT_FIELD_NUMBER: _ClassVar[int]
        TOTAL_TIMEOUT_TIME_LEFT_FIELD_NUMBER: _ClassVar[int]
        TOTAL_FOULS_COMMITTED_FIELD_NUMBER: _ClassVar[int]
        CONSECUTIVE_BALL_PLACEMENT_FAILURES_FIELD_NUMBER: _ClassVar[int]
        IS_BALL_PLACEMENT_ENABLED_FIELD_NUMBER: _ClassVar[int]
        HAS_BALL_PLACEMENT_FAILURES_REACHED_MAXIMUM_FIELD_NUMBER: _ClassVar[int]
        MAXIMUM_ALLOWED_ROBOTS_FIELD_NUMBER: _ClassVar[int]
        IS_ROBOT_SUBSTITUTION_REQUESTED_FIELD_NUMBER: _ClassVar[int]
        IS_ROBOT_SUBSTITUTION_ALLOWED_FIELD_NUMBER: _ClassVar[int]
        ROBOT_SUBSTITUTIONS_LEFT_FIELD_NUMBER: _ClassVar[int]
        ROBOT_SUBSTITUTION_TIME_LEFT_FIELD_NUMBER: _ClassVar[int]
        name: str
        score: int
        robot_ids: _containers.RepeatedCompositeFieldContainer[_robot_id_pb2.RobotId]
        goalkeeper_id: _robot_id_pb2.RobotId
        yellow_cards: int
        time_to_expire_active_yellow_cards: _containers.RepeatedCompositeFieldContainer[_duration_pb2.Duration]
        red_cards: int
        timeouts_left: int
        total_timeout_time_left: _duration_pb2.Duration
        total_fouls_committed: int
        consecutive_ball_placement_failures: int
        is_ball_placement_enabled: bool
        has_ball_placement_failures_reached_maximum: bool
        maximum_allowed_robots: int
        is_robot_substitution_requested: bool
        is_robot_substitution_allowed: bool
        robot_substitutions_left: int
        robot_substitution_time_left: _duration_pb2.Duration
        def __init__(self, name: _Optional[str] = ..., score: _Optional[int] = ..., robot_ids: _Optional[_Iterable[_Union[_robot_id_pb2.RobotId, _Mapping]]] = ..., goalkeeper_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., yellow_cards: _Optional[int] = ..., time_to_expire_active_yellow_cards: _Optional[_Iterable[_Union[_duration_pb2.Duration, _Mapping]]] = ..., red_cards: _Optional[int] = ..., timeouts_left: _Optional[int] = ..., total_timeout_time_left: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ..., total_fouls_committed: _Optional[int] = ..., consecutive_ball_placement_failures: _Optional[int] = ..., is_ball_placement_enabled: bool = ..., has_ball_placement_failures_reached_maximum: bool = ..., maximum_allowed_robots: _Optional[int] = ..., is_robot_substitution_requested: bool = ..., is_robot_substitution_allowed: bool = ..., robot_substitutions_left: _Optional[int] = ..., robot_substitution_time_left: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ...) -> None: ...
    class GameEventsProposal(_message.Message):
        __slots__ = ("proposal_id", "game_events", "was_accepted")
        PROPOSAL_ID_FIELD_NUMBER: _ClassVar[int]
        GAME_EVENTS_FIELD_NUMBER: _ClassVar[int]
        WAS_ACCEPTED_FIELD_NUMBER: _ClassVar[int]
        proposal_id: str
        game_events: _containers.RepeatedCompositeFieldContainer[_game_event_pb2.GameEvent]
        was_accepted: bool
        def __init__(self, proposal_id: _Optional[str] = ..., game_events: _Optional[_Iterable[_Union[_game_event_pb2.GameEvent, _Mapping]]] = ..., was_accepted: bool = ...) -> None: ...
    SOURCE_ID_FIELD_NUMBER: _ClassVar[int]
    DESCRIPTION_FIELD_NUMBER: _ClassVar[int]
    TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    MATCH_TYPE_FIELD_NUMBER: _ClassVar[int]
    HOME_TEAM_FIELD_NUMBER: _ClassVar[int]
    AWAY_TEAM_FIELD_NUMBER: _ClassVar[int]
    GAME_STAGE_FIELD_NUMBER: _ClassVar[int]
    GAME_STAGE_TIME_LEFT_FIELD_NUMBER: _ClassVar[int]
    TOTAL_COMMANDS_ISSUED_FIELD_NUMBER: _ClassVar[int]
    COMMAND_ISSUED_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    COMMAND_FIELD_NUMBER: _ClassVar[int]
    NEXT_COMMAND_FIELD_NUMBER: _ClassVar[int]
    GAME_EVENTS_FIELD_NUMBER: _ClassVar[int]
    GAME_EVENTS_PROPOSALS_FIELD_NUMBER: _ClassVar[int]
    source_id: str
    description: str
    timestamp: _timestamp_pb2.Timestamp
    match_type: _match_type_pb2.MatchType
    home_team: GameStatus.Team
    away_team: GameStatus.Team
    game_stage: _game_stage_pb2.GameStage
    game_stage_time_left: _duration_pb2.Duration
    total_commands_issued: int
    command_issued_timestamp: _timestamp_pb2.Timestamp
    command: _game_command_pb2.GameCommand
    next_command: _game_command_pb2.GameCommand
    game_events: _containers.RepeatedCompositeFieldContainer[_game_event_pb2.GameEvent]
    game_events_proposals: _containers.RepeatedCompositeFieldContainer[GameStatus.GameEventsProposal]
    def __init__(self, source_id: _Optional[str] = ..., description: _Optional[str] = ..., timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., match_type: _Optional[_Union[_match_type_pb2.MatchType, str]] = ..., home_team: _Optional[_Union[GameStatus.Team, _Mapping]] = ..., away_team: _Optional[_Union[GameStatus.Team, _Mapping]] = ..., game_stage: _Optional[_Union[_game_stage_pb2.GameStage, str]] = ..., game_stage_time_left: _Optional[_Union[_duration_pb2.Duration, _Mapping]] = ..., total_commands_issued: _Optional[int] = ..., command_issued_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., command: _Optional[_Union[_game_command_pb2.GameCommand, _Mapping]] = ..., next_command: _Optional[_Union[_game_command_pb2.GameCommand, _Mapping]] = ..., game_events: _Optional[_Iterable[_Union[_game_event_pb2.GameEvent, _Mapping]]] = ..., game_events_proposals: _Optional[_Iterable[_Union[GameStatus.GameEventsProposal, _Mapping]]] = ...) -> None: ...
