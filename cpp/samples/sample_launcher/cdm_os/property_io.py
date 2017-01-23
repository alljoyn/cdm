import itertools
from xml.dom import minidom


def _scalar_handler(elem):
    return elem.attributes['type'].nodeValue, elem.attributes['value'].nodeValue


def _array_handler(elem):
    return [_read_handlers[child_elem.nodeName](child_elem) for child_elem in elem.childNodes if child_elem.nodeName in _read_handlers]


def _struct_handler(elem):
    fields = [_field_handler(child_elem) for child_elem in elem.childNodes if child_elem.nodeName in _read_handlers]
    return dict(list(itertools.chain(*fields)))


def _field_handler(elem):
    return [(elem.attributes['name'].nodeValue, _read_handlers[child_elem.nodeName](child_elem)) for child_elem in elem.childNodes if child_elem.nodeName in _read_handlers]


_read_handlers = {
    'scalar': _scalar_handler,
    'array': _array_handler,
    'struct': _struct_handler,
    'field': _field_handler
}


def _format_property(property_data, accum):
    if type(property_data) is list:
        accum += "{}".format('\n'.join(["array[{}] = {}".format(i, _format_property(p, "")) for i, p in enumerate(property_data)]))

    elif type(property_data) is dict:
        fields = [_format_property(v, "{} = ".format(k)) for k, v in property_data.items()]
        accum += "struct {{{0}}}".format(", ".join(fields))
    elif type(property_data) is tuple:
        k, v = property_data
        accum += "{}({})".format(k, v)

    return accum


def _scalar_writer(xml, data_type, data_value):
    scalar_node = xml.createElement('scalar')
    scalar_node.attributes['type'] = str(data_type)
    scalar_node.attributes['value'] = str(data_value).strip('"')
    return scalar_node


def _array_writer(xml, properties):
    array_node = xml.createElement('array')
    for p in properties:
        child_node = _write_property(xml, p)
        array_node.appendChild(child_node)
    return array_node


def _struct_writer(xml, struct_prop):
    struct_node = xml.createElement('struct')
    for field_name, p in struct_prop.items():
        field_node = xml.createElement('field')
        field_node.attributes['name'] = field_name
        child_node = _write_property(xml, p)
        field_node.appendChild(child_node)
        struct_node.appendChild(field_node)
    return struct_node


def _write_property(xml, property_data):
    if type(property_data) is tuple:
        return _scalar_writer(xml, *property_data)
    elif type(property_data) is list:
        return _array_writer(xml, property_data)
    elif type(property_data) is dict:
        return _struct_writer(xml, property_data)


def _raise_value_error():
    raise ValueError()


_true_values = ['1', 'true', 'True', 'TRUE']
_false_values = ['0', 'false', 'False', 'FALSE']

_data_type_validators = {
    'unsigned': lambda x: int(x) if int(x) >= 0 else _raise_value_error(),
    'signed': lambda x: int(x),
    'string': lambda x: str(x),
    'bool': lambda x: 'true' if x in _true_values else 'false' if x in _false_values else _raise_value_error(),
    'double': lambda x: float(x)
}


def read_property_file(full_path):
    xml = minidom.parse(full_path)

    return _read_handlers[xml.childNodes[0].nodeName](xml.childNodes[0])


def format_property_data(property_data):
    return _format_property(property_data, "")


def write_property_file(property_data, full_path):
    xml = minidom.getDOMImplementation().createDocument(None, "root", None)
    top_elem = _write_property(xml, property_data)

    with open(full_path, "w") as fp:
        top_elem.writexml(fp, indent="", newl="\n")
        return True


def marshal_data_type(data_type, data_value):
    return _data_type_validators.get(str(data_type), lambda _: _raise_value_error())(str(data_value))