from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.common import game_event_pb2 as _game_event_pb2
from protocols.playback import sample_pb2 as _sample_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class ReceiveLivestreamRequest(_message.Message):
    __slots__ = ()
    def __init__(self) -> None: ...

class ReceiveLivestreamResponse(_message.Message):
    __slots__ = ("sample",)
    SAMPLE_FIELD_NUMBER: _ClassVar[int]
    sample: _sample_pb2.Sample
    def __init__(self, sample: _Optional[_Union[_sample_pb2.Sample, _Mapping]] = ...) -> None: ...

class GetGameEventsRequest(_message.Message):
    __slots__ = ()
    def __init__(self) -> None: ...

class GetGameEventsResponse(_message.Message):
    __slots__ = ("game_events",)
    GAME_EVENTS_FIELD_NUMBER: _ClassVar[int]
    game_events: _containers.RepeatedCompositeFieldContainer[_game_event_pb2.GameEvent]
    def __init__(self, game_events: _Optional[_Iterable[_Union[_game_event_pb2.GameEvent, _Mapping]]] = ...) -> None: ...

class GetReplayChunkRequest(_message.Message):
    __slots__ = ("start_timestamp",)
    START_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    start_timestamp: _timestamp_pb2.Timestamp
    def __init__(self, start_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ...) -> None: ...

class GetReplayChunkResponse(_message.Message):
    __slots__ = ("last_timestamp", "samples")
    LAST_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    SAMPLES_FIELD_NUMBER: _ClassVar[int]
    last_timestamp: _timestamp_pb2.Timestamp
    samples: _containers.RepeatedCompositeFieldContainer[_sample_pb2.Sample]
    def __init__(self, last_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., samples: _Optional[_Iterable[_Union[_sample_pb2.Sample, _Mapping]]] = ...) -> None: ...
