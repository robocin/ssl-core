# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protocols/playback/tracked_detection.proto
# Protobuf Python Version: 5.27.2
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import runtime_version as _runtime_version
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
_runtime_version.ValidateProtobufRuntimeVersion(
    _runtime_version.Domain.PUBLIC,
    5,
    27,
    2,
    '',
    'protocols/playback/tracked_detection.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from protocols.common import geometry_pb2 as protocols_dot_common_dot_geometry__pb2
from protocols.common import robot_id_pb2 as protocols_dot_common_dot_robot__id__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n*protocols/playback/tracked_detection.proto\x12\x12protocols.playback\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1fprotocols/common/geometry.proto\x1a\x1fprotocols/common/robot_id.proto\"\xf7\t\n\x10TrackedDetection\x12\x18\n\x10source_unique_id\x18\x01 \x01(\t\x12\x1c\n\x14source_software_name\x18\x02 \x01(\t\x12V\n\x13source_capabilities\x18\x03 \x03(\x0e\x32\x35.protocols.playback.TrackedDetection.SourceCapabilityB\x02\x10\x01\x12\x11\n\tserial_id\x18\x04 \x01(\r\x12\x38\n\x05\x62\x61lls\x18\x05 \x03(\x0b\x32).protocols.playback.TrackedDetection.Ball\x12:\n\x06robots\x18\x06 \x03(\x0b\x32*.protocols.playback.TrackedDetection.Robot\x1a\xbe\x04\n\x04\x42\x61ll\x12\x12\n\nconfidence\x18\x01 \x01(\x02\x12,\n\x08position\x18\x02 \x01(\x0b\x32\x1a.protocols.common.Point3Df\x12,\n\x08velocity\x18\x03 \x01(\x0b\x32\x1a.protocols.common.Point3Df\x12X\n\x10kick_information\x18\x04 \x01(\x0b\x32\x39.protocols.playback.TrackedDetection.Ball.KickInformationH\x00\x88\x01\x01\x1a\xd6\x02\n\x0fKickInformation\x12+\n\x08robot_id\x18\x01 \x01(\x0b\x32\x19.protocols.common.RobotId\x12\x32\n\x0estart_position\x18\x02 \x01(\x0b\x32\x1a.protocols.common.Point2Df\x12\x32\n\x0estart_velocity\x18\x03 \x01(\x0b\x32\x1a.protocols.common.Point3Df\x12\x33\n\x0fstart_timestamp\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12;\n\x17predicted_stop_position\x18\x05 \x01(\x0b\x32\x1a.protocols.common.Point2Df\x12<\n\x18predicted_stop_timestamp\x18\x06 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x13\n\x11_kick_information\x1a\xcd\x01\n\x05Robot\x12+\n\x08robot_id\x18\x01 \x01(\x0b\x32\x19.protocols.common.RobotId\x12\x12\n\nconfidence\x18\x02 \x01(\x02\x12,\n\x08position\x18\x03 \x01(\x0b\x32\x1a.protocols.common.Point2Df\x12\r\n\x05\x61ngle\x18\x04 \x01(\x02\x12,\n\x08velocity\x18\x05 \x01(\x0b\x32\x1a.protocols.common.Point2Df\x12\x18\n\x10\x61ngular_velocity\x18\x06 \x01(\x02\"\xb8\x01\n\x10SourceCapability\x12!\n\x1dSOURCE_CAPABILITY_UNSPECIFIED\x10\x00\x12)\n%SOURCE_CAPABILITY_DETECT_FLYING_BALLS\x10\x01\x12+\n\'SOURCE_CAPABILITY_DETECT_MULTIPLE_BALLS\x10\x02\x12)\n%SOURCE_CAPABILITY_DETECT_KICKED_BALLS\x10\x03\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protocols.playback.tracked_detection_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_TRACKEDDETECTION'].fields_by_name['source_capabilities']._loaded_options = None
  _globals['_TRACKEDDETECTION'].fields_by_name['source_capabilities']._serialized_options = b'\020\001'
  _globals['_TRACKEDDETECTION']._serialized_start=166
  _globals['_TRACKEDDETECTION']._serialized_end=1437
  _globals['_TRACKEDDETECTION_BALL']._serialized_start=468
  _globals['_TRACKEDDETECTION_BALL']._serialized_end=1042
  _globals['_TRACKEDDETECTION_BALL_KICKINFORMATION']._serialized_start=679
  _globals['_TRACKEDDETECTION_BALL_KICKINFORMATION']._serialized_end=1021
  _globals['_TRACKEDDETECTION_ROBOT']._serialized_start=1045
  _globals['_TRACKEDDETECTION_ROBOT']._serialized_end=1250
  _globals['_TRACKEDDETECTION_SOURCECAPABILITY']._serialized_start=1253
  _globals['_TRACKEDDETECTION_SOURCECAPABILITY']._serialized_end=1437
# @@protoc_insertion_point(module_scope)
