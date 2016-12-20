#    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
#    Source Project (AJOSP) Contributors and others.
#
#    SPDX-License-Identifier: Apache-2.0
#
#    All rights reserved. This program and the accompanying materials are
#    made available under the terms of the Apache License, Version 2.0
#    which accompanies this distribution, and is available at
#    http://www.apache.org/licenses/LICENSE-2.0
#
#    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
#    Alliance. All rights reserved.
#
#    Permission to use, copy, modify, and/or distribute this software for
#    any purpose with or without fee is hereby granted, provided that the
#    above copyright notice and this permission notice appear in all
#    copies.
#
#    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
#    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
#    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
#    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
#    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
#    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
#    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
#    PERFORMANCE OF THIS SOFTWARE.

import os

env = SConscript('./build_core/SConscript')

vars = Variables()
vars.Add('BINDINGS', 'Bindings to build (comma separated list): cpp, java', 'cpp,java')
vars.Add(EnumVariable('BUILD_CDM_SAMPLES',
                      'Build the CDM services samples.',
                      'on',
                      allowed_values = ['on', 'off']))
vars.Add(PathVariable('ALLJOYN_DISTDIR',
                      'Directory containing a built AllJoyn Core dist directory.',
                      os.environ.get('ALLJOYN_DISTDIR')))
vars.Add(EnumVariable('UINPUT',
                      'Activate uinput integration in samples.',
                      'off',
                      allowed_values = ['on', 'off']))

vars.Update(env)
Help(vars.GenerateHelpText(env))

if '' == env.subst('$ALLJOYN_DISTDIR'):
    print 'ALLJOYN_DISTDIR variable is required'
    if not GetOption('help'):
        Exit(1)
else:
    if env.get('ALLJOYN_DISTDIR'):
        # normalize ALLJOYN_DISTDIR first
        env['ALLJOYN_DISTDIR'] = env.Dir('$ALLJOYN_DISTDIR')
        env.Append(CPPPATH = [ env.Dir('$ALLJOYN_DISTDIR/cpp/inc'),
                               env.Dir('$ALLJOYN_DISTDIR/cpp/inc/alljoyn')])
        env.Append(LIBPATH = [ env.Dir('$ALLJOYN_DISTDIR/cpp/lib')])

    env['bindings'] = set([ b.strip() for b in env['BINDINGS'].split(',') ])

    env.SConscript('SConscript')