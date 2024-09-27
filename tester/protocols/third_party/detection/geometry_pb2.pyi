from google.protobuf.internal import containers as _containers
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class SSL_FieldShapeType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = ()
    Undefined: _ClassVar[SSL_FieldShapeType]
    CenterCircle: _ClassVar[SSL_FieldShapeType]
    TopTouchLine: _ClassVar[SSL_FieldShapeType]
    BottomTouchLine: _ClassVar[SSL_FieldShapeType]
    LeftGoalLine: _ClassVar[SSL_FieldShapeType]
    RightGoalLine: _ClassVar[SSL_FieldShapeType]
    HalfwayLine: _ClassVar[SSL_FieldShapeType]
    CenterLine: _ClassVar[SSL_FieldShapeType]
    LeftPenaltyStretch: _ClassVar[SSL_FieldShapeType]
    RightPenaltyStretch: _ClassVar[SSL_FieldShapeType]
    LeftFieldLeftPenaltyStretch: _ClassVar[SSL_FieldShapeType]
    LeftFieldRightPenaltyStretch: _ClassVar[SSL_FieldShapeType]
    RightFieldLeftPenaltyStretch: _ClassVar[SSL_FieldShapeType]
    RightFieldRightPenaltyStretch: _ClassVar[SSL_FieldShapeType]
Undefined: SSL_FieldShapeType
CenterCircle: SSL_FieldShapeType
TopTouchLine: SSL_FieldShapeType
BottomTouchLine: SSL_FieldShapeType
LeftGoalLine: SSL_FieldShapeType
RightGoalLine: SSL_FieldShapeType
HalfwayLine: SSL_FieldShapeType
CenterLine: SSL_FieldShapeType
LeftPenaltyStretch: SSL_FieldShapeType
RightPenaltyStretch: SSL_FieldShapeType
LeftFieldLeftPenaltyStretch: SSL_FieldShapeType
LeftFieldRightPenaltyStretch: SSL_FieldShapeType
RightFieldLeftPenaltyStretch: SSL_FieldShapeType
RightFieldRightPenaltyStretch: SSL_FieldShapeType

class Vector2f(_message.Message):
    __slots__ = ("x", "y")
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    x: float
    y: float
    def __init__(self, x: _Optional[float] = ..., y: _Optional[float] = ...) -> None: ...

class SSL_FieldLineSegment(_message.Message):
    __slots__ = ("name", "p1", "p2", "thickness", "type")
    NAME_FIELD_NUMBER: _ClassVar[int]
    P1_FIELD_NUMBER: _ClassVar[int]
    P2_FIELD_NUMBER: _ClassVar[int]
    THICKNESS_FIELD_NUMBER: _ClassVar[int]
    TYPE_FIELD_NUMBER: _ClassVar[int]
    name: str
    p1: Vector2f
    p2: Vector2f
    thickness: float
    type: SSL_FieldShapeType
    def __init__(self, name: _Optional[str] = ..., p1: _Optional[_Union[Vector2f, _Mapping]] = ..., p2: _Optional[_Union[Vector2f, _Mapping]] = ..., thickness: _Optional[float] = ..., type: _Optional[_Union[SSL_FieldShapeType, str]] = ...) -> None: ...

class SSL_FieldCircularArc(_message.Message):
    __slots__ = ("name", "center", "radius", "a1", "a2", "thickness", "type")
    NAME_FIELD_NUMBER: _ClassVar[int]
    CENTER_FIELD_NUMBER: _ClassVar[int]
    RADIUS_FIELD_NUMBER: _ClassVar[int]
    A1_FIELD_NUMBER: _ClassVar[int]
    A2_FIELD_NUMBER: _ClassVar[int]
    THICKNESS_FIELD_NUMBER: _ClassVar[int]
    TYPE_FIELD_NUMBER: _ClassVar[int]
    name: str
    center: Vector2f
    radius: float
    a1: float
    a2: float
    thickness: float
    type: SSL_FieldShapeType
    def __init__(self, name: _Optional[str] = ..., center: _Optional[_Union[Vector2f, _Mapping]] = ..., radius: _Optional[float] = ..., a1: _Optional[float] = ..., a2: _Optional[float] = ..., thickness: _Optional[float] = ..., type: _Optional[_Union[SSL_FieldShapeType, str]] = ...) -> None: ...

class SSL_GeometryFieldSize(_message.Message):
    __slots__ = ("field_length", "field_width", "goal_width", "goal_depth", "boundary_width", "field_lines", "field_arcs", "penalty_area_depth", "penalty_area_width", "center_circle_radius", "line_thickness", "goal_center_to_penalty_mark", "goal_height", "ball_radius", "max_robot_radius")
    FIELD_LENGTH_FIELD_NUMBER: _ClassVar[int]
    FIELD_WIDTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_WIDTH_FIELD_NUMBER: _ClassVar[int]
    GOAL_DEPTH_FIELD_NUMBER: _ClassVar[int]
    BOUNDARY_WIDTH_FIELD_NUMBER: _ClassVar[int]
    FIELD_LINES_FIELD_NUMBER: _ClassVar[int]
    FIELD_ARCS_FIELD_NUMBER: _ClassVar[int]
    PENALTY_AREA_DEPTH_FIELD_NUMBER: _ClassVar[int]
    PENALTY_AREA_WIDTH_FIELD_NUMBER: _ClassVar[int]
    CENTER_CIRCLE_RADIUS_FIELD_NUMBER: _ClassVar[int]
    LINE_THICKNESS_FIELD_NUMBER: _ClassVar[int]
    GOAL_CENTER_TO_PENALTY_MARK_FIELD_NUMBER: _ClassVar[int]
    GOAL_HEIGHT_FIELD_NUMBER: _ClassVar[int]
    BALL_RADIUS_FIELD_NUMBER: _ClassVar[int]
    MAX_ROBOT_RADIUS_FIELD_NUMBER: _ClassVar[int]
    field_length: int
    field_width: int
    goal_width: int
    goal_depth: int
    boundary_width: int
    field_lines: _containers.RepeatedCompositeFieldContainer[SSL_FieldLineSegment]
    field_arcs: _containers.RepeatedCompositeFieldContainer[SSL_FieldCircularArc]
    penalty_area_depth: int
    penalty_area_width: int
    center_circle_radius: int
    line_thickness: int
    goal_center_to_penalty_mark: int
    goal_height: int
    ball_radius: float
    max_robot_radius: float
    def __init__(self, field_length: _Optional[int] = ..., field_width: _Optional[int] = ..., goal_width: _Optional[int] = ..., goal_depth: _Optional[int] = ..., boundary_width: _Optional[int] = ..., field_lines: _Optional[_Iterable[_Union[SSL_FieldLineSegment, _Mapping]]] = ..., field_arcs: _Optional[_Iterable[_Union[SSL_FieldCircularArc, _Mapping]]] = ..., penalty_area_depth: _Optional[int] = ..., penalty_area_width: _Optional[int] = ..., center_circle_radius: _Optional[int] = ..., line_thickness: _Optional[int] = ..., goal_center_to_penalty_mark: _Optional[int] = ..., goal_height: _Optional[int] = ..., ball_radius: _Optional[float] = ..., max_robot_radius: _Optional[float] = ...) -> None: ...

class SSL_GeometryCameraCalibration(_message.Message):
    __slots__ = ("camera_id", "focal_length", "principal_point_x", "principal_point_y", "distortion", "q0", "q1", "q2", "q3", "tx", "ty", "tz", "derived_camera_world_tx", "derived_camera_world_ty", "derived_camera_world_tz", "pixel_image_width", "pixel_image_height")
    CAMERA_ID_FIELD_NUMBER: _ClassVar[int]
    FOCAL_LENGTH_FIELD_NUMBER: _ClassVar[int]
    PRINCIPAL_POINT_X_FIELD_NUMBER: _ClassVar[int]
    PRINCIPAL_POINT_Y_FIELD_NUMBER: _ClassVar[int]
    DISTORTION_FIELD_NUMBER: _ClassVar[int]
    Q0_FIELD_NUMBER: _ClassVar[int]
    Q1_FIELD_NUMBER: _ClassVar[int]
    Q2_FIELD_NUMBER: _ClassVar[int]
    Q3_FIELD_NUMBER: _ClassVar[int]
    TX_FIELD_NUMBER: _ClassVar[int]
    TY_FIELD_NUMBER: _ClassVar[int]
    TZ_FIELD_NUMBER: _ClassVar[int]
    DERIVED_CAMERA_WORLD_TX_FIELD_NUMBER: _ClassVar[int]
    DERIVED_CAMERA_WORLD_TY_FIELD_NUMBER: _ClassVar[int]
    DERIVED_CAMERA_WORLD_TZ_FIELD_NUMBER: _ClassVar[int]
    PIXEL_IMAGE_WIDTH_FIELD_NUMBER: _ClassVar[int]
    PIXEL_IMAGE_HEIGHT_FIELD_NUMBER: _ClassVar[int]
    camera_id: int
    focal_length: float
    principal_point_x: float
    principal_point_y: float
    distortion: float
    q0: float
    q1: float
    q2: float
    q3: float
    tx: float
    ty: float
    tz: float
    derived_camera_world_tx: float
    derived_camera_world_ty: float
    derived_camera_world_tz: float
    pixel_image_width: int
    pixel_image_height: int
    def __init__(self, camera_id: _Optional[int] = ..., focal_length: _Optional[float] = ..., principal_point_x: _Optional[float] = ..., principal_point_y: _Optional[float] = ..., distortion: _Optional[float] = ..., q0: _Optional[float] = ..., q1: _Optional[float] = ..., q2: _Optional[float] = ..., q3: _Optional[float] = ..., tx: _Optional[float] = ..., ty: _Optional[float] = ..., tz: _Optional[float] = ..., derived_camera_world_tx: _Optional[float] = ..., derived_camera_world_ty: _Optional[float] = ..., derived_camera_world_tz: _Optional[float] = ..., pixel_image_width: _Optional[int] = ..., pixel_image_height: _Optional[int] = ...) -> None: ...

class SSL_BallModelStraightTwoPhase(_message.Message):
    __slots__ = ("acc_slide", "acc_roll", "k_switch")
    ACC_SLIDE_FIELD_NUMBER: _ClassVar[int]
    ACC_ROLL_FIELD_NUMBER: _ClassVar[int]
    K_SWITCH_FIELD_NUMBER: _ClassVar[int]
    acc_slide: float
    acc_roll: float
    k_switch: float
    def __init__(self, acc_slide: _Optional[float] = ..., acc_roll: _Optional[float] = ..., k_switch: _Optional[float] = ...) -> None: ...

class SSL_BallModelChipFixedLoss(_message.Message):
    __slots__ = ("damping_xy_first_hop", "damping_xy_other_hops", "damping_z")
    DAMPING_XY_FIRST_HOP_FIELD_NUMBER: _ClassVar[int]
    DAMPING_XY_OTHER_HOPS_FIELD_NUMBER: _ClassVar[int]
    DAMPING_Z_FIELD_NUMBER: _ClassVar[int]
    damping_xy_first_hop: float
    damping_xy_other_hops: float
    damping_z: float
    def __init__(self, damping_xy_first_hop: _Optional[float] = ..., damping_xy_other_hops: _Optional[float] = ..., damping_z: _Optional[float] = ...) -> None: ...

class SSL_GeometryModels(_message.Message):
    __slots__ = ("straight_two_phase", "chip_fixed_loss")
    STRAIGHT_TWO_PHASE_FIELD_NUMBER: _ClassVar[int]
    CHIP_FIXED_LOSS_FIELD_NUMBER: _ClassVar[int]
    straight_two_phase: SSL_BallModelStraightTwoPhase
    chip_fixed_loss: SSL_BallModelChipFixedLoss
    def __init__(self, straight_two_phase: _Optional[_Union[SSL_BallModelStraightTwoPhase, _Mapping]] = ..., chip_fixed_loss: _Optional[_Union[SSL_BallModelChipFixedLoss, _Mapping]] = ...) -> None: ...

class SSL_GeometryData(_message.Message):
    __slots__ = ("field", "calib", "models")
    FIELD_FIELD_NUMBER: _ClassVar[int]
    CALIB_FIELD_NUMBER: _ClassVar[int]
    MODELS_FIELD_NUMBER: _ClassVar[int]
    field: SSL_GeometryFieldSize
    calib: _containers.RepeatedCompositeFieldContainer[SSL_GeometryCameraCalibration]
    models: SSL_GeometryModels
    def __init__(self, field: _Optional[_Union[SSL_GeometryFieldSize, _Mapping]] = ..., calib: _Optional[_Iterable[_Union[SSL_GeometryCameraCalibration, _Mapping]]] = ..., models: _Optional[_Union[SSL_GeometryModels, _Mapping]] = ...) -> None: ...
