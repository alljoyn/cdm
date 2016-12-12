#!/usr/bin/env python

# Read the xml interface files and generate InterfaceFactory.c for the
# device emulator.
#
# Usage: genTclFactory *.xml > InterfaceFactory.c

import sys
import re
from string import Template

class Iface:
    def __init__(self, short, full, cat):
        self.full = full
        self.short = short
        self.cat = cat
        self.enums = []
        self.structs = {}       # map from struct name to Struct
        #print "new iface", short, full, cat


    def studyAnno(self, anno):
        # Look for 
        #    <annotation name="org.alljoyn.Bus.Enum.Severity.Value.warning" value="0"/>
        #    <annotation name="org.alljoyn.Bus.Enum.Severity.Value.warning" value="0"/>
        #    <annotation name="org.alljoyn.Bus.Struct.AlertRecord.Field.severity.Type" value="[Severity]"/>
        #    <annotation name="org.alljoyn.Bus.Struct.AlertRecord.Field.alertCode.Type" value="q"/>
        #print "studyAnno", anno
        m = re.match('\s*<annotation .*\.Enum\.(\w+)\..*', anno)
        if m != None:
            enum = m.group(1)
            if not enum in self.enums:
                self.enums.append(enum)
        else:
            m = re.match('\s*<annotation .*\.Struct\.(\w+)\.Field\.(\w+)\.Type.*value="([^"]+)"', anno)
            if m != None:
                name  = m.group(1)
                field = m.group(2)
                sig   = m.group(3)
                #print "found", name, field, sig

                if name in self.structs:
                    self.structs[name].addField(field, sig)
                else:
                    s = Struct(self, name)
                    s.addField(field, sig)
                    self.structs[name] = s


    def isEnum(self, name):
        # Recognise [Name] and Name
        if name.startswith("[") and name.endswith("]"):
            name = name[1:-1]
        return name in self.enums


    def dump(self):
        print "Interface", self.full
        for e in self.enums:
            print "    enum ", e
        for v in self.structs.values():
            v.dump()



class Struct:
    def __init__(self, iface, name):
        self.iface  = iface
        self.name   = name
        self.fields = []
        #print "new struct", name


    def addField(self, field, sig):
        self.fields.append((field, sig))
        #print "new field", field, sig


    def ajSig(self):
        # Return the actual signature that AJ uses
        # This is for registration of encoders.
        sig = ""
        for (name, s) in self.fields:
            sig += s
        return sig


    def dump(self):
        print "    struct", self.name, self.fields
        print "    struct sig", self.ajSig()



def Main():
    # Map from the full name to an Iface object.
    ifaces = {}
    current = None

    for file in sys.argv:
        if file.endswith(".xml"):
            f = open(file)
            lines = f.readlines()
            f.close()
            for line in lines:
                m = re.match("\s*<interface\s+name=\"([^\"]+)\"", line)
                if m != None:
                    full = m.group(1)
                    m = re.match(".*\.(Operation|Environment)\.(\w+)", full)
                    if m != None:
                        cat = m.group(1).lower()
                        short = m.group(2)
                        current = Iface(short, full, cat)
                        ifaces[full] = current
                else:
                    m = re.match('\s*<annotation .*', line)
                    if m != None:
                        current.studyAnno(line)

            if False and current != None:
                current.dump()


    includes = ""
    registers  = ""


    for iface in ifaces.values():
        code = Template('#include <ajtcl/cdm/interfaces/${cat}/${short}Model.h>\n')
        includes += code.substitute(cat = iface.cat, short = iface.short)

    for iface in ifaces.values():
        for struct in iface.structs.values():
            code = Template('    HAL_RegisterEncoder("${sig}", Encoder_${struct});\n')
            registers += code.substitute(sig = struct.ajSig(), struct = struct.name)

    # print includes
    # print creates

    # Replace the lines in the file
    try:
        fin = open("template_InterfaceFactory.c", "r")
        fout = open("InterfaceFactory.c", "w")
        lines = fin.readlines()
        fin.close()
        for line in lines:
            if line == "INCLUDE_MARKER\n":
                fout.write(includes)
            elif line == "REGISTER_MARKER\n":
                fout.write(registers)
            else:
                fout.write(line)
        fout.close()
    except OSError, exn:
        print exn



Main()

