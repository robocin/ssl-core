from protocols.third_party.game_controller import common_pb2 as _common_pb2
from protocols.third_party.game_controller import geometry_pb2 as _geometry_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class GameEvent(_message.Message):
    __slots__ = ("type", "origin", "ball_left_field_touch_line", "ball_left_field_goal_line", "aimless_kick", "attacker_too_close_to_defense_area", "defender_in_defense_area", "boundary_crossing", "keeper_held_ball", "bot_dribbled_ball_too_far", "bot_pushed_bot", "bot_held_ball_deliberately", "bot_tipped_over", "attacker_touched_ball_in_defense_area", "bot_kicked_ball_too_fast", "bot_crash_unique", "bot_crash_drawn", "defender_too_close_to_kick_point", "bot_too_fast_in_stop", "bot_interfered_placement", "possible_goal", "goal", "invalid_goal", "attacker_double_touched_ball", "placement_succeeded", "penalty_kick_failed", "no_progress_in_game", "placement_failed", "multiple_cards", "multiple_fouls", "bot_substitution", "too_many_robots", "challenge_flag", "emergency_stop", "unsporting_behavior_minor", "unsporting_behavior_major", "prepared", "indirect_goal", "chipped_goal", "kick_timeout", "attacker_touched_opponent_in_defense_area", "attacker_touched_opponent_in_defense_area_skipped", "bot_crash_unique_skipped", "bot_pushed_bot_skipped", "defender_in_defense_area_partially", "multiple_placement_failures")
    class Type(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        UNKNOWN_GAME_EVENT_TYPE: _ClassVar[GameEvent.Type]
        BALL_LEFT_FIELD_TOUCH_LINE: _ClassVar[GameEvent.Type]
        BALL_LEFT_FIELD_GOAL_LINE: _ClassVar[GameEvent.Type]
        AIMLESS_KICK: _ClassVar[GameEvent.Type]
        ATTACKER_TOO_CLOSE_TO_DEFENSE_AREA: _ClassVar[GameEvent.Type]
        DEFENDER_IN_DEFENSE_AREA: _ClassVar[GameEvent.Type]
        BOUNDARY_CROSSING: _ClassVar[GameEvent.Type]
        KEEPER_HELD_BALL: _ClassVar[GameEvent.Type]
        BOT_DRIBBLED_BALL_TOO_FAR: _ClassVar[GameEvent.Type]
        BOT_PUSHED_BOT: _ClassVar[GameEvent.Type]
        BOT_HELD_BALL_DELIBERATELY: _ClassVar[GameEvent.Type]
        BOT_TIPPED_OVER: _ClassVar[GameEvent.Type]
        ATTACKER_TOUCHED_BALL_IN_DEFENSE_AREA: _ClassVar[GameEvent.Type]
        BOT_KICKED_BALL_TOO_FAST: _ClassVar[GameEvent.Type]
        BOT_CRASH_UNIQUE: _ClassVar[GameEvent.Type]
        BOT_CRASH_DRAWN: _ClassVar[GameEvent.Type]
        DEFENDER_TOO_CLOSE_TO_KICK_POINT: _ClassVar[GameEvent.Type]
        BOT_TOO_FAST_IN_STOP: _ClassVar[GameEvent.Type]
        BOT_INTERFERED_PLACEMENT: _ClassVar[GameEvent.Type]
        POSSIBLE_GOAL: _ClassVar[GameEvent.Type]
        GOAL: _ClassVar[GameEvent.Type]
        INVALID_GOAL: _ClassVar[GameEvent.Type]
        ATTACKER_DOUBLE_TOUCHED_BALL: _ClassVar[GameEvent.Type]
        PLACEMENT_SUCCEEDED: _ClassVar[GameEvent.Type]
        PENALTY_KICK_FAILED: _ClassVar[GameEvent.Type]
        NO_PROGRESS_IN_GAME: _ClassVar[GameEvent.Type]
        PLACEMENT_FAILED: _ClassVar[GameEvent.Type]
        MULTIPLE_CARDS: _ClassVar[GameEvent.Type]
        MULTIPLE_FOULS: _ClassVar[GameEvent.Type]
        BOT_SUBSTITUTION: _ClassVar[GameEvent.Type]
        TOO_MANY_ROBOTS: _ClassVar[GameEvent.Type]
        CHALLENGE_FLAG: _ClassVar[GameEvent.Type]
        EMERGENCY_STOP: _ClassVar[GameEvent.Type]
        UNSPORTING_BEHAVIOR_MINOR: _ClassVar[GameEvent.Type]
        UNSPORTING_BEHAVIOR_MAJOR: _ClassVar[GameEvent.Type]
        PREPARED: _ClassVar[GameEvent.Type]
        INDIRECT_GOAL: _ClassVar[GameEvent.Type]
        CHIPPED_GOAL: _ClassVar[GameEvent.Type]
        KICK_TIMEOUT: _ClassVar[GameEvent.Type]
        ATTACKER_TOUCHED_OPPONENT_IN_DEFENSE_AREA: _ClassVar[GameEvent.Type]
        ATTACKER_TOUCHED_OPPONENT_IN_DEFENSE_AREA_SKIPPED: _ClassVar[GameEvent.Type]
        BOT_CRASH_UNIQUE_SKIPPED: _ClassVar[GameEvent.Type]
        BOT_PUSHED_BOT_SKIPPED: _ClassVar[GameEvent.Type]
        DEFENDER_IN_DEFENSE_AREA_PARTIALLY: _ClassVar[GameEvent.Type]
        MULTIPLE_PLACEMENT_FAILURES: _ClassVar[GameEvent.Type]
    UNKNOWN_GAME_EVENT_TYPE: GameEvent.Type
    BALL_LEFT_FIELD_TOUCH_LINE: GameEvent.Type
    BALL_LEFT_FIELD_GOAL_LINE: GameEvent.Type
    AIMLESS_KICK: GameEvent.Type
    ATTACKER_TOO_CLOSE_TO_DEFENSE_AREA: GameEvent.Type
    DEFENDER_IN_DEFENSE_AREA: GameEvent.Type
    BOUNDARY_CROSSING: GameEvent.Type
    KEEPER_HELD_BALL: GameEvent.Type
    BOT_DRIBBLED_BALL_TOO_FAR: GameEvent.Type
    BOT_PUSHED_BOT: GameEvent.Type
    BOT_HELD_BALL_DELIBERATELY: GameEvent.Type
    BOT_TIPPED_OVER: GameEvent.Type
    ATTACKER_TOUCHED_BALL_IN_DEFENSE_AREA: GameEvent.Type
    BOT_KICKED_BALL_TOO_FAST: GameEvent.Type
    BOT_CRASH_UNIQUE: GameEvent.Type
    BOT_CRASH_DRAWN: GameEvent.Type
    DEFENDER_TOO_CLOSE_TO_KICK_POINT: GameEvent.Type
    BOT_TOO_FAST_IN_STOP: GameEvent.Type
    BOT_INTERFERED_PLACEMENT: GameEvent.Type
    POSSIBLE_GOAL: GameEvent.Type
    GOAL: GameEvent.Type
    INVALID_GOAL: GameEvent.Type
    ATTACKER_DOUBLE_TOUCHED_BALL: GameEvent.Type
    PLACEMENT_SUCCEEDED: GameEvent.Type
    PENALTY_KICK_FAILED: GameEvent.Type
    NO_PROGRESS_IN_GAME: GameEvent.Type
    PLACEMENT_FAILED: GameEvent.Type
    MULTIPLE_CARDS: GameEvent.Type
    MULTIPLE_FOULS: GameEvent.Type
    BOT_SUBSTITUTION: GameEvent.Type
    TOO_MANY_ROBOTS: GameEvent.Type
    CHALLENGE_FLAG: GameEvent.Type
    EMERGENCY_STOP: GameEvent.Type
    UNSPORTING_BEHAVIOR_MINOR: GameEvent.Type
    UNSPORTING_BEHAVIOR_MAJOR: GameEvent.Type
    PREPARED: GameEvent.Type
    INDIRECT_GOAL: GameEvent.Type
    CHIPPED_GOAL: GameEvent.Type
    KICK_TIMEOUT: GameEvent.Type
    ATTACKER_TOUCHED_OPPONENT_IN_DEFENSE_AREA: GameEvent.Type
    ATTACKER_TOUCHED_OPPONENT_IN_DEFENSE_AREA_SKIPPED: GameEvent.Type
    BOT_CRASH_UNIQUE_SKIPPED: GameEvent.Type
    BOT_PUSHED_BOT_SKIPPED: GameEvent.Type
    DEFENDER_IN_DEFENSE_AREA_PARTIALLY: GameEvent.Type
    MULTIPLE_PLACEMENT_FAILURES: GameEvent.Type
    class BallLeftField(_message.Message):
        __slots__ = ("by_team", "by_bot", "location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class AimlessKick(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "kick_location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        KICK_LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        kick_location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., kick_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class Goal(_message.Message):
        __slots__ = ("by_team", "kicking_team", "kicking_bot", "location", "kick_location", "max_ball_height", "num_robots_by_team", "last_touch_by_team", "message")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        KICKING_TEAM_FIELD_NUMBER: _ClassVar[int]
        KICKING_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        KICK_LOCATION_FIELD_NUMBER: _ClassVar[int]
        MAX_BALL_HEIGHT_FIELD_NUMBER: _ClassVar[int]
        NUM_ROBOTS_BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        LAST_TOUCH_BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        MESSAGE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        kicking_team: _common_pb2.Team
        kicking_bot: int
        location: _geometry_pb2.Vector2
        kick_location: _geometry_pb2.Vector2
        max_ball_height: float
        num_robots_by_team: int
        last_touch_by_team: int
        message: str
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., kicking_team: _Optional[_Union[_common_pb2.Team, str]] = ..., kicking_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., kick_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., max_ball_height: _Optional[float] = ..., num_robots_by_team: _Optional[int] = ..., last_touch_by_team: _Optional[int] = ..., message: _Optional[str] = ...) -> None: ...
    class IndirectGoal(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "kick_location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        KICK_LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        kick_location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., kick_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class ChippedGoal(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "kick_location", "max_ball_height")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        KICK_LOCATION_FIELD_NUMBER: _ClassVar[int]
        MAX_BALL_HEIGHT_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        kick_location: _geometry_pb2.Vector2
        max_ball_height: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., kick_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., max_ball_height: _Optional[float] = ...) -> None: ...
    class BotTooFastInStop(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "speed")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        SPEED_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        speed: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., speed: _Optional[float] = ...) -> None: ...
    class DefenderTooCloseToKickPoint(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        distance: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., distance: _Optional[float] = ...) -> None: ...
    class BotCrashDrawn(_message.Message):
        __slots__ = ("bot_yellow", "bot_blue", "location", "crash_speed", "speed_diff", "crash_angle")
        BOT_YELLOW_FIELD_NUMBER: _ClassVar[int]
        BOT_BLUE_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        CRASH_SPEED_FIELD_NUMBER: _ClassVar[int]
        SPEED_DIFF_FIELD_NUMBER: _ClassVar[int]
        CRASH_ANGLE_FIELD_NUMBER: _ClassVar[int]
        bot_yellow: int
        bot_blue: int
        location: _geometry_pb2.Vector2
        crash_speed: float
        speed_diff: float
        crash_angle: float
        def __init__(self, bot_yellow: _Optional[int] = ..., bot_blue: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., crash_speed: _Optional[float] = ..., speed_diff: _Optional[float] = ..., crash_angle: _Optional[float] = ...) -> None: ...
    class BotCrashUnique(_message.Message):
        __slots__ = ("by_team", "violator", "victim", "location", "crash_speed", "speed_diff", "crash_angle")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        VIOLATOR_FIELD_NUMBER: _ClassVar[int]
        VICTIM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        CRASH_SPEED_FIELD_NUMBER: _ClassVar[int]
        SPEED_DIFF_FIELD_NUMBER: _ClassVar[int]
        CRASH_ANGLE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        violator: int
        victim: int
        location: _geometry_pb2.Vector2
        crash_speed: float
        speed_diff: float
        crash_angle: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., violator: _Optional[int] = ..., victim: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., crash_speed: _Optional[float] = ..., speed_diff: _Optional[float] = ..., crash_angle: _Optional[float] = ...) -> None: ...
    class BotPushedBot(_message.Message):
        __slots__ = ("by_team", "violator", "victim", "location", "pushed_distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        VIOLATOR_FIELD_NUMBER: _ClassVar[int]
        VICTIM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        PUSHED_DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        violator: int
        victim: int
        location: _geometry_pb2.Vector2
        pushed_distance: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., violator: _Optional[int] = ..., victim: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., pushed_distance: _Optional[float] = ...) -> None: ...
    class BotTippedOver(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "ball_location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        BALL_LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        ball_location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., ball_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class DefenderInDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        distance: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., distance: _Optional[float] = ...) -> None: ...
    class DefenderInDefenseAreaPartially(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "distance", "ball_location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FIELD_NUMBER: _ClassVar[int]
        BALL_LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        distance: float
        ball_location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., distance: _Optional[float] = ..., ball_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class AttackerTouchedBallInDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        distance: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., distance: _Optional[float] = ...) -> None: ...
    class BotKickedBallTooFast(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "initial_ball_speed", "chipped")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        INITIAL_BALL_SPEED_FIELD_NUMBER: _ClassVar[int]
        CHIPPED_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        initial_ball_speed: float
        chipped: bool
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., initial_ball_speed: _Optional[float] = ..., chipped: bool = ...) -> None: ...
    class BotDribbledBallTooFar(_message.Message):
        __slots__ = ("by_team", "by_bot", "start", "end")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        START_FIELD_NUMBER: _ClassVar[int]
        END_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        start: _geometry_pb2.Vector2
        end: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., start: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., end: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class AttackerTouchedOpponentInDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_bot", "victim", "location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        VICTIM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        victim: int
        location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., victim: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class AttackerDoubleTouchedBall(_message.Message):
        __slots__ = ("by_team", "by_bot", "location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class AttackerTooCloseToDefenseArea(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "distance", "ball_location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FIELD_NUMBER: _ClassVar[int]
        BALL_LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        distance: float
        ball_location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., distance: _Optional[float] = ..., ball_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class BotHeldBallDeliberately(_message.Message):
        __slots__ = ("by_team", "by_bot", "location", "duration")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DURATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        duration: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., duration: _Optional[float] = ...) -> None: ...
    class BotInterferedPlacement(_message.Message):
        __slots__ = ("by_team", "by_bot", "location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        BY_BOT_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        by_bot: int
        location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., by_bot: _Optional[int] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class MultipleCards(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ...) -> None: ...
    class MultipleFouls(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ...) -> None: ...
    class MultiplePlacementFailures(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ...) -> None: ...
    class KickTimeout(_message.Message):
        __slots__ = ("by_team", "location", "time")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        TIME_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        location: _geometry_pb2.Vector2
        time: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., time: _Optional[float] = ...) -> None: ...
    class NoProgressInGame(_message.Message):
        __slots__ = ("location", "time")
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        TIME_FIELD_NUMBER: _ClassVar[int]
        location: _geometry_pb2.Vector2
        time: float
        def __init__(self, location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., time: _Optional[float] = ...) -> None: ...
    class PlacementFailed(_message.Message):
        __slots__ = ("by_team", "remaining_distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        REMAINING_DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        remaining_distance: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., remaining_distance: _Optional[float] = ...) -> None: ...
    class UnsportingBehaviorMinor(_message.Message):
        __slots__ = ("by_team", "reason")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        REASON_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        reason: str
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., reason: _Optional[str] = ...) -> None: ...
    class UnsportingBehaviorMajor(_message.Message):
        __slots__ = ("by_team", "reason")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        REASON_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        reason: str
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., reason: _Optional[str] = ...) -> None: ...
    class KeeperHeldBall(_message.Message):
        __slots__ = ("by_team", "location", "duration")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        DURATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        location: _geometry_pb2.Vector2
        duration: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ..., duration: _Optional[float] = ...) -> None: ...
    class PlacementSucceeded(_message.Message):
        __slots__ = ("by_team", "time_taken", "precision", "distance")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        TIME_TAKEN_FIELD_NUMBER: _ClassVar[int]
        PRECISION_FIELD_NUMBER: _ClassVar[int]
        DISTANCE_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        time_taken: float
        precision: float
        distance: float
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., time_taken: _Optional[float] = ..., precision: _Optional[float] = ..., distance: _Optional[float] = ...) -> None: ...
    class Prepared(_message.Message):
        __slots__ = ("time_taken",)
        TIME_TAKEN_FIELD_NUMBER: _ClassVar[int]
        time_taken: float
        def __init__(self, time_taken: _Optional[float] = ...) -> None: ...
    class BotSubstitution(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ...) -> None: ...
    class ChallengeFlag(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ...) -> None: ...
    class EmergencyStop(_message.Message):
        __slots__ = ("by_team",)
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ...) -> None: ...
    class TooManyRobots(_message.Message):
        __slots__ = ("by_team", "num_robots_allowed", "num_robots_on_field", "ball_location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        NUM_ROBOTS_ALLOWED_FIELD_NUMBER: _ClassVar[int]
        NUM_ROBOTS_ON_FIELD_FIELD_NUMBER: _ClassVar[int]
        BALL_LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        num_robots_allowed: int
        num_robots_on_field: int
        ball_location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., num_robots_allowed: _Optional[int] = ..., num_robots_on_field: _Optional[int] = ..., ball_location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class BoundaryCrossing(_message.Message):
        __slots__ = ("by_team", "location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    class PenaltyKickFailed(_message.Message):
        __slots__ = ("by_team", "location")
        BY_TEAM_FIELD_NUMBER: _ClassVar[int]
        LOCATION_FIELD_NUMBER: _ClassVar[int]
        by_team: _common_pb2.Team
        location: _geometry_pb2.Vector2
        def __init__(self, by_team: _Optional[_Union[_common_pb2.Team, str]] = ..., location: _Optional[_Union[_geometry_pb2.Vector2, _Mapping]] = ...) -> None: ...
    TYPE_FIELD_NUMBER: _ClassVar[int]
    ORIGIN_FIELD_NUMBER: _ClassVar[int]
    BALL_LEFT_FIELD_TOUCH_LINE_FIELD_NUMBER: _ClassVar[int]
    BALL_LEFT_FIELD_GOAL_LINE_FIELD_NUMBER: _ClassVar[int]
    AIMLESS_KICK_FIELD_NUMBER: _ClassVar[int]
    ATTACKER_TOO_CLOSE_TO_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    DEFENDER_IN_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    BOUNDARY_CROSSING_FIELD_NUMBER: _ClassVar[int]
    KEEPER_HELD_BALL_FIELD_NUMBER: _ClassVar[int]
    BOT_DRIBBLED_BALL_TOO_FAR_FIELD_NUMBER: _ClassVar[int]
    BOT_PUSHED_BOT_FIELD_NUMBER: _ClassVar[int]
    BOT_HELD_BALL_DELIBERATELY_FIELD_NUMBER: _ClassVar[int]
    BOT_TIPPED_OVER_FIELD_NUMBER: _ClassVar[int]
    ATTACKER_TOUCHED_BALL_IN_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    BOT_KICKED_BALL_TOO_FAST_FIELD_NUMBER: _ClassVar[int]
    BOT_CRASH_UNIQUE_FIELD_NUMBER: _ClassVar[int]
    BOT_CRASH_DRAWN_FIELD_NUMBER: _ClassVar[int]
    DEFENDER_TOO_CLOSE_TO_KICK_POINT_FIELD_NUMBER: _ClassVar[int]
    BOT_TOO_FAST_IN_STOP_FIELD_NUMBER: _ClassVar[int]
    BOT_INTERFERED_PLACEMENT_FIELD_NUMBER: _ClassVar[int]
    POSSIBLE_GOAL_FIELD_NUMBER: _ClassVar[int]
    GOAL_FIELD_NUMBER: _ClassVar[int]
    INVALID_GOAL_FIELD_NUMBER: _ClassVar[int]
    ATTACKER_DOUBLE_TOUCHED_BALL_FIELD_NUMBER: _ClassVar[int]
    PLACEMENT_SUCCEEDED_FIELD_NUMBER: _ClassVar[int]
    PENALTY_KICK_FAILED_FIELD_NUMBER: _ClassVar[int]
    NO_PROGRESS_IN_GAME_FIELD_NUMBER: _ClassVar[int]
    PLACEMENT_FAILED_FIELD_NUMBER: _ClassVar[int]
    MULTIPLE_CARDS_FIELD_NUMBER: _ClassVar[int]
    MULTIPLE_FOULS_FIELD_NUMBER: _ClassVar[int]
    BOT_SUBSTITUTION_FIELD_NUMBER: _ClassVar[int]
    TOO_MANY_ROBOTS_FIELD_NUMBER: _ClassVar[int]
    CHALLENGE_FLAG_FIELD_NUMBER: _ClassVar[int]
    EMERGENCY_STOP_FIELD_NUMBER: _ClassVar[int]
    UNSPORTING_BEHAVIOR_MINOR_FIELD_NUMBER: _ClassVar[int]
    UNSPORTING_BEHAVIOR_MAJOR_FIELD_NUMBER: _ClassVar[int]
    PREPARED_FIELD_NUMBER: _ClassVar[int]
    INDIRECT_GOAL_FIELD_NUMBER: _ClassVar[int]
    CHIPPED_GOAL_FIELD_NUMBER: _ClassVar[int]
    KICK_TIMEOUT_FIELD_NUMBER: _ClassVar[int]
    ATTACKER_TOUCHED_OPPONENT_IN_DEFENSE_AREA_FIELD_NUMBER: _ClassVar[int]
    ATTACKER_TOUCHED_OPPONENT_IN_DEFENSE_AREA_SKIPPED_FIELD_NUMBER: _ClassVar[int]
    BOT_CRASH_UNIQUE_SKIPPED_FIELD_NUMBER: _ClassVar[int]
    BOT_PUSHED_BOT_SKIPPED_FIELD_NUMBER: _ClassVar[int]
    DEFENDER_IN_DEFENSE_AREA_PARTIALLY_FIELD_NUMBER: _ClassVar[int]
    MULTIPLE_PLACEMENT_FAILURES_FIELD_NUMBER: _ClassVar[int]
    type: GameEvent.Type
    origin: _containers.RepeatedScalarFieldContainer[str]
    ball_left_field_touch_line: GameEvent.BallLeftField
    ball_left_field_goal_line: GameEvent.BallLeftField
    aimless_kick: GameEvent.AimlessKick
    attacker_too_close_to_defense_area: GameEvent.AttackerTooCloseToDefenseArea
    defender_in_defense_area: GameEvent.DefenderInDefenseArea
    boundary_crossing: GameEvent.BoundaryCrossing
    keeper_held_ball: GameEvent.KeeperHeldBall
    bot_dribbled_ball_too_far: GameEvent.BotDribbledBallTooFar
    bot_pushed_bot: GameEvent.BotPushedBot
    bot_held_ball_deliberately: GameEvent.BotHeldBallDeliberately
    bot_tipped_over: GameEvent.BotTippedOver
    attacker_touched_ball_in_defense_area: GameEvent.AttackerTouchedBallInDefenseArea
    bot_kicked_ball_too_fast: GameEvent.BotKickedBallTooFast
    bot_crash_unique: GameEvent.BotCrashUnique
    bot_crash_drawn: GameEvent.BotCrashDrawn
    defender_too_close_to_kick_point: GameEvent.DefenderTooCloseToKickPoint
    bot_too_fast_in_stop: GameEvent.BotTooFastInStop
    bot_interfered_placement: GameEvent.BotInterferedPlacement
    possible_goal: GameEvent.Goal
    goal: GameEvent.Goal
    invalid_goal: GameEvent.Goal
    attacker_double_touched_ball: GameEvent.AttackerDoubleTouchedBall
    placement_succeeded: GameEvent.PlacementSucceeded
    penalty_kick_failed: GameEvent.PenaltyKickFailed
    no_progress_in_game: GameEvent.NoProgressInGame
    placement_failed: GameEvent.PlacementFailed
    multiple_cards: GameEvent.MultipleCards
    multiple_fouls: GameEvent.MultipleFouls
    bot_substitution: GameEvent.BotSubstitution
    too_many_robots: GameEvent.TooManyRobots
    challenge_flag: GameEvent.ChallengeFlag
    emergency_stop: GameEvent.EmergencyStop
    unsporting_behavior_minor: GameEvent.UnsportingBehaviorMinor
    unsporting_behavior_major: GameEvent.UnsportingBehaviorMajor
    prepared: GameEvent.Prepared
    indirect_goal: GameEvent.IndirectGoal
    chipped_goal: GameEvent.ChippedGoal
    kick_timeout: GameEvent.KickTimeout
    attacker_touched_opponent_in_defense_area: GameEvent.AttackerTouchedOpponentInDefenseArea
    attacker_touched_opponent_in_defense_area_skipped: GameEvent.AttackerTouchedOpponentInDefenseArea
    bot_crash_unique_skipped: GameEvent.BotCrashUnique
    bot_pushed_bot_skipped: GameEvent.BotPushedBot
    defender_in_defense_area_partially: GameEvent.DefenderInDefenseAreaPartially
    multiple_placement_failures: GameEvent.MultiplePlacementFailures
    def __init__(self, type: _Optional[_Union[GameEvent.Type, str]] = ..., origin: _Optional[_Iterable[str]] = ..., ball_left_field_touch_line: _Optional[_Union[GameEvent.BallLeftField, _Mapping]] = ..., ball_left_field_goal_line: _Optional[_Union[GameEvent.BallLeftField, _Mapping]] = ..., aimless_kick: _Optional[_Union[GameEvent.AimlessKick, _Mapping]] = ..., attacker_too_close_to_defense_area: _Optional[_Union[GameEvent.AttackerTooCloseToDefenseArea, _Mapping]] = ..., defender_in_defense_area: _Optional[_Union[GameEvent.DefenderInDefenseArea, _Mapping]] = ..., boundary_crossing: _Optional[_Union[GameEvent.BoundaryCrossing, _Mapping]] = ..., keeper_held_ball: _Optional[_Union[GameEvent.KeeperHeldBall, _Mapping]] = ..., bot_dribbled_ball_too_far: _Optional[_Union[GameEvent.BotDribbledBallTooFar, _Mapping]] = ..., bot_pushed_bot: _Optional[_Union[GameEvent.BotPushedBot, _Mapping]] = ..., bot_held_ball_deliberately: _Optional[_Union[GameEvent.BotHeldBallDeliberately, _Mapping]] = ..., bot_tipped_over: _Optional[_Union[GameEvent.BotTippedOver, _Mapping]] = ..., attacker_touched_ball_in_defense_area: _Optional[_Union[GameEvent.AttackerTouchedBallInDefenseArea, _Mapping]] = ..., bot_kicked_ball_too_fast: _Optional[_Union[GameEvent.BotKickedBallTooFast, _Mapping]] = ..., bot_crash_unique: _Optional[_Union[GameEvent.BotCrashUnique, _Mapping]] = ..., bot_crash_drawn: _Optional[_Union[GameEvent.BotCrashDrawn, _Mapping]] = ..., defender_too_close_to_kick_point: _Optional[_Union[GameEvent.DefenderTooCloseToKickPoint, _Mapping]] = ..., bot_too_fast_in_stop: _Optional[_Union[GameEvent.BotTooFastInStop, _Mapping]] = ..., bot_interfered_placement: _Optional[_Union[GameEvent.BotInterferedPlacement, _Mapping]] = ..., possible_goal: _Optional[_Union[GameEvent.Goal, _Mapping]] = ..., goal: _Optional[_Union[GameEvent.Goal, _Mapping]] = ..., invalid_goal: _Optional[_Union[GameEvent.Goal, _Mapping]] = ..., attacker_double_touched_ball: _Optional[_Union[GameEvent.AttackerDoubleTouchedBall, _Mapping]] = ..., placement_succeeded: _Optional[_Union[GameEvent.PlacementSucceeded, _Mapping]] = ..., penalty_kick_failed: _Optional[_Union[GameEvent.PenaltyKickFailed, _Mapping]] = ..., no_progress_in_game: _Optional[_Union[GameEvent.NoProgressInGame, _Mapping]] = ..., placement_failed: _Optional[_Union[GameEvent.PlacementFailed, _Mapping]] = ..., multiple_cards: _Optional[_Union[GameEvent.MultipleCards, _Mapping]] = ..., multiple_fouls: _Optional[_Union[GameEvent.MultipleFouls, _Mapping]] = ..., bot_substitution: _Optional[_Union[GameEvent.BotSubstitution, _Mapping]] = ..., too_many_robots: _Optional[_Union[GameEvent.TooManyRobots, _Mapping]] = ..., challenge_flag: _Optional[_Union[GameEvent.ChallengeFlag, _Mapping]] = ..., emergency_stop: _Optional[_Union[GameEvent.EmergencyStop, _Mapping]] = ..., unsporting_behavior_minor: _Optional[_Union[GameEvent.UnsportingBehaviorMinor, _Mapping]] = ..., unsporting_behavior_major: _Optional[_Union[GameEvent.UnsportingBehaviorMajor, _Mapping]] = ..., prepared: _Optional[_Union[GameEvent.Prepared, _Mapping]] = ..., indirect_goal: _Optional[_Union[GameEvent.IndirectGoal, _Mapping]] = ..., chipped_goal: _Optional[_Union[GameEvent.ChippedGoal, _Mapping]] = ..., kick_timeout: _Optional[_Union[GameEvent.KickTimeout, _Mapping]] = ..., attacker_touched_opponent_in_defense_area: _Optional[_Union[GameEvent.AttackerTouchedOpponentInDefenseArea, _Mapping]] = ..., attacker_touched_opponent_in_defense_area_skipped: _Optional[_Union[GameEvent.AttackerTouchedOpponentInDefenseArea, _Mapping]] = ..., bot_crash_unique_skipped: _Optional[_Union[GameEvent.BotCrashUnique, _Mapping]] = ..., bot_pushed_bot_skipped: _Optional[_Union[GameEvent.BotPushedBot, _Mapping]] = ..., defender_in_defense_area_partially: _Optional[_Union[GameEvent.DefenderInDefenseAreaPartially, _Mapping]] = ..., multiple_placement_failures: _Optional[_Union[GameEvent.MultiplePlacementFailures, _Mapping]] = ...) -> None: ...
