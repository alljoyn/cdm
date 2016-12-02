#!/usr/bin/env python

# Read the xml interface files and generate InterfaceFactory.cc
#
# Usage: gencreate *.xml > sample.cc

import sys
import re
from string import Template

ifaces = []

for file in sys.argv:
    if file.endswith(".xml"):
        f = open(file)
        lines = f.readlines()
        f.close()
        for line in lines:
            m = re.match("\s*<interface\s+name=\"([^\"]+)\"", line)
            if m != None:
                iface = m.group(1)
                m = re.match(".*\.(Operation|Environment)\.(\w+)", iface)
                if m != None:
                    cat = m.group(1).lower()
                    short = m.group(2)
                    ifaces.append((cat, short, iface))


includes = ""
creates  = ""

for (cat, short, full) in ifaces:
    code = Template('#include "interfaces/controller/$cat/${short}IntfController.h"\n')
    includes += code.substitute(cat = cat, short = short)

for (cat, short, full) in ifaces:
    code = Template('    m_controllerCreators["${full}"] = static_cast<CreateIntfControllerFptr>(&${short}IntfController::CreateInterface);\n')
    creates += code.substitute(full = full, short = short)

# print includes
# print creates

# Replace the lines in the file
try:
    fin = open("template_ControllerFactory.cc", "r")
    fout = open("ControllerFactory.cc", "w")
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

