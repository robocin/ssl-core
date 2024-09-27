# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protocols/playback/raw_detection.proto
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
    'protocols/playback/raw_detection.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protocols.common import geometry_pb2 as protocols_dot_common_dot_geometry__pb2
from protocols.common import robot_id_pb2 as protocols_dot_common_dot_robot__id__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&protocols/playback/raw_detection.proto\x12\x12protocols.playback\x1a\x1fprotocols/common/geometry.proto\x1a\x1fprotocols/common/robot_id.proto\"\xd7\x03\n\x0cRawDetection\x12\x38\n\x07\x63\x61meras\x18\x01 \x03(\x0b\x32\'.protocols.playback.RawDetection.Camera\x1a\x8c\x03\n\x06\x43\x61mera\x12\x11\n\tcamera_id\x18\x01 \x01(\r\x12\x11\n\tserial_id\x18\x02 \x01(\r\x12;\n\x05\x62\x61lls\x18\x03 \x03(\x0b\x32,.protocols.playback.RawDetection.Camera.Ball\x12=\n\x06robots\x18\x04 \x03(\x0b\x32-.protocols.playback.RawDetection.Camera.Robot\x1aH\n\x04\x42\x61ll\x12\x12\n\nconfidence\x18\x01 \x01(\x02\x12,\n\x08position\x18\x02 \x01(\x0b\x32\x1a.protocols.common.Point3Df\x1a\x95\x01\n\x05Robot\x12+\n\x08robot_id\x18\x01 \x01(\x0b\x32\x19.protocols.common.RobotId\x12\x12\n\nconfidence\x18\x02 \x01(\x02\x12,\n\x08position\x18\x03 \x01(\x0b\x32\x1a.protocols.common.Point2Df\x12\r\n\x05\x61ngle\x18\x04 \x01(\x02\x12\x0e\n\x06height\x18\x05 \x01(\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protocols.playback.raw_detection_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_RAWDETECTION']._serialized_start=129
  _globals['_RAWDETECTION']._serialized_end=600
  _globals['_RAWDETECTION_CAMERA']._serialized_start=204
  _globals['_RAWDETECTION_CAMERA']._serialized_end=600
  _globals['_RAWDETECTION_CAMERA_BALL']._serialized_start=376
  _globals['_RAWDETECTION_CAMERA_BALL']._serialized_end=448
  _globals['_RAWDETECTION_CAMERA_ROBOT']._serialized_start=451
  _globals['_RAWDETECTION_CAMERA_ROBOT']._serialized_end=600
# @@protoc_insertion_point(module_scope)
