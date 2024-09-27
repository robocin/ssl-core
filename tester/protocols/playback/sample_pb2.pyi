from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.playback import detection_pb2 as _detection_pb2
from protocols.playback import field_pb2 as _field_pb2
from protocols.playback import game_status_pb2 as _game_status_pb2
from protocols.playback import raw_detection_pb2 as _raw_detection_pb2
from protocols.playback import tracked_detection_pb2 as _tracked_detection_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Sample(_message.Message):
    __slots__ = ("first_timestamp", "timestamp", "field", "detection", "game_status", "raw_detection", "tracked_detection")
    FIRST_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
    FIELD_FIELD_NUMBER: _ClassVar[int]
    DETECTION_FIELD_NUMBER: _ClassVar[int]
    GAME_STATUS_FIELD_NUMBER: _ClassVar[int]
    RAW_DETECTION_FIELD_NUMBER: _ClassVar[int]
    TRACKED_DETECTION_FIELD_NUMBER: _ClassVar[int]
    first_timestamp: _timestamp_pb2.Timestamp
    timestamp: _timestamp_pb2.Timestamp
    field: _field_pb2.Field
    detection: _detection_pb2.Detection
    game_status: _game_status_pb2.GameStatus
    raw_detection: _raw_detection_pb2.RawDetection
    tracked_detection: _tracked_detection_pb2.TrackedDetection
    def __init__(self, first_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., field: _Optional[_Union[_field_pb2.Field, _Mapping]] = ..., detection: _Optional[_Union[_detection_pb2.Detection, _Mapping]] = ..., game_status: _Optional[_Union[_game_status_pb2.GameStatus, _Mapping]] = ..., raw_detection: _Optional[_Union[_raw_detection_pb2.RawDetection, _Mapping]] = ..., tracked_detection: _Optional[_Union[_tracked_detection_pb2.TrackedDetection, _Mapping]] = ...) -> None: ...
