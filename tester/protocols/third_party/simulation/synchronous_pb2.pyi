from protocols.third_party.detection import raw_pb2 as _raw_pb2
from protocols.third_party.simulation import control_pb2 as _control_pb2
from protocols.third_party.simulation import robot_control_pb2 as _robot_control_pb2
from protocols.third_party.simulation import robot_feedback_pb2 as _robot_feedback_pb2
from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class SimulationSyncRequest(_message.Message):
    __slots__ = ("sim_step", "simulator_command", "robot_control")
    SIM_STEP_FIELD_NUMBER: _ClassVar[int]
    SIMULATOR_COMMAND_FIELD_NUMBER: _ClassVar[int]
    ROBOT_CONTROL_FIELD_NUMBER: _ClassVar[int]
    sim_step: float
    simulator_command: _control_pb2.SimulatorCommand
    robot_control: _robot_control_pb2.RobotControl
    def __init__(self, sim_step: _Optional[float] = ..., simulator_command: _Optional[_Union[_control_pb2.SimulatorCommand, _Mapping]] = ..., robot_control: _Optional[_Union[_robot_control_pb2.RobotControl, _Mapping]] = ...) -> None: ...

class SimulationSyncResponse(_message.Message):
    __slots__ = ("detection", "robot_control_response")
    DETECTION_FIELD_NUMBER: _ClassVar[int]
    ROBOT_CONTROL_RESPONSE_FIELD_NUMBER: _ClassVar[int]
    detection: _containers.RepeatedCompositeFieldContainer[_raw_pb2.SSL_DetectionFrame]
    robot_control_response: _robot_feedback_pb2.RobotControlResponse
    def __init__(self, detection: _Optional[_Iterable[_Union[_raw_pb2.SSL_DetectionFrame, _Mapping]]] = ..., robot_control_response: _Optional[_Union[_robot_feedback_pb2.RobotControlResponse, _Mapping]] = ...) -> None: ...
