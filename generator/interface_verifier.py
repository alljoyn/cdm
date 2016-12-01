#!/usr/bin/env python2

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

import os
import glob

import xml_parser as xml


# These should probably be parameters
base_dir = "/Users/Nathaniel/projects/hae_interfaces"
interface_dir = "org.alljoyn.SmartSpaces.UserInterfaceSettings"

scan_path = os.path.join(base_dir, "interfaces", interface_dir)

saxhandler = xml.AJXMLParser()
parser = xml.make_parser()
parser.setContentHandler(saxhandler)

xml_files = glob.glob(os.path.join(scan_path, "*.xml"))
md_files = [os.path.splitext(fname)[0] + ".md" for fname in xml_files]

def verify_interface_pairs(pairs):
    for xml, md in pairs:
        if not os.path.exists(md): 
            raise Exception("Error: {0} is missing a corresponding mark down".format(xml))

    return pairs

def build_interface_pairs(xml_list, md_list):
    return verify_interface_pairs(zip(xml_list, md_list))

interface_pairs = build_interface_pairs(xml_files, md_files)


_expected_annotations = (
    'org.alljoyn.Bus.Secure',
    )

_types = {
        's': 'string',
        'b': 'bool',
        'y': 'byte',
        'n': 'int16',
        'q': 'uint16',
        'i': 'int32',
        'u': 'uint32',
        'x': 'int64',
        't': 'uint64',
        'd': 'double', 
        'as': 'string[]',
        'ab': 'bool[]',
        'ay': 'byte[]',
        'an': 'int16[]',
        'aq': 'uint16[]',
        'ai': 'int32[]',
        'au': 'uint32[]',
        'ax': 'int64[]',
        'at': 'uint64[]',
        'ad': 'double[]', 
}

_access_map = {
    'read': 'read',
    'readwrite': 'read-write',    
}

def verify_xml_with_mark_down(interface, md_filename):
    with open(md_filename) as markdown_fp:
        markdown = markdown_fp.read()

        def match_key_value(key, value, parent):
            required_md = '{0} = {1}'.format(key, value)
            return None if required_md in markdown else "Annotation missing/mismatched {0} = {1} on {2}".format(key, value, parent)

        def find_name(obj, name_of):
            attr = getattr(obj, name_of + "Name")
            name = "### {}".format(attr)
            return (None if name in markdown else "{} {} not found".format(name_of, attr)), name

        def extract_substr(substr_name, base_str, end_str="#"):
            substr_start = base_str[base_str.find(substr_name)+len(substr_name):]
            return substr_start[: substr_start.find(end_str)]

        def verify_property(prop):
            def verify_mapped_component(substr, component_name, component_map):
                component_attr = getattr(prop, 'Property' + component_name)
                component_value = component_map.get(str(component_attr), 'unknown')
                return None if component_value in substr else "Property {} {} != {} expected {}".format(prop.PropertyName, component_name, component_value, component_attr)

            name_error, prop_name = find_name(prop, "Property")
            prop_substr = extract_substr(prop_name, markdown)
            
            type_error = verify_mapped_component(prop_substr, 'Type', _types)
            access_error = verify_mapped_component(prop_substr, 'Access', _access_map)

            annotation_errors = [match_key_value(annotation.AnnotationName, annotation.AnnotationValue, prop.PropertyName) for annotation in prop.annotations if 'org.alljoyn.Bus.' not in annotation.AnnotationName]
            return [name_error, type_error, access_error] + annotation_errors

        def verify_method(method):
            name_error, method_name = find_name(method, "Method")
            method_substr = extract_substr(method_name, markdown)


            arg_template = '* **{}** --- {} ---'
            arg_strs = [arg_template.format(arg.ArgName, _types.get(str(arg.ArgType))) for arg in method.args]
            arg_errors = ["Method argument type mismatch/missing {}.{} - expected {}".format(method.MethodName, arg.ArgName, arg.ArgType) for arg_str in arg_strs if arg_str not in markdown]

            return [name_error] + arg_errors


        def verify_signal(signal):
            name_error, signal_name = find_name(signal, "Signal")
            return [name_error]

        def find_markdown_errors():
            def verify_components(component_list, verifier):
                return [error for component in component_list for error in verifier(component)]

            interface_name_found = "# {0}".format(interface.FullInterfaceName) in markdown
            errors = [] if interface_name_found else ["Interface name error: {0} not found in markdown".format(interface.FullInterfaceName)]
            
            # gather interface annotation errors
            errors += [match_key_value(annotation.AnnotationName, annotation.AnnotationValue, "Interface") for annotation in interface.annotations if annotation.AnnotationName in _expected_annotations]

            # gather property errors
            errors += verify_components(interface.properties, verify_property)

            # gather method errors
            errors += verify_components(interface.methods, verify_method)

            # gather method errors
            errors += verify_components(interface.signals, verify_signal)

            return filter(None, errors)

        markdown_errors = find_markdown_errors()

        def format_markdown_errors():
            errors = "\n\t".join(markdown_errors)
            return "\n\t{0}\n * ERROR(s) found in {1}".format(errors, md_filename)

        return "\nVerifying {0}...{1}".format(md_filename, "Done!" if not markdown_errors else format_markdown_errors())


for xml_file, md_file in interface_pairs:
    parser.parse(xml_file)
    report = verify_xml_with_mark_down(saxhandler.root.list[0], md_file)
    print report
