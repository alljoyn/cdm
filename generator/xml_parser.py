# Copyright AllSeen Alliance. All rights reserved.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import xml.parsers.expat
import xml.sax
import re
import string
import inspect
from collections import namedtuple


class Symbol(object):
    """
    Used to wrap a string and allow it to be converted to various formats...
    Examples of future usages:
        s = Symbol("FooBar")
        s.upper() -> "FOOBAR"
        s.snake() -> "foo_bar"

    """
    def __init__(self, string):
        self.string = string

    def __str__(self):
        return self.string

    def upper(self):
        return self.string.upper()

    def split_camel_case(self, seperator):
        str = ""
        for c in self.string:
            if c in string.ascii_uppercase and str and str[-1] not in string.ascii_uppercase:
                str = str + seperator + c
            else:
                str = str + c
        return str.lower()

    def snake(self):
        return self.split_camel_case("_").lower()

    def upper_snake(self):
        return self.snake().upper()

    def camel_case(self):
        str = ""
        for c in self.string:
            if c in string.ascii_uppercase and str and str[-1] not in string.ascii_uppercase:
                str = str + c.upper()
            else:
                str = str + c.lower()
        return str

    def add_spaces(self):
        return self.split_camel_case(" ")

    def add_spaces_upper(self):
        return self.add_spaces().upper()

    def add_spaces_lower(self):
        return self.add_spaces().lower()

    def __eq__(self, other):
        return str(self) == str(other)


def _padded_tag_replacement(value, prefix=""):
    func_name = inspect.stack()[1][3]
    full_name = prefix + "." + func_name if prefix else func_name
    return "{0: <{1}}".format(value, len(full_name) + 4)


class Padder(object):
    def __getattr__(self, item):
        baseattr, padto = item.split('*')
        s = self.__str__() if not len(baseattr) else self.__getattribute__(str(baseattr))
        return "{value: <{pad}}".format(value=s() if callable(s) else s, pad=padto)


class AJType(object):
    CTypeMap = {
        's': 'qcc::String',
        'b': 'bool',
        'y': 'uint8_t',
        'n': 'int16_t',
        'q': 'uint16_t',
        'i': 'int32_t',
        'u': 'uint32_t',
        'x': 'int64_t',
        't': 'uint64_t',
        'd': 'double',
        'o': 'qcc::String',  # Object Path
    }

    AJTypeIdMap = {
        'b': 'ALLJOYN_BOOLEAN',
        'd': 'ALLJOYN_DOUBLE',
        'e': 'ALLJOYN_DICT_ENTRY',
        'g': 'ALLJOYN_SIGNATURE',
        'h': 'ALLJOYN_HANDLE',
        'i': 'ALLJOYN_INT32',
        'n': 'ALLJOYN_INT16',
        'o': 'ALLJOYN_OBJECT_PATH',
        'q': 'ALLJOYN_UINT16',
        'r': 'ALLJOYN_STRUCT',
        's': 'ALLJOYN_STRING',
        't': 'ALLJOYN_UINT64',
        'u': 'ALLJOYN_UINT32',
        'v': 'ALLJOYN_VARIANT',
        'x': 'ALLJOYN_INT64',
        'y': 'ALLJOYN_BYTE',
    }

    AJTypeVarMap = {
        'y': 'byte',
        'n': 'int16',
        'q': 'uint16',
        'b': 'bool',
        'u': 'uint32',
        'i': 'int32',
        'x': 'int64',
        't': 'uint64',
        'd': 'double',
        's': 'string',
        'o': 'objPath',
        'g': 'signature',
        'h': 'handle',
        'a': 'array',
        'r': 'struct',
        'v': 'variant',
    }

    JavaTypePrimitiveMap = {
        's': 'String',
        'b': 'boolean',
        'y': 'byte',
        'n': 'short',
        'q': 'short', # unsigned 16 bit integer in java?
        'i': 'int',
        'u': 'int', # unsigned 32 bit integer in java?
        'x': 'long',
        't': 'long', # unsigned 64 bit integer in java?
        'd': 'double',
        'o': 'String',
    }

    JavaTypeClassMap = {
        's': 'String',
        'b': 'Boolean',
        'y': 'Byte',
        'n': 'Short',
        'q': 'Short', # unsigned 16 bit integer in java?
        'i': 'Integer',
        'u': 'Integer', # unsigned 32 bit integer in java?
        'x': 'Long',
        't': 'Long', # unsigned 64 bit integer in java?
        'd': 'Double',
        'o': 'String',
    }

    def __init__(self, signature, parent_interface=None):
        self.annotated_type = None
        self.signature = signature
        self.parent_interface = parent_interface

    def ajtypeid(self):
        return self.AJTypeIdMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def ajtype(self):
        return _padded_tag_replacement(self.AJTypeVarMap.get(self.signature, "unknown"), "PropertyType")

    def ajtype_primitive(self):
        type = self.signature

        if type.startswith('a'):
            type = type[1:]

        if type.startswith('[') and type.endswith(']'):
            if self.parent_interface:
                for enum in self.parent_interface.enums:
                    if enum.EnumName == type[1:-1] and enum.enum_type:
                        return str(enum.enum_type)

            # default to integer primitive
            return 'i'

        return type

    def ajvar(self):
        return "v_" + self.AJTypeVarMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def ctype(self, arg=False):
        template = None

        ajtype = self.annotated_type if self.annotated_type else self.signature

        if ajtype.startswith("a"):
            template = "std::vector"
            ajtype = ajtype[1:]

        if ajtype.startswith('[') and ajtype.endswith(']'):
            ctype = ajtype[1:-1]
        else:
            ctype = self.CTypeMap.get(ajtype, "/* TODO:%{} */".format(ajtype))

        if template:
            return template + "<" + ctype + ">" + ("&" if arg else "")

        if arg and ctype=="qcc::String":
            return ctype + "&"

        return ctype

    def ctype_arg(self):
        return self.ctype(arg=True)

    def javatype(self):
        array = False

        ajtype = self.annotated_type if self.annotated_type else self.signature

        if ajtype.startswith("a"):
            array = True
            ajtype = ajtype[1:]

        if ajtype.startswith('[') and ajtype.endswith(']'):
            javatype = ajtype[1:-1]
        else:
            javatype = self.JavaTypePrimitiveMap.get(ajtype, "/* TODO:%{} */".format(ajtype))

        if array:
            return javatype + "[]"

        return javatype

    def javatype_primitive(self):
        type = self.signature
        array = False

        if type.startswith('a'):
            array = True
            type = type[1:]

        type = self.JavaTypePrimitiveMap.get(type, None)

        if not type:
            type = self.JavaTypePrimitiveMap.get(self.ajtype_primitive(), None)

        if array and type:
            return type + "[]"

        return type

    def javatype_class(self):
        return self.JavaTypeClassMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def set_annotated_type(self, value):
        self.annotated_type = value

    def __str__(self):
        return self.signature


class InterfaceEnum(object):
    EnumEntry = namedtuple("EnumEntry", "EnumValueName EnumValue Last")

    def __init__(self, name, interface):
        self.EnumName = Symbol(name)
        self.values = []
        self.parent_interface = interface

    def reset_last_value(self):
        for i in xrange(len(self.values)):
            enum_entry = self.values[i]
            # I feel wasteful, I wish I could mutate you :(
            self.values[i] = InterfaceEnum.EnumEntry(enum_entry.EnumValueName, enum_entry.EnumValue, False)

    def add_value(self, enumerator, value):
        self.reset_last_value()
        enum_value_name = remove_special_chars(str(enumerator))
        self.values.append(InterfaceEnum.EnumEntry(Symbol(enum_value_name), value, True))

    @property
    def enum_type(self):
        name = '['+str(self.EnumName)+']'

        for property in self.parent_interface.properties:
            for annotation in property.annotations:
                if annotation.AnnotationValue == name:
                    return property.PropertyType

        for method in self.parent_interface.methods:
            for method_arg in method.args:
                for annotation in method_arg.annotations:
                    if annotation.AnnotationValue == name:
                        return method_arg.ArgType

        return None


class InterfaceStruct(object):
    StructField = namedtuple("StructField", "FieldType FieldName FieldPosition")

    def __init__(self, name):
        self.StructName = name
        self.fields = []

    def add_field(self, name, type, interface):
        self.fields.append(InterfaceStruct.StructField(AJType(type, interface), name, len(self.fields)))


class Interface(object):
    def __init__(self, name):
        self.InterfaceName = Symbol(name.split(".")[-1])
        self.InterfaceCategory = Symbol(name.split(".")[-2].lower())
        self.FullInterfaceName = name
        self.Secure = None
        self.Version = None
        self.version = lambda: "{0:<11}".format(self.Version)
        self.annotations = []
        self.structs = []
        self.enums = []
        self.properties = []
        self.methods = []
        self.signals = []
        self.doc = {}

    def user_properties(self):
        return filter(lambda x: str(x.PropertyName) != "Version", self.properties)

    def set_secure(self, value):
        self.Secure = bool(value)

    def set_doc_string(self, language, value):
        self.doc[language.lower()] = value

    def add_struct_field(self, struct_name, field, field_type):
        struct = None
        for s in self.structs:
            if s.StructName == struct_name:
                struct = s
                break
        if struct is None:
            struct = InterfaceStruct(struct_name)
            self.structs.append(struct)
        struct.add_field(field, field_type, self)

    def add_enum_value(self, enum_name, enumerator, value):
        enum = None
        for e in self.enums:
            if e.EnumName == enum_name:
                enum = e
                break
        if enum is None:
            enum = InterfaceEnum(enum_name, self)
            self.enums.append(enum)

        enum.add_value(enumerator, value)

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.Secure'):
                lambda m: self.set_secure(value),

            re.compile(r'org\.alljoyn\.Bus\.DocString\.(\w*)'):
                lambda m: self.set_doc_string(m.group(1), value),

            re.compile(r'org\.alljoyn\.Bus\.Struct\.(\w*)\.Field\.(\w*).Type'):
                lambda m: self.add_struct_field(m.group(1), m.group(2), value),

            re.compile(r'org\.alljoyn\.Bus\.Enum\.(\w*)\.Value\.([\w\/-]*)'):
                lambda m: self.add_enum_value(m.group(1), m.group(2), value),
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown annotation:", name

    def add_child(self, child):
        if isinstance(child, Property):
            child.parent_interface = self
            self.properties.append(child)
        elif isinstance(child, Method):
            self.methods.append(child)
        elif isinstance(child, Signal):
            self.signals.append(child)
        elif isinstance(child, Annotation):
            self.annotations.append(child)
            self.add_annotation(child.AnnotationName, child.AnnotationValue)
        else:
            print "Unexpected: ", child


class Property(object):
    def __init__(self, name, type, access):
        self.PropertyName = Symbol(name)
        self.PropertyType = AJType(type)
        self.PropertyAccess = access
        self.doc = {}
        self.EmitsChangedSignal = False
        self.Const = False
        self.PropertyWritable = "write" in self.PropertyAccess
        self.annotations = []
        self.min = None 
        self.max = None 
        self.units = None
        self.parent_interface = None

    def emit_changed(self):
        return _padded_tag_replacement(self.EmitsChangedSignal)

    def property_access(self):
        return _padded_tag_replacement(self.PropertyAccess)

    def set_doc_string(self, language, value):
        self.doc[language.lower()] = value

    def set_emits_changed_signal(self, value):
        if value.lower() == "true":
            self.EmitsChangedSignal = True
            self.Const = False
        elif value.lower == "false":
            self.EmitsChangedSignal = False
            self.Const = False
        elif value.lower == "const":
            self.EmitsChangedSignal = False
            self.Const = True


    def get_emits_changed_signal(self):
        return self.EmitsChangedSignal

    def set_min(self, value): 
        self.min = value 
 
    def set_max(self, value): 
        self.min = value 
 
    def set_units(self, units): 
        self.units = units

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.DocString\.(\w*)'):
                lambda m: self.set_doc_string(m.group(1), value),

            re.compile(r'org\.freedesktop\.DBus\.Property\.EmitsChangedSignal'):
                lambda m: self.set_emits_changed_signal(value),

            re.compile(r'org\.alljoyn\.Bus\.Type\.Name'):
                lambda m: self.PropertyType.set_annotated_type(value),

            re.compile(r'org\.alljoyn\.Bus\.Type\.Min'): 
                lambda m: self.set_min(value), 
 
            re.compile(r'org\.alljoyn\.Bus\.Type\.Max'): 
                lambda m: self.set_max(value), 
 
            re.compile(r'org\.alljoyn\.Bus\.Type\.Units'): 
                lambda m: self.set_units(value), 
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown annotation:", name

    def add_child(self, child):
        if isinstance(child, Annotation):
            self.annotations.append(child)
            self.add_annotation(child.AnnotationName, child.AnnotationValue)

    def is_bool(self):
        return self.PropertyType.signature == 'b'

    def is_enum(self):
        annotation_values = [annotation.AnnotationValue for annotation in self.annotations]
        for enum in self.parent_interface.enums:
            for value in annotation_values:
                if str(enum.EnumName) in value:
                    return True
        return False

    def enum_name(self):
        for enum in self.parent_interface.enums:
            for annotation in self.annotations:
                if str(enum.EnumName) in annotation.AnnotationValue and 'org.alljoyn.Bus.Type.Name' == annotation.AnnotationName:
                    name = annotation.AnnotationValue
                    if name[0] == 'a' and name[1] == '[':
                        name = name.strip('a')
                    return name.strip('[]')
        return None

    def android_property_view_type(self):
        if self.PropertyWritable:
            if self.is_bool():
                return 'ReadWriteBoolPropertyView'
            elif self.is_enum():
                return 'ReadWriteEnumPropertyView'
            else:
                return 'ReadWriteValuePropertyView'
        else:
            if self.is_enum():
                return 'ReadOnlyEnumPropertyView'
            return 'ReadOnlyValuePropertyView'

    def android_property_view_signature(self):
        if self.is_bool():
            return 'this, this.intf, "%s"' % self.PropertyName
        elif self.is_enum():
            return 'this, this.intf, "%s", %s.%s.class' % (self.PropertyName, self.parent_interface.InterfaceName, self.enum_name())
        else:
            return 'this, this.intf, "%s", null' % self.PropertyName


class Method(object):
    def __init__(self, name):
        self.MethodName = Symbol(name)
        self.args = [] 
 
    def add_arg(self, arg): 
        self.args.append(arg) 
 
    def add_child(self, child): 
        if isinstance(child, MethodArg): 
            self.add_arg(child)

    def input_args(self):
        args = [arg for arg in self.args if arg.ArgDirection == 'in']
        if len(args) > 0:
            map(lambda x:setattr(x, 'last', False), args)
            setattr(args[-1], 'last', True)
        return args

    def output_arg(self):
        try:
            return [arg for arg in self.args if arg.ArgDirection == 'out'][0]
        except IndexError:
            return None

    def input_signature(self):
        return ''.join([str(arg.ArgType) for arg in self.args if arg.ArgDirection == 'in'])

    def output_signature(self):
        return ''.join([str(arg.ArgType) for arg in self.args if arg.ArgDirection == 'out'])


class MethodArg(object):
    def __init__(self, name, type, direction):
        self.ArgName = Symbol(name) 
        self.ArgType = AJType(type)
        self.ArgDirection = direction
        self.annotations = []

    def add_child(self, child):
        if isinstance(child, Annotation):
            self.annotations.append(child)
            self.add_annotation(child.AnnotationName, child.AnnotationValue)

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.Type\.Name'):
                lambda m: self.ArgType.set_annotated_type(value),
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown annotation:", name


class Signal(object):
    def __init__(self, name, sessionless):
        self.SignalName = Symbol(name)
        self.SignalSessionless = sessionless.lower()=="true"

    def add_child(self, child):
        pass


class Annotation(Padder):
    def __init__(self, name, value):
        self.AnnotationName = name
        self.AnnotationValue = value

    def __str__(self):
        return "{} = {}".format(self.AnnotationName, self.AnnotationValue)

# Description is deprecated for DocString annotation
class Description(object):
    def __init__(self, language):
        self.language = language


class Root(object):
    def __init__(self, **kwargs):
        self.list = []

    def add_child(self, child):
        self.list.append(child)


class AJXMLParser(xml.sax.handler.ContentHandler):
    Elements = {
        # Element Name  # (HandlerClass, [list, of, valid, parents])
        "node":         (Root, [type(None)]),
        "interface":    (Interface, [Root]),
        "property":     (Property, [Interface]),
        "method":       (Method, [Interface]),
        "signal":       (Signal, [Interface]),
        "annotation":   (Annotation, [Interface, Property, Method, MethodArg, Signal]),
        "arg":          (MethodArg, [Method]),
        "description":  (Description, [Interface, Property, Method, MethodArg, Signal]),
    }

    def __init__(self):
        xml.sax.handler.ContentHandler.__init__(self)
        self.stack = []
        self.root = None
        self.current_name = None

    def startElement(self, name, attrs):
        self.current_name = name

        attr_dict = {k: attrs.getValue(k) for k in attrs.getNames()}

        # print "  " * (len(self.stack)+1), name, attrDict

        if name not in self.Elements:
            raise Exception("Unsupported XML element '%s'" % name)

        parent = self.stack[-1] if self.stack else None

        ctor, valid_parents = self.Elements[name]

        if parent.__class__ not in valid_parents:
            raise Exception("Unexpected XML element '%s' under '%s'" % (name, parent.__class__))

        try:
            obj = ctor(**attr_dict)
            self.stack.append(obj)
        except TypeError as e:
            # If ctor fails it'll throw a cryptic exception, add a bit of useful information to it
            raise TypeError("%s (Trying to construct %s(%s))" % (e.message, ctor, attr_dict.keys()))

    def endElement(self, name):
        child = self.stack.pop()
        parent = self.stack[-1] if self.stack else None
        if parent is not None:
            parent.add_child(child)
        else:
            self.root = child
        self.current_name = None


class AboutDataString(object):
    def __init__(self, lang='en'):
        self.key = None
        self.value = None
        self.lang = lang

    def add_child(self, child):
        pass


class AboutData(object):
    def __init__(self):
        self.data = []
        self.device_type_desc = None

    def add_child(self, child):
        if isinstance(child, AboutDataString):
            self.data.append(child)
        elif isinstance(child, DeviceTypeDescription):
            self.device_type_desc = child

    def find_element(self, key):
        for element in self.data:
            if element.key == key:
                return element

    def get_value(self, key):
        return self.find_element(key).value

    @property
    def AppId(self):
        return self.get_value('AppId')

    @property
    def DefaultLanguage(self):
        return self.get_value('DefaultLanguage')

    @property
    def DeviceName(self):
        return self.get_value('DeviceName')

    @property
    def DeviceId(self):
        return self.get_value('DeviceId')

    @property
    def AppName(self):
        return self.get_value('AppName')

    @property
    def Manufacturer(self):
        return self.get_value('Manufacturer')

    @property
    def ModelNumber(self):
        return self.get_value('ModelNumber')

    @property
    def Description(self):
        return self.get_value('Description')

    @property
    def DateOfManufacture(self):
        return self.get_value('DateOfManufacture')

    @property
    def SoftwareVersion(self):
        return self.get_value('SoftwareVersion')

    @property
    def HardwareVersion(self):
        return self.get_value('HardwareVersion')

    @property
    def SupportUrl(self):
        return self.get_value('SupportUrl')

    @property
    def UserDefinedTag(self):
        return self.get_value('UserDefinedTag')

    @property
    def CountryOfProduction(self):
        return self.get_value('CountryOfProduction')

    @property
    def Location(self):
        return self.get_value('Location')

    @property
    def CorporateBrand(self):
        return self.get_value('CorporateBrand')

    @property
    def ProductBrand(self):
        return self.get_value('ProductBrand')

    @property
    def DeviceTypeDescription(self):
        return self.device_type_desc


class DeviceTypeDescription(object):
    def __init__(self):
        self.data = None

    def add_child(self, child):
        if isinstance(child, TypeDescription):
            self.data = child


class TypeDescription(object):
    def __init__(self):
        self.device_type = None
        self.object_path = None

    def add_child(self, child):
        if isinstance(child, DeviceType):
            self.device_type = child
        elif isinstance(child, DeviceTypeObjectPath):
            self.object_path = child


class DeviceType(object):
    def __init__(self):
        self.value = None

    def __str__(self):
        return self.value


class DeviceTypeObjectPath(object):
    def __init__(self):
        self.value = None

    def __str__(self):
        return self.value


class InterfaceList(object):
    def __init__(self):
        self.objects = []

    def add_child(self, child):
        if isinstance(child, ObjectPath):
            self.objects.append(child)


class ObjectPath(object):
    def __init__(self, path):
        self.Path = path
        self.interfaces = []

    def add_child(self, child):
        if isinstance(child, Interface):
            self.interfaces.append(child)


class Device(Root):
    def __init__(self, name):
        self.DeviceName = Symbol(name)
        self.interface_list = []
        self.about_data = None

    def add_child(self, child):
        if isinstance(child, InterfaceList):
            self.interface_list.append(child)
        elif isinstance(child, AboutData):
            self.about_data = child

    @property
    def interfaces(self):
        filtered_interfaces = []
        for list in self.interface_list:
            for object in list.objects:
                for interf in object.interfaces:
                    if interf not in filtered_interfaces:
                        setattr(interf, 'last', False)
                        filtered_interfaces.append(interf)

        # set a 'last' property on the last interface of the list
        # to remove the trailing comma from cpp constructor initializer list
        last_interface = filtered_interfaces[-1]
        setattr(last_interface, 'last', True)

        return filtered_interfaces


class AJEmulatorXMLParser(AJXMLParser, object):
    Elements = {
        # Element Name  # (HandlerClass, [list, of, valid, parents])
        "DeviceEmulator":       (Device, [type(None)]),
        "AboutData":            (AboutData, [Device]),
        "AppId":                (AboutDataString, [AboutData]),
        "DefaultLanguage":      (AboutDataString, [AboutData]),
        "DeviceName":           (AboutDataString, [AboutData]),
        "DeviceId":             (AboutDataString, [AboutData]),
        "AppName":              (AboutDataString, [AboutData]),
        "Manufacturer":         (AboutDataString, [AboutData]),
        "ModelNumber":          (AboutDataString, [AboutData]),
        "Description":          (AboutDataString, [AboutData]),
        "DateOfManufacture":    (AboutDataString, [AboutData]),
        "SoftwareVersion":      (AboutDataString, [AboutData]),
        "HardwareVersion":      (AboutDataString, [AboutData]),
        "SupportUrl":           (AboutDataString, [AboutData]),
        "UserDefinedTag":       (AboutDataString, [AboutData]),
        "CountryOfProduction":  (AboutDataString, [AboutData]),
        "Location":             (AboutDataString, [AboutData]),
        "CorporateBrand":       (AboutDataString, [AboutData]),
        "ProductBrand":         (AboutDataString, [AboutData]),
        "DeviceTypeDescription":(DeviceTypeDescription, [AboutData]),
        "TypeDescription":      (TypeDescription, [DeviceTypeDescription]),
        "device_type":          (DeviceType, [TypeDescription]),
        "object_path":          (DeviceTypeObjectPath, [TypeDescription]),
        "InterfaceList":        (InterfaceList, [Device]),
        "Object":               (ObjectPath, [InterfaceList]),
        "Interface":            (Interface, [ObjectPath]),
    }

    def __init__(self):
        super(AJEmulatorXMLParser, self).__init__()
        self._char_buffer = []

    def _join_buffer(self):
        element_value = ''.join(self._char_buffer).strip()
        self._char_buffer = []
        return element_value

    def characters(self, data):
        obj = self.stack[-1]
        if isinstance(obj, AboutDataString) and obj.key is None:
            obj.key = self.current_name
        self._char_buffer.append(data)

    def endElement(self, name):
        obj = self.stack[-1]
        obj.value = self._join_buffer()
        super(AJEmulatorXMLParser, self).endElement(name)


def make_parser():
    return xml.sax.make_parser()


def remove_special_chars(string):
    return filter(str.isalnum, string)