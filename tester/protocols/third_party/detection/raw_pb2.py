# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protocols/third_party/detection/raw.proto
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
    'protocols/third_party/detection/raw.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)protocols/third_party/detection/raw.proto\x12\x1fprotocols.third_party.detection\"x\n\x11SSL_DetectionBall\x12\x12\n\nconfidence\x18\x01 \x02(\x02\x12\x0c\n\x04\x61rea\x18\x02 \x01(\r\x12\t\n\x01x\x18\x03 \x02(\x02\x12\t\n\x01y\x18\x04 \x02(\x02\x12\t\n\x01z\x18\x05 \x01(\x02\x12\x0f\n\x07pixel_x\x18\x06 \x02(\x02\x12\x0f\n\x07pixel_y\x18\x07 \x02(\x02\"\x97\x01\n\x12SSL_DetectionRobot\x12\x12\n\nconfidence\x18\x01 \x02(\x02\x12\x10\n\x08robot_id\x18\x02 \x01(\r\x12\t\n\x01x\x18\x03 \x02(\x02\x12\t\n\x01y\x18\x04 \x02(\x02\x12\x13\n\x0borientation\x18\x05 \x01(\x02\x12\x0f\n\x07pixel_x\x18\x06 \x02(\x02\x12\x0f\n\x07pixel_y\x18\x07 \x02(\x02\x12\x0e\n\x06height\x18\x08 \x01(\x02\"\xd3\x02\n\x12SSL_DetectionFrame\x12\x14\n\x0c\x66rame_number\x18\x01 \x02(\r\x12\x11\n\tt_capture\x18\x02 \x02(\x01\x12\x0e\n\x06t_sent\x18\x03 \x02(\x01\x12\x18\n\x10t_capture_camera\x18\x08 \x01(\x01\x12\x11\n\tcamera_id\x18\x04 \x02(\r\x12\x41\n\x05\x62\x61lls\x18\x05 \x03(\x0b\x32\x32.protocols.third_party.detection.SSL_DetectionBall\x12J\n\rrobots_yellow\x18\x06 \x03(\x0b\x32\x33.protocols.third_party.detection.SSL_DetectionRobot\x12H\n\x0brobots_blue\x18\x07 \x03(\x0b\x32\x33.protocols.third_party.detection.SSL_DetectionRobot')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protocols.third_party.detection.raw_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_SSL_DETECTIONBALL']._serialized_start=78
  _globals['_SSL_DETECTIONBALL']._serialized_end=198
  _globals['_SSL_DETECTIONROBOT']._serialized_start=201
  _globals['_SSL_DETECTIONROBOT']._serialized_end=352
  _globals['_SSL_DETECTIONFRAME']._serialized_start=355
  _globals['_SSL_DETECTIONFRAME']._serialized_end=694
# @@protoc_insertion_point(module_scope)
