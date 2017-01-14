#!/usr/bin/env python

# Read the xml interface files and generate InterfaceFactory.cc
#
# Usage: gencreate *.xml > sample.cc

import argparse
import string
import sys
import re
from string import Template


def split_camel_case(word, separator):
    s = ""
    for c in word:
        if c in string.ascii_uppercase and s and s[-1] not in (string.ascii_uppercase + string.digits + "_"):
            s = s + separator + c
        else:
            s = s + c
    return s.lower()

def snake(word):
    return split_camel_case(word, "_").lower()

def upper_snake(word):
    return snake(word).upper()

#======================================================================

argument_parser = argparse.ArgumentParser()
argument_parser.add_argument('--binding', nargs='?', default="cc", choices=['c', 'cc', 'cpp'], help="The output language to generate")
argument_parser.add_argument('xml_files', nargs='*', help='Unix style pathname pattern expansion to xml interface files')
args = argument_parser.parse_args()

lang = args.binding
if lang == 'cpp':
    lang = 'cc'

#======================================================================

ifaces = []

for file in args.xml_files:
    if file.endswith(".xml"):
        f = open(file)
        lines = f.readlines()
        f.close()
        for line in lines:
            m = re.match("\s*<interface\s+name=\"([^\"]+)\"", line)
            if m != None:
                iface = m.group(1)
                m = re.match(".*\.(Operation|Environment|UserInterfaceSettings|Input)\.(\w+)", iface)
                if m != None:
                    cat = m.group(1).lower()
                    short = m.group(2)
                    ifaces.append((cat, short, iface))


includes = ""
creates  = ""

for (cat, short, full) in ifaces:
    if lang == 'cc':
        code = Template('#include "interfaces/controller/$cat/${short}IntfController.h"\n')
    else:
        line1 = '#include <ajtcl/cdm/interfaces/$cat/${short}Model.h>\n'
        line2 = '#include "Models/${cat}/${short}ModelImpl.h"\n'
        code = Template(line1 + line2)
    includes += code.substitute(cat = cat, short = short)


for (cat, short, full) in ifaces:
    if lang == 'cc':
        code = Template('    m_controllerCreators["${full}"] = static_cast<CreateIntfControllerFptr>(&${short}IntfController::CreateInterface);\n')
        creates += code.substitute(full = full, short = short)
    else:
        code = Template("""
    if (strcmp(ifaceName, ${usnake}) == 0) {
        return Cdm_AddInterface(objPath, ${usnake}, intfDesc${catshort}, &intfHandler${catshort}, Get${short}Model());
    }\n""")
        catshort = cat.capitalize() + short
        usnake   = upper_snake(short);
        creates += code.substitute(full = full, short = short, catshort = catshort, usnake = usnake)

# print includes
# print creates

# Replace the lines in the file
try:
    if lang == 'cc':
        fin = open("template_ControllerFactory.cc", "r")
        fout = open("ControllerFactory.cc", "w")
    else:
        fin = open("template_InterfaceFactory.c", "r")
        fout = open("InterfaceFactory.c", "w")

    lines = fin.readlines()
    fin.close()
    for line in lines:
        if line == "INCLUDE_MARKER\n":
            fout.write(includes)
        elif line == "CREATE_MARKER\n":
            fout.write(creates)
        else:
            fout.write(line)
    fout.close()
except OSError, exn:
    print exn

