# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: GPTelemetry.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='GPTelemetry.proto',
  package='',
  serialized_pb='\n\x11GPTelemetry.proto\"\x91\x02\n\tTelemetry\x12\x11\n\tunix_time\x18\x01 \x02(\r\x12\x0b\n\x03lon\x18\x02 \x02(\x01\x12\x0b\n\x03lat\x18\x03 \x02(\x01\x12\x10\n\x08\x61lt_baro\x18\x04 \x02(\x02\x12\x0f\n\x07\x61lt_gps\x18\x05 \x02(\x02\x12\x0c\n\x04roll\x18\x06 \x02(\x02\x12\r\n\x05pitch\x18\x07 \x02(\x02\x12\x12\n\ngps_course\x18\x08 \x02(\x02\x12\x12\n\nmag_course\x18\t \x02(\x02\x12\x11\n\tgps_speed\x18\n \x02(\x02\x12\x11\n\tair_speed\x18\x0b \x02(\x02\x12\x18\n\x10navmode_navphase\x18\x0c \x01(\r\x12\x15\n\rlzp_deviation\x18\r \x01(\x02\x12\x18\n\x10\x63ourse_deviation\x18\x0e \x01(\x02')




_TELEMETRY = _descriptor.Descriptor(
  name='Telemetry',
  full_name='Telemetry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='unix_time', full_name='Telemetry.unix_time', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='lon', full_name='Telemetry.lon', index=1,
      number=2, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='lat', full_name='Telemetry.lat', index=2,
      number=3, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='alt_baro', full_name='Telemetry.alt_baro', index=3,
      number=4, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='alt_gps', full_name='Telemetry.alt_gps', index=4,
      number=5, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='roll', full_name='Telemetry.roll', index=5,
      number=6, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='pitch', full_name='Telemetry.pitch', index=6,
      number=7, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='gps_course', full_name='Telemetry.gps_course', index=7,
      number=8, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='mag_course', full_name='Telemetry.mag_course', index=8,
      number=9, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='gps_speed', full_name='Telemetry.gps_speed', index=9,
      number=10, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='air_speed', full_name='Telemetry.air_speed', index=10,
      number=11, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='navmode_navphase', full_name='Telemetry.navmode_navphase', index=11,
      number=12, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='lzp_deviation', full_name='Telemetry.lzp_deviation', index=12,
      number=13, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='course_deviation', full_name='Telemetry.course_deviation', index=13,
      number=14, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=22,
  serialized_end=295,
)

DESCRIPTOR.message_types_by_name['Telemetry'] = _TELEMETRY

class Telemetry(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _TELEMETRY

  # @@protoc_insertion_point(class_scope:Telemetry)


# @@protoc_insertion_point(module_scope)
