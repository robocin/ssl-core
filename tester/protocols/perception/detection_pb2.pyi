from google.protobuf import timestamp_pb2 as _timestamp_pb2
from protocols.common import geometry_pb2 as _geometry_pb2
from protocols.common import robot_id_pb2 as _robot_id_pb2
from protocols.third_party.detection import raw_wrapper_pb2 as _raw_wrapper_pb2
from protocols.third_party.game_controller import tracked_wrapper_pb2 as _tracked_wrapper_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class DetectionWrapper(_message.Message):
    __slots__ = ("detection", "raw_detections", "tracked_detections")
    DETECTION_FIELD_NUMBER: _ClassVar[int]
    RAW_DETECTIONS_FIELD_NUMBER: _ClassVar[int]
    TRACKED_DETECTIONS_FIELD_NUMBER: _ClassVar[int]
    detection: Detection
    raw_detections: _containers.RepeatedCompositeFieldContainer[_raw_wrapper_pb2.SSL_WrapperPacket]
    tracked_detections: _containers.RepeatedCompositeFieldContainer[_tracked_wrapper_pb2.TrackerWrapperPacket]
    def __init__(self, detection: _Optional[_Union[Detection, _Mapping]] = ..., raw_detections: _Optional[_Iterable[_Union[_raw_wrapper_pb2.SSL_WrapperPacket, _Mapping]]] = ..., tracked_detections: _Optional[_Iterable[_Union[_tracked_wrapper_pb2.TrackerWrapperPacket, _Mapping]]] = ...) -> None: ...

class Detection(_message.Message):
    __slots__ = ("serial_id", "created_at", "framerate", "balls", "robots", "field")
    SERIAL_ID_FIELD_NUMBER: _ClassVar[int]
    CREATED_AT_FIELD_NUMBER: _ClassVar[int]
    FRAMERATE_FIELD_NUMBER: _ClassVar[int]
    BALLS_FIELD_NUMBER: _ClassVar[int]
    ROBOTS_FIELD_NUMBER: _ClassVar[int]
    FIELD_FIELD_NUMBER: _ClassVar[int]
    serial_id: int
    created_at: _timestamp_pb2.Timestamp
    framerate: int
    balls: _containers.RepeatedCompositeFieldContainer[Ball]
    robots: _containers.RepeatedCompositeFieldContainer[Robot]
    field: Field
    def __init__(self, serial_id: _Optional[int] = ..., created_at: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., framerate: _Optional[int] = ..., balls: _Optional[_Iterable[_Union[Ball, _Mapping]]] = ..., robots: _Optional[_Iterable[_Union[Robot, _Mapping]]] = ..., field: _Optional[_Union[Field, _Mapping]] = ...) -> None: ...

class Ball(_message.Message):
    __slots__ = ("confidence", "position", "velocity", "kick_information")
    class KickInformation(_message.Message):
        __slots__ = ("robot_id", "start_position", "start_velocity", "start_timestamp", "predicted_stop_position", "predicted_stop_timestamp")
        ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
        START_POSITION_FIELD_NUMBER: _ClassVar[int]
        START_VELOCITY_FIELD_NUMBER: _ClassVar[int]
        START_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
        PREDICTED_STOP_POSITION_FIELD_NUMBER: _ClassVar[int]
        PREDICTED_STOP_TIMESTAMP_FIELD_NUMBER: _ClassVar[int]
        robot_id: _robot_id_pb2.RobotId
        start_position: _geometry_pb2.Point2Df
        start_velocity: _geometry_pb2.Point3Df
        start_timestamp: _timestamp_pb2.Timestamp
        predicted_stop_position: _geometry_pb2.Point2Df
        predicted_stop_timestamp: _timestamp_pb2.Timestamp
        def __init__(self, robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., start_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., start_velocity: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ..., start_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., predicted_stop_position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., predicted_stop_timestamp: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ...) -> None: ...
    CONFIDENCE_FIELD_NUMBER: _ClassVar[int]
    POSITION_FIELD_NUMBER: _ClassVar[int]
    VELOCITY_FIELD_NUMBER: _ClassVar[int]
    KICK_INFORMATION_FIELD_NUMBER: _ClassVar[int]
    confidence: float
    position: _geometry_pb2.Point3Df
    velocity: _geometry_pb2.Point3Df
    kick_information: Ball.KickInformation
    def __init__(self, confidence: _Optional[float] = ..., position: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ..., velocity: _Optional[_Union[_geometry_pb2.Point3Df, _Mapping]] = ..., kick_information: _Optional[_Union[Ball.KickInformation, _Mapping]] = ...) -> None: ...

class Robot(_message.Message):
    __slots__ = ("confidence", "robot_id", "position", "angle", "velocity", "angular_velocity", "radius", "height", "dribbler_width", "feedback")
    class Feedback(_message.Message):
        __slots__ = ("dribbler_ball_contact", "kick_charge_percentage", "battery_percentage", "wheels")
        class Wheel(_message.Message):
            __slots__ = ("wheel_id", "motor_speed")
            WHEEL_ID_FIELD_NUMBER: _ClassVar[int]
            MOTOR_SPEED_FIELD_NUMBER: _ClassVar[int]
            wheel_id: int
            motor_speed: float
            def __init__(self, wheel_id: _Optional[int] = ..., motor_speed: _Optional[float] = ...) -> None: ...
        DRIBBLER_BALL_CONTACT_FIELD_NUMBER: _ClassVar[int]
        KICK_CHARGE_PERCENTAGE_FIELD_NUMBER: _ClassVar[int]
        BATTERY_PERCENTAGE_FIELD_NUMBER: _ClassVar[int]
        WHEELS_FIELD_NUMBER: _ClassVar[int]
        dribbler_ball_contact: bool
        kick_charge_percentage: float
        battery_percentage: float
        wheels: _containers.RepeatedCompositeFieldContainer[Robot.Feedback.Wheel]
        def __init__(self, dribbler_ball_contact: bool = ..., kick_charge_percentage: _Optional[float] = ..., battery_percentage: _Optional[float] = ..., wheels: _Optional[_Iterable[_Union[Robot.Feedback.Wheel, _Mapping]]] = ...) -> None: ...
    CONFIDENCE_FIELD_NUMBER: _ClassVar[int]
    ROBOT_ID_FIELD_NUMBER: _ClassVar[int]
    POSITION_FIELD_NUMBER: _ClassVar[int]
    ANGLE_FIELD_NUMBER: _ClassVar[int]
    VELOCITY_FIELD_NUMBER: _ClassVar[int]
    ANGULAR_VELOCITY_FIELD_NUMBER: _ClassVar[int]
    RADIUS_FIELD_NUMBER: _ClassVar[int]
    HEIGHT_FIELD_NUMBER: _ClassVar[int]
    DRIBBLER_WIDTH_FIELD_NUMBER: _ClassVar[int]
    FEEDBACK_FIELD_NUMBER: _ClassVar[int]
    confidence: float
    robot_id: _robot_id_pb2.RobotId
    position: _geometry_pb2.Point2Df
    angle: float
    velocity: _geometry_pb2.Point2Df
    angular_velocity: float
    radius: float
    height: float
    dribbler_width: float
    feedback: Robot.Feedback
    def __init__(self, confidence: _Optional[float] = ..., robot_id: _Optional[_Union[_robot_id_pb2.RobotId, _Mapping]] = ..., position: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angle: _Optional[float] = ..., velocity: _Optional[_Union[_geometry_pb2.Point2Df, _Mapping]] = ..., angular_velocity: _Optional[float] = ..., radius: _Optional[float] = ..., height: _Optional[float] = ..., dribbler_width: _Optional[float] = ..., feedback: _Optional[_Union[Robot.Feedback, _Mapping]] = ...) -> None: ...

class Field(_message.Message):
    __slots__ = ("serial_id", "length", "width", "goal_depth", "goal_width", "penalty_area_depth", "penalty_area_width", "boundary_width", "goal_center_to_penalty_mark")
    SERIAL_ID_FIELD_NUMBER: _ClassVar[int]
    LENGTH_FIELD_NUMBER: _ClassVar[int]
    WIDTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_DEPTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_WIDTH_FIELD_NUMBER: _ClassVar[int]
    PENALTY_AREA_DEPTH_FIELD_NUMBER: _ClassVar[int]
    PENALTY_AREA_WIDTH_FIELD_NUMBER: _ClassVar[int]
    BOUNDARY_WIDTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_CENTER_TO_PENALTY_MARK_FIELD_NUMBER: _ClassVar[int]
    serial_id: int
    length: float
    width: float
    goal_depth: float
    goal_width: float
    penalty_area_depth: float
    penalty_area_width: float
    boundary_width: float
    goal_center_to_penalty_mark: float
    def __init__(self, serial_id: _Optional[int] = ..., length: _Optional[float] = ..., width: _Optional[float] = ..., goal_depth: _Optional[float] = ..., goal_width: _Optional[float] = ..., penalty_area_depth: _Optional[float] = ..., penalty_area_width: _Optional[float] = ..., boundary_width: _Optional[float] = ..., goal_center_to_penalty_mark: _Optional[float] = ...) -> None: ...
