# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protocols/third_party/detection/raw_wrapper.proto
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
    'protocols/third_party/detection/raw_wrapper.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protocols.third_party.detection import geometry_pb2 as protocols_dot_third__party_dot_detection_dot_geometry__pb2
from protocols.third_party.detection import raw_pb2 as protocols_dot_third__party_dot_detection_dot_raw__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n1protocols/third_party/detection/raw_wrapper.proto\x12\x1fprotocols.third_party.detection\x1a.protocols/third_party/detection/geometry.proto\x1a)protocols/third_party/detection/raw.proto\"\xa0\x01\n\x11SSL_WrapperPacket\x12\x46\n\tdetection\x18\x01 \x01(\x0b\x32\x33.protocols.third_party.detection.SSL_DetectionFrame\x12\x43\n\x08geometry\x18\x02 \x01(\x0b\x32\x31.protocols.third_party.detection.SSL_GeometryData')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protocols.third_party.detection.raw_wrapper_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_SSL_WRAPPERPACKET']._serialized_start=178
  _globals['_SSL_WRAPPERPACKET']._serialized_end=338
# @@protoc_insertion_point(module_scope)
