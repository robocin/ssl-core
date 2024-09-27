from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class RealismConfigErForce(_message.Message):
    __slots__ = ("stddev_ball_p", "stddev_robot_p", "stddev_robot_phi", "stddev_ball_area", "enable_invisible_ball", "ball_visibility_threshold", "camera_overlap", "dribbler_ball_detections", "camera_position_error", "robot_command_loss", "robot_response_loss", "missing_ball_detections", "vision_delay", "vision_processing_time", "simulate_dribbling")
    STDDEV_BALL_P_FIELD_NUMBER: _ClassVar[int]
    STDDEV_ROBOT_P_FIELD_NUMBER: _ClassVar[int]
    STDDEV_ROBOT_PHI_FIELD_NUMBER: _ClassVar[int]
    STDDEV_BALL_AREA_FIELD_NUMBER: _ClassVar[int]
    ENABLE_INVISIBLE_BALL_FIELD_NUMBER: _ClassVar[int]
    BALL_VISIBILITY_THRESHOLD_FIELD_NUMBER: _ClassVar[int]
    CAMERA_OVERLAP_FIELD_NUMBER: _ClassVar[int]
    DRIBBLER_BALL_DETECTIONS_FIELD_NUMBER: _ClassVar[int]
    CAMERA_POSITION_ERROR_FIELD_NUMBER: _ClassVar[int]
    ROBOT_COMMAND_LOSS_FIELD_NUMBER: _ClassVar[int]
    ROBOT_RESPONSE_LOSS_FIELD_NUMBER: _ClassVar[int]
    MISSING_BALL_DETECTIONS_FIELD_NUMBER: _ClassVar[int]
    VISION_DELAY_FIELD_NUMBER: _ClassVar[int]
    VISION_PROCESSING_TIME_FIELD_NUMBER: _ClassVar[int]
    SIMULATE_DRIBBLING_FIELD_NUMBER: _ClassVar[int]
    stddev_ball_p: float
    stddev_robot_p: float
    stddev_robot_phi: float
    stddev_ball_area: float
    enable_invisible_ball: bool
    ball_visibility_threshold: float
    camera_overlap: float
    dribbler_ball_detections: float
    camera_position_error: float
    robot_command_loss: float
    robot_response_loss: float
    missing_ball_detections: float
    vision_delay: int
    vision_processing_time: int
    simulate_dribbling: bool
    def __init__(self, stddev_ball_p: _Optional[float] = ..., stddev_robot_p: _Optional[float] = ..., stddev_robot_phi: _Optional[float] = ..., stddev_ball_area: _Optional[float] = ..., enable_invisible_ball: bool = ..., ball_visibility_threshold: _Optional[float] = ..., camera_overlap: _Optional[float] = ..., dribbler_ball_detections: _Optional[float] = ..., camera_position_error: _Optional[float] = ..., robot_command_loss: _Optional[float] = ..., robot_response_loss: _Optional[float] = ..., missing_ball_detections: _Optional[float] = ..., vision_delay: _Optional[int] = ..., vision_processing_time: _Optional[int] = ..., simulate_dribbling: bool = ...) -> None: ...
