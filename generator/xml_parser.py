# 
# Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
#    Source Project (AJOSP) Contributors and others.
# 
#    SPDX-License-Identifier: Apache-2.0
# 
#    All rights reserved. This program and the accompanying materials are
#    made available under the terms of the Apache License, Version 2.0
#    which accompanies this distribution, and is available at
#    http://www.apache.org/licenses/LICENSE-2.0
# 
#    Copyright 2016 Open Connectivity Foundation and Contributors to
#    AllSeen Alliance. All rights reserved.
# 
#    Permission to use, copy, modify, and/or distribute this software for
#    any purpose with or without fee is hereby granted, provided that the
#    above copyright notice and this permission notice appear in all
#    copies.
# 
#     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
#     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
#     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
#     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
#     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
#     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
#     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
#     PERFORMANCE OF THIS SOFTWARE.

import xml.parsers.expat
import xml.sax
import re
import string
from collections import namedtuple


class Symbol(object):
    """
    Used to wrap a string and allow it to be converted to various formats...
    Examples of future usages:
        s = Symbol("FooBar")
        s.upper() -> "FOOBAR"
        s.snake() -> "foo_bar"

    """
    def __init__(self, s):
        self.string = s

    def __str__(self):
        return self.string

    def capitalize(self):
        return self.string.capitalize()

    def upper(self):
        return self.string.upper()

    def split_camel_case(self, separator):
        s = ""
        for c in self.string:
            if c in string.ascii_uppercase and s and s[-1] not in (string.ascii_uppercase + string.digits + "_"):
                s = s + separator + c
            else:
                s = s + c
        return s.lower()

    def snake(self):
        return self.split_camel_case("_").lower()

    def upper_snake(self):
        return self.snake().upper()

    def camel_case(self):
        s = ""
        for c in self.string:
            if c in string.ascii_uppercase and s and s[-1] not in (string.ascii_uppercase + string.digits + "_"):
                s = s + c.upper()
            else:
                s = s + c.lower()
        return s

    def add_spaces(self):
        return self.split_camel_case(" ")

    def add_spaces_upper(self):
        return self.add_spaces().upper()

    def add_spaces_lower(self):
        return self.add_spaces().lower()

    def __eq__(self, other):
        return str(self) == str(other)


def _padded_tag_replacement(value, prefix=""):
    return value


class AJType(object):
    CppTypeMap = {
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

    TCLTypeMap = {
        's': 'char const*',
        'b': 'bool',
        'y': 'uint8_t',
        'n': 'int16_t',
        'q': 'uint16_t',
        'i': 'int32_t',
        'u': 'uint32_t',
        'x': 'int64_t',
        't': 'uint64_t',
        'd': 'double',
        'o': 'char const*',  # Object Path
    }

    # These are in the name of Array_% for predefined C array types.
    TCLArrayMap = {
        's': 'string',
        'b': 'Bool',
        'y': 'uint8',
        'n': 'int16',
        'q': 'uint16',
        'i': 'int32',
        'u': 'uint32',
        'x': 'int64',
        't': 'uint64',
        'd': 'double',
        'o': 'string',
    }

    # These are in the name of HAL encoders and decoders.
    TCLHalMap = {
        's': 'String',
        'b': 'Bool',
        'y': 'UInt',
        'n': 'Int',
        'q': 'UInt',
        'i': 'Int',
        'u': 'UInt',
        'x': 'Int',
        't': 'UInt',
        'd': 'Double',
        'o': 'String',
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
        'q': 'short',  # unsigned 16 bit integer in java?
        'i': 'int',
        'u': 'int',    # unsigned 32 bit integer in java?
        'x': 'long',
        't': 'long',   # unsigned 64 bit integer in java?
        'd': 'double',
        'o': 'String',
    }

    JavaTypeClassMap = {
        's': 'String',
        'b': 'Boolean',
        'y': 'Byte',
        'n': 'Short',
        'q': 'Short',    # unsigned 16 bit integer in java?
        'i': 'Integer',
        'u': 'Integer',  # unsigned 32 bit integer in java?
        'x': 'Long',
        't': 'Long',     # unsigned 64 bit integer in java?
        'd': 'Double',
        'o': 'String',
    }

    ObjCFormatStrMap = {
        's': 's',
        'b': '@',
        'y': 'u',
        'n': 'hd',
        'q': 'hu',
        'i': 'd',
        'u': 'u',
        'x': 'lld',
        't': 'llu',
        'd': 'f',
        'o': '@',  # Object Path
    }

    def __init__(self, signature, parent=None, sigoverride=None):
        self.annotated_type = None
        self.signature = signature
        self.sigoverride = sigoverride
        self.parent = parent

    def ajtypeid(self):
        return self.AJTypeIdMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def ajtype(self):
        return _padded_tag_replacement(self.AJTypeVarMap.get(self.signature, "unknown"), "Type")

    def ajtypeInterfaceName(self):
        interface = interface_of(self)
        return interface.Name

    def ajtypeIsArray(self, useAnnotated=True, returnType=False):
        # See if the name is 'a' followed by any signature. If so then return the signature
        ajtype = self.annotated_type if self.annotated_type and useAnnotated else self.signature
        if ajtype.startswith('a'):
            return ajtype[1:] if not returnType else AJType(ajtype[1:], parent=self.parent, sigoverride=self.sigoverride)
        return None

    def ajtypeIsArrayOfName(self):
        # See if the type is 'a' followed by a struct or enum name. If so then return the name.
        ajtype = self.annotated_type if self.annotated_type else self.signature
        if ajtype.startswith('a'):
            ajtype = ajtype[1:]
            if ajtype.startswith('[') and ajtype.endswith(']'):
                ajtype = ajtype[1:-1]
                return ajtype
        return None

    def ajtypeIsEnum(self, name=None):
        # See if the name in [Name] is an enum in this interface
        # If so then return the InterfaceEnum object, otherwise None
        if name is None:
            # like cpptype
            ajtype = self.annotated_type if self.annotated_type else self.signature

            if ajtype.startswith('[') and ajtype.endswith(']'):
                name = ajtype[1:-1]

        if name is not None:
            interface = interface_of(self)
            for enum in interface.Enums:
                if enum.Name == name:
                    return enum
        return None

    def interfaceStruct(self, name=None):
        # See if the name in [Name] is a struct in this interface
        if name is None:
            # like cpptype
            ajtype = self.annotated_type if self.annotated_type else self.signature
            if ajtype.startswith('[') and ajtype.endswith(']'):
                name = ajtype[1:-1]

        interface = interface_of(self)
        for stru in interface.Structs:
            if stru.Name == (name[1:-1] if name is not None and name.startswith('[') and name.endswith(']') else name):
                return stru
        return None

    def ajtypeIsStruct(self, name=None):
        struct = self.interfaceStruct(name)
        return AJType(struct.resolve_signature()) if struct else None

    def ajtypeStructOf(self):
        sig = self.signature
        return sig[1:-1] if sig.startswith('(') and sig.endswith(')') else None

    def ajtypeStructName(self, withIface=False, withArray=False):
        # See if this type is a struct or array of struct
        # Return the Name if so, otherwise None
        isArray = False
        ajtype = self.annotated_type if self.annotated_type else self.signature

        if ajtype.startswith('a'):
            ajtype = ajtype[1:]
            isArray = True

        if ajtype.startswith('[') and ajtype.endswith(']'):
            ajtype = ajtype[1:-1]
            if self.ajtypeIsStruct(ajtype):
                if withIface:
                    # For tcl
                    interface = interface_of(self)
                    ajtype = str(interface.Name) + "_" + ajtype
                if withArray:
                    ajtype = "Array_" + ajtype
                return ajtype
        return None

    def ajtypeIsString(self):
        return self.signature == 's' or self.signature == 'o'

    def ajtype_primitive(self):
        sig = self.signature

        if sig.startswith('a'):
            sig = sig[1:]

        if sig.startswith('[') and sig.endswith(']'):
            interface = interface_of(self)
            if interface:
                for enum in interface.Enums:
                    if enum.Name == sig[1:-1] and enum.enum_type():
                        return str(enum.enum_type())

            # default to integer primitive
            return 'i'

        return sig

    def tcltype(self, enumByName=True):
        ajtype = self.annotated_type if self.annotated_type else self.signature
        ctype = None
        array = False

        if ajtype.startswith("a"):
            array = True
            ajtype = ajtype[1:]

        if ajtype.startswith('[') and ajtype.endswith(']'):
            ajtype = ajtype[1:-1]
            if self.ajtypeIsEnum(ajtype) and not enumByName:
                # in OnSet functions we need the ctype for the signature
                ctype = self.TCLTypeMap.get(self.sigoverride, self.TCLTypeMap.get(self.signature, "/* TODO:%{} */".format(ajtype)))
            else:
                interface = interface_of(self)
                if interface:
                    ctype = str(interface.Name) + "_" + ajtype

        if ctype is None:
            if array:
                ctype = self.TCLArrayMap.get(ajtype, "/* TODO:%{} */".format(ajtype))
            else:
                ctype = self.TCLTypeMap.get(ajtype, "/* TODO:%{} */".format(ajtype))

        if array:
            ctype = "Array_" + ctype

        return ctype

    def tclMarshalSig(self):
        # Use the signature but allow overrides
        if self.sigoverride:
            return self.sigoverride
        return self.signature

    def tclArrayDescr(self):
        # Return a description of the array type for use in code e.g. Array_Alerts_AlertRecord
        # The names are expected to be in camel case. This also handles "as" for Array_string etc.
        name = self.annotated_type if self.annotated_type else self.signature

        if name.startswith("a"):
            name = name[1:]
            if name.startswith('[') and name.endswith(']'):
                name = name[1:-1]
                interface = interface_of(self)
                if interface:
                    name = str(interface.Name) + "_" + name
            else:
                name = self.TCLArrayMap.get(name, "/* TODO:%{} */".format(name))
            return "Array_" + name

        return None

    def tclTypeName(self):
        name = self.signature[1:] if self.signature.startswith("a") else self.signature
        return self.TCLArrayMap.get(name)

    def tclHalEncoder(self, decode=False):
        if decode:
            prefix = "HAL_Decode_"
        else:
            prefix = "HAL_Encode_"

        if self.ajtypeIsEnum():
            value = self.TCLHalMap.get(self.sigoverride, self.TCLHalMap.get(self.signature, None))
            return prefix + (value if value else "Int")

        # Arrays are represented by "Array_%" where % is from TCLArrayMap
        if self.ajtypeIsArray():
            return prefix + self.tclArrayDescr()

        if self.ajtypeStructName():
            return prefix + self.ajtypeStructName(withIface=True, withArray=True)

        return prefix + self.TCLHalMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def cpptype(self, arg=False):
        template = None

        ajtype = self.annotated_type if self.annotated_type else self.signature

        if ajtype.startswith("a"):
            template = "std::vector"
            ajtype = ajtype[1:]

        if ajtype.startswith('[') and ajtype.endswith(']'):
            cpptype = ajtype[1:-1]
            interface = interface_of(self)
            if interface and (self.ajtypeIsEnum(cpptype) or self.ajtypeIsStruct(cpptype)):
                cpptype = "%sInterface::%s" % (interface.Name, cpptype)
        else:
            cpptype = self.CppTypeMap.get(ajtype, "/* TODO:%{} */".format(ajtype))

        if template:
            return template + "<" + cpptype + ">" + ("&" if arg else "")

        if arg and cpptype == "qcc::String":
            return cpptype + "&"

        return cpptype

    def cpptype_arg(self):
        return self.cpptype(arg=True)

    def cpp_signature_type(self, signatureToSearch=None):
        ajtype = signatureToSearch if signatureToSearch else self.signature
        return self.CppTypeMap.get(ajtype, "/* TODO:%{} */".format(ajtype))

    def msgType(self):
        # This is the type that an arg to MsgArg.Get/Set must be.
        ajtype = self.annotated_type if self.annotated_type else self.signature

        if ajtype.startswith("a"):
            return "ERROR_ARRAY"

        if ajtype.startswith('[') and ajtype.endswith(']'):
            cpptype = ajtype[1:-1]
            interface = interface_of(self)

            if interface and self.ajtypeIsStruct(cpptype):
                return "ERROR_STRUCT"

            if interface and self.ajtypeIsEnum(cpptype):
                for annotation in interface.Annotations:
                    if annotation.Name.find("org.twobulls.Struct") != -1:
                        if annotation.Name.lower().find(cpptype.lower()) != -1:
                            if annotation.Name.find(".Sig") != -1:
                                cpptype = self.cpp_signature_type(annotation.Value)


        elif self.ajtypeIsString():
            cpptype = "const char*"
        else:
            cpptype = self.CppTypeMap.get(ajtype, "/* TODO:%{} */".format(ajtype))

        return cpptype

    def toMsgArg(self, expr):
        # Patch the expression to assign to the type from msgtype()
        if self.ajtypeIsString():
            return expr + ".c_str()"
        return expr

    def toStreamArg(self, expr):
        # Patch the expression to pass it to std::ostream
        # We need to be careful of byte sized integers.
        if self.ajtypeIsString():
            return expr + ".c_str()"
        if self.ajtype() in ["byte"]:
            return "(unsigned)(" + expr + ")"
        return expr

    def fromMsgArg(self, expr):
        # For going from msgType() to the carrier type
        if self.ajtypeIsEnum():
            return "static_cast<%s>(%s)" % (self.cpptype(), expr)
        return expr

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
        sig = self.signature
        array = False

        if sig.startswith('a'):
            array = True
            sig = sig[1:]

        sig = self.JavaTypePrimitiveMap.get(sig, None)

        if not sig:
            sig = self.JavaTypePrimitiveMap.get(self.ajtype_primitive(), None)

        if array and sig:
            return sig + "[]"

        return sig

    def javatype_any(self):
        javatype = self.javatype_primitive()
        if javatype is None:
            javatype = self.javatype()
        return javatype

    def javatype_class(self):
        return self.JavaTypeClassMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def objc_format_str(self):
        return self.ObjCFormatStrMap.get(self.signature, "/* TODO:%{} */".format(self.signature))

    def set_annotated_type(self, value):
        self.annotated_type = value

    def is_array(self):
        ajtype = self.annotated_type if self.annotated_type else self.signature
        return ajtype.startswith("a")

    def is_bool(self):
        ajtype = self.annotated_type if self.annotated_type else self.signature
        return ajtype == 'b'

    def is_string(self):
        ajtype = self.annotated_type if self.annotated_type else self.signature
        return ajtype == 's'

    def interface(self):
        return interface_of(self)

    def __str__(self):
        return self.signature


class InterfaceEnum(object):
    EnumEntry = namedtuple("EnumEntry", "Name Value")

    def __init__(self, name, parent = None):
        self.Name = Symbol(name)
        self.Values = []
        self.InvalidValues = []
        self.parent = parent

    def add_value(self, enumerator, value):
        enum_value_name = str(enumerator).replace("-", "_")
        enum_value_name = filter(lambda c: c in (string.ascii_letters + string.digits + "_"), enum_value_name)
        array = self.InvalidValues if (value == '255' and 'NotSupported' in enum_value_name) else self.Values
        array.append(InterfaceEnum.EnumEntry(Symbol(enum_value_name), value))

    def enum_type(self):
        name = '['+str(self.Name)+']'
        interface = interface_of(self)

        for prop in interface.Properties:
            for annotation in prop.Annotations:
                if annotation.Value == name:
                    return prop.Type

        for method in interface.Methods:
            for method_arg in method.Args:
                for annotation in method_arg.Annotations:
                    if annotation.Value == name:
                        return method_arg.Type

        # Internal code gen use to gain type signature of enums contained in structs.
        for annotation in interface.Annotations:
            if annotation.Name.find("org.twobulls.Struct") != -1:
                if annotation.Name.lower().find(self.Name.string.lower()) != -1:
                    if annotation.Name.find(".Sig") != -1:
                        return AJType(annotation.Value, self)

        return AJType('i', self)


class InterfaceStruct(object):
    StructField = namedtuple("StructField", "Type Name")

    def __init__(self, name, parent=None):
        self.Name = name
        self.Fields = []
        self.parent = parent
        self.Key = None

    def add_field(self, name, ajtype, interface):
        self.Fields.append(InterfaceStruct.StructField(AJType(ajtype, self), name))

    def set_key(self, struct_key):
        for f in self.Fields:
            if f.Name == struct_key:
                self.Key = f
                break

    def set_field_sig(self, field, field_sig):
        # Set a type signature override
        for f in self.Fields:
            if f.Name == field:
                f.Type.sigoverride = field_sig

    def resolve_signature(self):
        # Join the signatures of the fields and wrap them in ()
        interface = interface_of(self)
        sig = ""
        for f in self.Fields:
            sig += interface.resolve_signature(f[0].signature)
        return "(" + sig + ")"


class Interface(object):
    def __init__(self, name):
        self.Name = Symbol(name.split(".")[-1])
        self.Category = Symbol(name.split(".")[-2].lower())
        self.FullName = name
        self.ClassName = name.replace(".", "_")
        self.Secure = None
        self.Version = None
        self.Annotations = []
        self.Structs = []
        self.Enums = []
        self.Properties = []
        self.Methods = []
        self.Signals = []
        self.doc = {}
        self.PropertiesLUT = {}
        self.parent = None

    @property
    def UserProperties(self):
        return filter(lambda x: str(x.Name) != "Version", self.Properties)

    @property
    def PropLUT(self):
        return self.PropertiesLUT

    def UIProperties(self):
        return filter(lambda x: str(x.Name) != "Version" and not x.is_selector(), self.Properties)

    def set_secure(self, value):
        self.Secure = bool(value)

    def set_doc_string(self, language, value):
        self.doc[language.lower()] = value

    def add_struct_field(self, struct_name, field, field_type):
        struct = None
        for s in self.Structs:
            if s.Name == struct_name:
                struct = s
                break
        if struct is None:
            struct = InterfaceStruct(struct_name, self)
            self.Structs.append(struct)
        struct.add_field(field, field_type, self)

    def set_struct_key(self, struct_name, key_field):
        for s in self.Structs:
            if s.Name == struct_name:
                s.set_key(key_field)

    def set_field_sig(self, struct_name, field, field_sig):
        for s in self.Structs:
            if s.Name == struct_name:
                s.set_field_sig(field, field_sig)

    def add_enum_value(self, enum_name, enumerator, value):
        enum = None
        for e in self.Enums:
            if e.Name == enum_name:
                enum = e
                break
        if enum is None:
            enum = InterfaceEnum(enum_name, self)
            self.Enums.append(enum)

        enum.add_value(enumerator, value)

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.Secure'):
                lambda m: self.set_secure(value),

            re.compile(r'org\.alljoyn\.Bus\.DocString\.(\w*)'):
                lambda m: self.set_doc_string(m.group(1), value),

            re.compile(r'org\.alljoyn\.Bus\.Struct\.(\w*)\.Field\.(\w*).Type'):
                lambda m: self.add_struct_field(m.group(1), m.group(2), value),

            re.compile(r'org\.alljoyn\.Bus\.Enum\.(\w*)\.Value\.([\w/-]*)'):
                lambda m: self.add_enum_value(m.group(1), m.group(2), value),

            re.compile(r'org\.twobulls\.Struct\.(\w*)\.UniqueKey'):
                lambda m: self.set_struct_key(m.group(1), value),

            re.compile(r'org\.twobulls\.Struct\.(\w*)\.Field\.(\w*).Sig'):
                lambda m: self.set_field_sig(m.group(1), m.group(2), value),
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown interface annotation:", name

    def add_child(self, child):
        child.parent = self
        if isinstance(child, Property):
            self.Properties.append(child)
            self.PropertiesLUT[child.Name.string] = child
        elif isinstance(child, Method):
            self.Methods.append(child)
        elif isinstance(child, Signal):
            self.Signals.append(child)
        elif isinstance(child, Annotation):
            self.Annotations.append(child)
            self.add_annotation(child.Name, child.Value)
        elif isinstance(child, Description):
            pass
        else:
            print "Unexpected: ", child

    def resolve_signature(self, sig):
        # Resolve to a signature mapping our names to their signatures
        if sig.startswith('[') and sig.endswith(']'):
            name = sig[1:-1]
            for enum in self.Enums:
                if enum.Name == name and enum.enum_type():
                    return str(enum.enum_type())
            for struc in self.Structs:
                if struc.Name == name:
                    return struc.resolve_signature()
        return sig

    def has_writable_property(self):
        for property in self.UserProperties:
            if property.Writable and not property.Selector:
                return True
        return False

    def has_property_with_selector(self):
        for property in self.UserProperties:
            if property.Selector:
                return True
        return False

    def get_property_with_name(self, name):
        for property in self.UserProperties:
            if property.Name == name:
                return property
        return None


class Selector(object):
    def __init__(self, name, property):
        self.Name = Symbol(name)
        self.RelatedProperty = property

    @property
    def Property(self):
        interface = interface_of(self.RelatedProperty)
        return interface.get_property_with_name(self.Name)


class Property(object):
    def __init__(self, name, type, access):
        self.Name = Symbol(name)
        self.Type = AJType(type, self)
        self.Access = access
        self.doc = {}
        self.EmitsChangedSignal = False
        self.Const = False
        self.Writable = "write" in self.Access
        self.Readable = "read" in self.Access
        self.Annotations = []
        self.Min = None
        self.Max = None
        self.MaxFromProperty = None
        self.MinFromProperty = None
        self.StepFromProperty = None
        self.ValueIn = None
        self.Units = None
        self.parent = None
        self.Selector = None
        self.Clamp = False
        self.CustomCheck = False

    def tcl_access_char(self):
        return {
            'read': '>',
            'readwrite': '='
        }.get(self.Access, 'TODO')

    def emit_changed(self):
        return _padded_tag_replacement(self.EmitsChangedSignal)

    def property_access(self):
        return _padded_tag_replacement(self.Access)

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

    def set_min(self, value): 
        self.Min = value
 
    def set_max(self, value): 
        self.Max = value

    def set_max_from_property(self, value):
        self.MaxFromProperty = value

    def set_min_from_property(self, value):
        self.MinFromProperty = value

    def set_step_from_property(self, value):
        self.StepFromProperty = value

    def set_units(self, units): 
        self.Units = units

    def set_clamp(self, value):
        self.Clamp = True if value == "true" else False

    def set_value_in_from_property(self, value):
        self.ValueIn = value

    def set_custom_check(self, value):
        self.CustomCheck = True if value == "true" else False

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.DocString\.(\w*)'):
                lambda m: self.set_doc_string(m.group(1), value),

            re.compile(r'org\.freedesktop\.DBus\.Property\.EmitsChangedSignal'):
                lambda m: self.set_emits_changed_signal(value),

            re.compile(r'org\.alljoyn\.Bus\.Type\.Name'):
                lambda m: self.Type.set_annotated_type(value),

            re.compile(r'org\.alljoyn\.Bus\.Type\.Min'):
                lambda m: self.set_min(value),

            re.compile(r'org\.alljoyn\.Bus\.Type\.Max'):
                lambda m: self.set_max(value),

            re.compile(r'org\.alljoyn\.Bus\.Type\.Units'):
                lambda m: self.set_units(value),

            re.compile(r'org\.twobulls\.Property\.Selector'):
                lambda m: self.add_selector(value),

            re.compile(r'org\.twobulls\.Property\.Max'):
                lambda m: self.set_max_from_property(value),

            re.compile(r'org\.twobulls\.Property\.Min'):
                lambda m: self.set_min_from_property(value),

            re.compile(r'org\.twobulls\.Property\.Step'):
                lambda m: self.set_step_from_property(value),

            re.compile(r'org\.twobulls\.Property\.Clamp'):
                lambda m: self.set_clamp(value),

            re.compile(r'org\.twobulls\.Property\.ValueIn'):
                lambda m: self.set_value_in_from_property(value),

            re.compile(r'org\.twobulls\.Property\.CustomCheck'):
                lambda m: self.set_custom_check(value),
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown property annotation:", name

    def add_child(self, child):
        child.parent = self
        if isinstance(child, Annotation):
            self.Annotations.append(child)
            self.add_annotation(child.Name, child.Value)

    def add_selector(self, value):
        self.Selector = Selector(value, self)

    def is_bool(self):
        return self.Type.signature == 'b'

    def is_string(self):
        return self.Type.signature == 's'

    def is_enum(self):
        annotation_values = [annotation.Value for annotation in self.Annotations]
        interface = interface_of(self)
        for enum in interface.Enums:
            for value in annotation_values:
                if str(enum.Name) in value:
                    return True
        return False

    def is_selector(self):
        interface = interface_of(self)
        properties_with_selectors = [property.Selector for property in interface.UserProperties if property.Selector]
        for property in properties_with_selectors:
            if property.Name == self.Name:
                return True
        return False

    def enum_name(self):
        interface = interface_of(self)
        for enum in interface.Enums:
            for annotation in self.Annotations:
                if str(enum.Name) in annotation.Value and 'org.alljoyn.Bus.Type.Name' == annotation.Name:
                    name = annotation.Value
                    if name[0] == 'a' and name[1] == '[':
                        name = name.strip('a')
                    return name.strip('[]')
        return None

    def android_property_view_type(self):
        if self.Writable:
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
            return 'this, this.intf, "%s"' % self.Name
        elif self.is_enum():
            interface = interface_of(self)
            return 'this, this.intf, "%s", %s.%s.class' % (self.Name, interface.Name, self.enum_name())
        else:
            return 'this, this.intf, "%s", null' % self.Name


class Mutator(object):
    def __init__(self, name, interface, prop, prop_signature, default_value):
        self.Name = name
        self.Interface = interface
        self.Property = prop
        self.PropertyType = AJType(prop_signature, self)
        self.DefaultValue = default_value


class Method(object):
    def __init__(self, name):
        self.Name = Symbol(name)
        self.Args = []
        self.Annotations = []
        self.Mutators = []
        self.doc = {}
        self.parent = None
        self.noreply = False

    @property
    def CodeDoc(self):
        return self.doc.get("en", None)

    def add_arg(self, arg):
        self.Args.append(arg)

    def set_doc_string(self, language, value):
        self.doc[language.lower()] = value

    def set_dbus_anno(self, name, value):
        if name == "NoReply":
            self.noreply = value == "True"
        else:
            print "Unknown method DBus annotation:", name

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.DocString\.(\w*)'):
                lambda m: self.set_doc_string(m.group(1), value),
            re.compile(r'org\.freedesktop\.DBus\.Method\.(\w*)'):
                lambda m: self.set_dbus_anno(m.group(1), value),
            re.compile(r'org\.twobulls\.Method\.Mutates'):
                lambda m: self.add_mutator(value),
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown method annotation:", name

    def add_child(self, child): 
        child.parent = self
        if isinstance(child, MethodArg): 
            self.add_arg(child)
        elif isinstance(child, Annotation):
            self.Annotations.append(child)
            self.add_annotation(child.Name, child.Value)

    def add_mutator(self, value):
        interface, prop, prop_signature, default_value = value.split(":")
        self.Mutators.append(Mutator(self.Name, interface, prop, prop_signature, default_value))

    def input_args(self):
        return [arg for arg in self.Args if arg.Direction == 'in']

    def output_args(self):
        return [arg for arg in self.Args if arg.Direction == 'out']

    def output_arg(self):
        try:
            return [arg for arg in self.Args if arg.Direction == 'out'][0]
        except IndexError:
            return None

    def input_signature(self):
        return ''.join([str(arg.Type) for arg in self.Args if arg.Direction == 'in'])

    def output_signature(self):
        return ''.join([str(arg.Type) for arg in self.Args if arg.Direction == 'out'])


class MethodArg(object):
    def __init__(self, name, type, direction):
        self.Name = Symbol(name)
        self.Type = AJType(type, self)
        self.Direction = direction
        self.Annotations = []
        self.doc = {}
        self.parent = None

    def add_child(self, child):
        child.parent = self
        if isinstance(child, Annotation):
            self.Annotations.append(child)
            self.add_annotation(child.Name, child.Value)

    def set_doc_string(self, language, value):
        self.doc[language.lower()] = value

    def add_annotation(self, name, value):
        regexs = {
            re.compile(r'org\.alljoyn\.Bus\.Type\.Name'):
                lambda m: self.Type.set_annotated_type(value),

            re.compile(r'org\.alljoyn\.Bus\.DocString\.(\w*)'):
                lambda m: self.set_doc_string(m.group(1), value),
 
            re.compile(r'org\.alljoyn\.Bus\.Type\.Units'): 
                lambda m: False
        }

        handled = False
        for regex, handler in regexs.items():
            match = regex.match(name)
            if match:
                handler(match)
                handled = True

        if not handled:
            print "Unknown method arg annotation:", name


class Signal:
    def __init__(self, name, sessionless):
        self.Name = Symbol(name)
        self.Sessionless = sessionless.lower() == "true"
        self.parent = None

    def add_child(self, child):
        pass


class Annotation:
    def __init__(self, name, value):
        self.Name = name
        self.Value = value

    def __str__(self):
        return "{} = {}".format(self.Name, self.Value)


# Description is deprecated for DocString annotation
class Description:
    def __init__(self, language):
        self.language = language


class Root:
    def __init__(self, **kwargs):
        self.list = []

    def add_child(self, child):
        child.parent = None
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


class AboutDataString:
    def __init__(self, lang='en'):
        self.key = None
        self.value = None
        self.lang = lang

    def add_child(self, child):
        pass

    def __str__(self):
        return self.value


class AboutData:
    def __init__(self):
        self.DeviceTypeDescription = None

    def add_child(self, child):
        if isinstance(child, AboutDataString):
            self.__dict__[str(child.key)] = child
        elif isinstance(child, DeviceTypeDescription):
            self.DeviceTypeDescription = child


class DeviceTypeDescription:
    def __init__(self):
        self.data = None

    def add_child(self, child):
        if isinstance(child, TypeDescription):
            self.data = child


class TypeDescription:
    def __init__(self):
        self.device_type = None
        self.object_path = None

    def add_child(self, child):
        if isinstance(child, DeviceType):
            self.device_type = child
        elif isinstance(child, DeviceTypeObjectPath):
            self.object_path = child


class DeviceType:
    def __init__(self):
        self.value = None

    def __str__(self):
        return self.value


class DeviceTypeObjectPath:
    def __init__(self):
        self.value = None

    def __str__(self):
        return self.value


class InterfaceList:
    def __init__(self):
        self.Objects = []

    def add_child(self, child):
        if isinstance(child, ObjectPath):
            self.Objects.append(child)


class ObjectPath:
    def __init__(self, path):
        self.Path = path
        self.Interfaces = []

    def add_child(self, child):
        if isinstance(child, Interface):
            self.Interfaces.append(child)


class Device(Root):
    def __init__(self, name, **kwargs):
        Root.__init__(self, **kwargs)

        self.Name = Symbol(name)
        self.Objects = []
        self.AboutData = None

    def add_child(self, child):
        if isinstance(child, InterfaceList):
            self.Objects += child.Objects
        elif isinstance(child, AboutData):
            self.AboutData = child

    def all_interfaces(self):
        filtered_interfaces = []
        for o in self.Objects:
            for i in o.Interfaces:
                if i not in filtered_interfaces:
                    filtered_interfaces.append(i)

        return filtered_interfaces


class AJEmulatorXMLParser(AJXMLParser, object):
    Elements = {
        # Element Name  # (HandlerClass, [list, of, valid, parents])
        "DeviceEmulator":        (Device, [type(None)]),
        "AboutData":             (AboutData, [Device]),
        "AppId":                 (AboutDataString, [AboutData]),
        "DefaultLanguage":       (AboutDataString, [AboutData]),
        "DeviceName":            (AboutDataString, [AboutData]),
        "DeviceId":              (AboutDataString, [AboutData]),
        "AppName":               (AboutDataString, [AboutData]),
        "Manufacturer":          (AboutDataString, [AboutData]),
        "ModelNumber":           (AboutDataString, [AboutData]),
        "Description":           (AboutDataString, [AboutData]),
        "DateOfManufacture":     (AboutDataString, [AboutData]),
        "SoftwareVersion":       (AboutDataString, [AboutData]),
        "HardwareVersion":       (AboutDataString, [AboutData]),
        "SupportUrl":            (AboutDataString, [AboutData]),
        "UserDefinedTag":        (AboutDataString, [AboutData]),
        "CountryOfProduction":   (AboutDataString, [AboutData]),
        "Location":              (AboutDataString, [AboutData]),
        "CorporateBrand":        (AboutDataString, [AboutData]),
        "ProductBrand":          (AboutDataString, [AboutData]),
        "DeviceTypeDescription": (DeviceTypeDescription, [AboutData]),
        "TypeDescription":       (TypeDescription, [DeviceTypeDescription]),
        "device_type":           (DeviceType, [TypeDescription]),
        "object_path":           (DeviceTypeObjectPath, [TypeDescription]),
        "InterfaceList":         (InterfaceList, [Device]),
        "Object":                (ObjectPath, [InterfaceList]),
        "Interface":             (Interface, [ObjectPath]),
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


def interface_of(obj):
    if isinstance(obj, Interface):
        return obj
    if obj.parent:
        return interface_of(obj.parent)
    return None