# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vins:msg/FeatureQuality.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_FeatureQuality(type):
    """Metaclass of message 'FeatureQuality'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vins')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vins.msg.FeatureQuality')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__feature_quality
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__feature_quality
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__feature_quality
            cls._TYPE_SUPPORT = module.type_support_msg__msg__feature_quality
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__feature_quality

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class FeatureQuality(metaclass=Metaclass_FeatureQuality):
    """Message class 'FeatureQuality'."""

    __slots__ = [
        '_header',
        '_tracked',
        '_long_tracks_gt_5',
        '_new_features',
        '_total',
        '_visual_features',
        '_vx',
        '_vy',
        '_vz',
        '_velocity_norm',
        '_ba_x',
        '_ba_y',
        '_ba_z',
        '_ba_norm',
        '_bg_x',
        '_bg_y',
        '_bg_z',
        '_bg_norm',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'tracked': 'int32',
        'long_tracks_gt_5': 'int32',
        'new_features': 'int32',
        'total': 'int32',
        'visual_features': 'int32',
        'vx': 'double',
        'vy': 'double',
        'vz': 'double',
        'velocity_norm': 'double',
        'ba_x': 'double',
        'ba_y': 'double',
        'ba_z': 'double',
        'ba_norm': 'double',
        'bg_x': 'double',
        'bg_y': 'double',
        'bg_z': 'double',
        'bg_norm': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.tracked = kwargs.get('tracked', int())
        self.long_tracks_gt_5 = kwargs.get('long_tracks_gt_5', int())
        self.new_features = kwargs.get('new_features', int())
        self.total = kwargs.get('total', int())
        self.visual_features = kwargs.get('visual_features', int())
        self.vx = kwargs.get('vx', float())
        self.vy = kwargs.get('vy', float())
        self.vz = kwargs.get('vz', float())
        self.velocity_norm = kwargs.get('velocity_norm', float())
        self.ba_x = kwargs.get('ba_x', float())
        self.ba_y = kwargs.get('ba_y', float())
        self.ba_z = kwargs.get('ba_z', float())
        self.ba_norm = kwargs.get('ba_norm', float())
        self.bg_x = kwargs.get('bg_x', float())
        self.bg_y = kwargs.get('bg_y', float())
        self.bg_z = kwargs.get('bg_z', float())
        self.bg_norm = kwargs.get('bg_norm', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.tracked != other.tracked:
            return False
        if self.long_tracks_gt_5 != other.long_tracks_gt_5:
            return False
        if self.new_features != other.new_features:
            return False
        if self.total != other.total:
            return False
        if self.visual_features != other.visual_features:
            return False
        if self.vx != other.vx:
            return False
        if self.vy != other.vy:
            return False
        if self.vz != other.vz:
            return False
        if self.velocity_norm != other.velocity_norm:
            return False
        if self.ba_x != other.ba_x:
            return False
        if self.ba_y != other.ba_y:
            return False
        if self.ba_z != other.ba_z:
            return False
        if self.ba_norm != other.ba_norm:
            return False
        if self.bg_x != other.bg_x:
            return False
        if self.bg_y != other.bg_y:
            return False
        if self.bg_z != other.bg_z:
            return False
        if self.bg_norm != other.bg_norm:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def tracked(self):
        """Message field 'tracked'."""
        return self._tracked

    @tracked.setter
    def tracked(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'tracked' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'tracked' field must be an integer in [-2147483648, 2147483647]"
        self._tracked = value

    @builtins.property
    def long_tracks_gt_5(self):
        """Message field 'long_tracks_gt_5'."""
        return self._long_tracks_gt_5

    @long_tracks_gt_5.setter
    def long_tracks_gt_5(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'long_tracks_gt_5' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'long_tracks_gt_5' field must be an integer in [-2147483648, 2147483647]"
        self._long_tracks_gt_5 = value

    @builtins.property
    def new_features(self):
        """Message field 'new_features'."""
        return self._new_features

    @new_features.setter
    def new_features(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'new_features' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'new_features' field must be an integer in [-2147483648, 2147483647]"
        self._new_features = value

    @builtins.property
    def total(self):
        """Message field 'total'."""
        return self._total

    @total.setter
    def total(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'total' field must be an integer in [-2147483648, 2147483647]"
        self._total = value

    @builtins.property
    def visual_features(self):
        """Message field 'visual_features'."""
        return self._visual_features

    @visual_features.setter
    def visual_features(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'visual_features' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'visual_features' field must be an integer in [-2147483648, 2147483647]"
        self._visual_features = value

    @builtins.property
    def vx(self):
        """Message field 'vx'."""
        return self._vx

    @vx.setter
    def vx(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'vx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vx = value

    @builtins.property
    def vy(self):
        """Message field 'vy'."""
        return self._vy

    @vy.setter
    def vy(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'vy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vy = value

    @builtins.property
    def vz(self):
        """Message field 'vz'."""
        return self._vz

    @vz.setter
    def vz(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'vz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vz = value

    @builtins.property
    def velocity_norm(self):
        """Message field 'velocity_norm'."""
        return self._velocity_norm

    @velocity_norm.setter
    def velocity_norm(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'velocity_norm' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'velocity_norm' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._velocity_norm = value

    @builtins.property
    def ba_x(self):
        """Message field 'ba_x'."""
        return self._ba_x

    @ba_x.setter
    def ba_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ba_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ba_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ba_x = value

    @builtins.property
    def ba_y(self):
        """Message field 'ba_y'."""
        return self._ba_y

    @ba_y.setter
    def ba_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ba_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ba_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ba_y = value

    @builtins.property
    def ba_z(self):
        """Message field 'ba_z'."""
        return self._ba_z

    @ba_z.setter
    def ba_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ba_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ba_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ba_z = value

    @builtins.property
    def ba_norm(self):
        """Message field 'ba_norm'."""
        return self._ba_norm

    @ba_norm.setter
    def ba_norm(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ba_norm' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ba_norm' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ba_norm = value

    @builtins.property
    def bg_x(self):
        """Message field 'bg_x'."""
        return self._bg_x

    @bg_x.setter
    def bg_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bg_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bg_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bg_x = value

    @builtins.property
    def bg_y(self):
        """Message field 'bg_y'."""
        return self._bg_y

    @bg_y.setter
    def bg_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bg_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bg_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bg_y = value

    @builtins.property
    def bg_z(self):
        """Message field 'bg_z'."""
        return self._bg_z

    @bg_z.setter
    def bg_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bg_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bg_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bg_z = value

    @builtins.property
    def bg_norm(self):
        """Message field 'bg_norm'."""
        return self._bg_norm

    @bg_norm.setter
    def bg_norm(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bg_norm' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bg_norm' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bg_norm = value
