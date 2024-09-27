from protocols.third_party.game_controller import event_pb2 as _event_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class MatchType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    UNKNOWN_MATCH: _ClassVar[MatchType]
    GROUP_PHASE: _ClassVar[MatchType]
    ELIMINATION_PHASE: _ClassVar[MatchType]
    FRIENDLY: _ClassVar[MatchType]
UNKNOWN_MATCH: MatchType
GROUP_PHASE: MatchType
ELIMINATION_PHASE: MatchType
FRIENDLY: MatchType

class Referee(_message.Message):
    __slots__ = ("source_identifier", "match_type", "packet_timestamp", "stage", "stage_time_left", "command", "command_counter", "command_timestamp", "yellow", "blue", "designated_position", "blue_team_on_positive_half", "next_command", "game_events", "game_event_proposals", "current_action_time_remaining", "status_message")
    class Stage(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        NORMAL_FIRST_HALF_PRE: _ClassVar[Referee.Stage]
        NORMAL_FIRST_HALF: _ClassVar[Referee.Stage]
        NORMAL_HALF_TIME: _ClassVar[Referee.Stage]
        NORMAL_SECOND_HALF_PRE: _ClassVar[Referee.Stage]
        NORMAL_SECOND_HALF: _ClassVar[Referee.Stage]
        EXTRA_TIME_BREAK: _ClassVar[Referee.Stage]
        EXTRA_FIRST_HALF_PRE: _ClassVar[Referee.Stage]
        EXTRA_FIRST_HALF: _ClassVar[Referee.Stage]
        EXTRA_HALF_TIME: _ClassVar[Referee.Stage]
        EXTRA_SECOND_HALF_PRE: _ClassVar[Referee.Stage]
        EXTRA_SECOND_HALF: _ClassVar[Referee.Stage]
        PENALTY_SHOOTOUT_BREAK: _ClassVar[Referee.Stage]
        PENALTY_SHOOTOUT: _ClassVar[Referee.Stage]
        POST_GAME: _ClassVar[Referee.Stage]
    NORMAL_FIRST_HALF_PRE: Referee.Stage
    NORMAL_FIRST_HALF: Referee.Stage
    NORMAL_HALF_TIME: Referee.Stage
    NORMAL_SECOND_HALF_PRE: Referee.Stage
    NORMAL_SECOND_HALF: Referee.Stage
    EXTRA_TIME_BREAK: Referee.Stage
    EXTRA_FIRST_HALF_PRE: Referee.Stage
    EXTRA_FIRST_HALF: Referee.Stage
    EXTRA_HALF_TIME: Referee.Stage
    EXTRA_SECOND_HALF_PRE: Referee.Stage
    EXTRA_SECOND_HALF: Referee.Stage
    PENALTY_SHOOTOUT_BREAK: Referee.Stage
    PENALTY_SHOOTOUT: Referee.Stage
    POST_GAME: Referee.Stage
    class Command(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        HALT: _ClassVar[Referee.Command]
        STOP: _ClassVar[Referee.Command]
        NORMAL_START: _ClassVar[Referee.Command]
        FORCE_START: _ClassVar[Referee.Command]
        PREPARE_KICKOFF_YELLOW: _ClassVar[Referee.Command]
        PREPARE_KICKOFF_BLUE: _ClassVar[Referee.Command]
        PREPARE_PENALTY_YELLOW: _ClassVar[Referee.Command]
        PREPARE_PENALTY_BLUE: _ClassVar[Referee.Command]
        DIRECT_FREE_YELLOW: _ClassVar[Referee.Command]
        DIRECT_FREE_BLUE: _ClassVar[Referee.Command]
        INDIRECT_FREE_YELLOW: _ClassVar[Referee.Command]
        INDIRECT_FREE_BLUE: _ClassVar[Referee.Command]
        TIMEOUT_YELLOW: _ClassVar[Referee.Command]
        TIMEOUT_BLUE: _ClassVar[Referee.Command]
        GOAL_YELLOW: _ClassVar[Referee.Command]
        GOAL_BLUE: _ClassVar[Referee.Command]
        BALL_PLACEMENT_YELLOW: _ClassVar[Referee.Command]
        BALL_PLACEMENT_BLUE: _ClassVar[Referee.Command]
    HALT: Referee.Command
    STOP: Referee.Command
    NORMAL_START: Referee.Command
    FORCE_START: Referee.Command
    PREPARE_KICKOFF_YELLOW: Referee.Command
    PREPARE_KICKOFF_BLUE: Referee.Command
    PREPARE_PENALTY_YELLOW: Referee.Command
    PREPARE_PENALTY_BLUE: Referee.Command
    DIRECT_FREE_YELLOW: Referee.Command
    DIRECT_FREE_BLUE: Referee.Command
    INDIRECT_FREE_YELLOW: Referee.Command
    INDIRECT_FREE_BLUE: Referee.Command
    TIMEOUT_YELLOW: Referee.Command
    TIMEOUT_BLUE: Referee.Command
    GOAL_YELLOW: Referee.Command
    GOAL_BLUE: Referee.Command
    BALL_PLACEMENT_YELLOW: Referee.Command
    BALL_PLACEMENT_BLUE: Referee.Command
    class TeamInfo(_message.Message):
        __slots__ = ("name", "score", "red_cards", "yellow_card_times", "yellow_cards", "timeouts", "timeout_time", "goalkeeper", "foul_counter", "ball_placement_failures", "can_place_ball", "max_allowed_bots", "bot_substitution_intent", "ball_placement_failures_reached", "bot_substitution_allowed", "bot_substitutions_left", "bot_substitution_time_left")
        NAME_FIELD_NUMBER: _ClassVar[int]
        SCORE_FIELD_NUMBER: _ClassVar[int]
        RED_CARDS_FIELD_NUMBER: _ClassVar[int]
        YELLOW_CARD_TIMES_FIELD_NUMBER: _ClassVar[int]
        YELLOW_CARDS_FIELD_NUMBER: _ClassVar[int]
        TIMEOUTS_FIELD_NUMBER: _ClassVar[int]
        TIMEOUT_TIME_FIELD_NUMBER: _ClassVar[int]
        GOALKEEPER_FIELD_NUMBER: _ClassVar[int]
        FOUL_COUNTER_FIELD_NUMBER: _ClassVar[int]
        BALL_PLACEMENT_FAILURES_FIELD_NUMBER: _ClassVar[int]
        CAN_PLACE_BALL_FIELD_NUMBER: _ClassVar[int]
        MAX_ALLOWED_BOTS_FIELD_NUMBER: _ClassVar[int]
        BOT_SUBSTITUTION_INTENT_FIELD_NUMBER: _ClassVar[int]
        BALL_PLACEMENT_FAILURES_REACHED_FIELD_NUMBER: _ClassVar[int]
        BOT_SUBSTITUTION_ALLOWED_FIELD_NUMBER: _ClassVar[int]
        BOT_SUBSTITUTIONS_LEFT_FIELD_NUMBER: _ClassVar[int]
        BOT_SUBSTITUTION_TIME_LEFT_FIELD_NUMBER: _ClassVar[int]
        name: str
        score: int
        red_cards: int
        yellow_card_times: _containers.RepeatedScalarFieldContainer[int]
        yellow_cards: int
        timeouts: int
        timeout_time: int
        goalkeeper: int
        foul_counter: int
        ball_placement_failures: int
        can_place_ball: bool
        max_allowed_bots: int
        bot_substitution_intent: bool
        ball_placement_failures_reached: bool
        bot_substitution_allowed: bool
        bot_substitutions_left: int
        bot_substitution_time_left: int
        def __init__(self, name: _Optional[str] = ..., score: _Optional[int] = ..., red_cards: _Optional[int] = ..., yellow_card_times: _Optional[_Iterable[int]] = ..., yellow_cards: _Optional[int] = ..., timeouts: _Optional[int] = ..., timeout_time: _Optional[int] = ..., goalkeeper: _Optional[int] = ..., foul_counter: _Optional[int] = ..., ball_placement_failures: _Optional[int] = ..., can_place_ball: bool = ..., max_allowed_bots: _Optional[int] = ..., bot_substitution_intent: bool = ..., ball_placement_failures_reached: bool = ..., bot_substitution_allowed: bool = ..., bot_substitutions_left: _Optional[int] = ..., bot_substitution_time_left: _Optional[int] = ...) -> None: ...
    class Point(_message.Message):
        __slots__ = ("x", "y")
        X_FIELD_NUMBER: _ClassVar[int]
        Y_FIELD_NUMBER: _ClassVar[int]
        x: float
        y: float
        def __init__(self, x: _Optional[float] = ..., y: _Optional[float] = ...) -> None: ...
    SOURCE_IDENTIFIER_FIELD_NUMBER: _ClassVar[int]
    MATCH_TYPE_FIELD_NUMBER: _ClassVar[int]
    PACKET_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    STAGE_FIELD_NUMBER: _ClassVar[int]
    STAGE_TIME_LEFT_FIELD_NUMBER: _ClassVar[int]
    COMMAND_FIELD_NUMBER: _ClassVar[int]
    COMMAND_COUNTER_FIELD_NUMBER: _ClassVar[int]
    COMMAND_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    YELLOW_FIELD_NUMBER: _ClassVar[int]
    BLUE_FIELD_NUMBER: _ClassVar[int]
    DESIGNATED_POSITION_FIELD_NUMBER: _ClassVar[int]
    BLUE_TEAM_ON_POSITIVE_HALF_FIELD_NUMBER: _ClassVar[int]
    NEXT_COMMAND_FIELD_NUMBER: _ClassVar[int]
    GAME_EVENTS_FIELD_NUMBER: _ClassVar[int]
    GAME_EVENT_PROPOSALS_FIELD_NUMBER: _ClassVar[int]
    CURRENT_ACTION_TIME_REMAINING_FIELD_NUMBER: _ClassVar[int]
    STATUS_MESSAGE_FIELD_NUMBER: _ClassVar[int]
    source_identifier: str
    match_type: MatchType
    packet_timestamp: int
    stage: Referee.Stage
    stage_time_left: int
    command: Referee.Command
    command_counter: int
    command_timestamp: int
    yellow: Referee.TeamInfo
    blue: Referee.TeamInfo
    designated_position: Referee.Point
    blue_team_on_positive_half: bool
    next_command: Referee.Command
    game_events: _containers.RepeatedCompositeFieldContainer[_event_pb2.GameEvent]
    game_event_proposals: _containers.RepeatedCompositeFieldContainer[GameEventProposalGroup]
    current_action_time_remaining: int
    status_message: str
    def __init__(self, source_identifier: _Optional[str] = ..., match_type: _Optional[_Union[MatchType, str]] = ..., packet_timestamp: _Optional[int] = ..., stage: _Optional[_Union[Referee.Stage, str]] = ..., stage_time_left: _Optional[int] = ..., command: _Optional[_Union[Referee.Command, str]] = ..., command_counter: _Optional[int] = ..., command_timestamp: _Optional[int] = ..., yellow: _Optional[_Union[Referee.TeamInfo, _Mapping]] = ..., blue: _Optional[_Union[Referee.TeamInfo, _Mapping]] = ..., designated_position: _Optional[_Union[Referee.Point, _Mapping]] = ..., blue_team_on_positive_half: bool = ..., next_command: _Optional[_Union[Referee.Command, str]] = ..., game_events: _Optional[_Iterable[_Union[_event_pb2.GameEvent, _Mapping]]] = ..., game_event_proposals: _Optional[_Iterable[_Union[GameEventProposalGroup, _Mapping]]] = ..., current_action_time_remaining: _Optional[int] = ..., status_message: _Optional[str] = ...) -> None: ...

class GameEventProposalGroup(_message.Message):
    __slots__ = ("id", "game_events", "accepted")
    ID_FIELD_NUMBER: _ClassVar[int]
    GAME_EVENTS_FIELD_NUMBER: _ClassVar[int]
    ACCEPTED_FIELD_NUMBER: _ClassVar[int]
    id: str
    game_events: _containers.RepeatedCompositeFieldContainer[_event_pb2.GameEvent]
    accepted: bool
    def __init__(self, id: _Optional[str] = ..., game_events: _Optional[_Iterable[_Union[_event_pb2.GameEvent, _Mapping]]] = ..., accepted: bool = ...) -> None: ...
