#!/usr/bin/env python

# Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
# Source Project (AJOSP) Contributors and others.
#
# SPDX-License-Identifier: Apache-2.0
#
# All rights reserved. This program and the accompanying materials are
# made available under the terms of the Apache License, Version 2.0
# which accompanies this distribution, and is available at
# http://www.apache.org/licenses/LICENSE-2.0
#
# Copyright 2016 Open Connectivity Foundation and Contributors to
# AllSeen Alliance. All rights reserved.
#
# Permission to use, copy, modify, and/or distribute this software for
# any purpose with or without fee is hereby granted, provided that the
# above copyright notice and this permission notice appear in all
# copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
# PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
# TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.


# Read the xml interface files and generate some code
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
                m = re.match(".*\.(Operation|Environment|UserInterfaceSettings|Input)\.(\w+)", iface)
                if m != None:
                    cat = m.group(1).lower()
                    short = m.group(2)
                    ifaces.append((cat, short, iface))



for (cat, short, full) in ifaces:
    code = Template("#include <interfaces/controllee/$cat/${short}IntfControllee.h>")
    print code.substitute(cat = cat, short = short)

print

for (cat, short, full) in ifaces:
    code = Template('#include "Models/$cat/${short}Model.h"')
    print code.substitute(cat = cat, short = short)

print
print

for (cat, short, full) in ifaces:
    code = Template("""if (name == "$full")
{
    status = mkInterface<${short}IntfControllee, ${short}Model>(obj.path);
}
else
""")
    print code.substitute(short = short, full = full),
