# # 
#    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
#    Source Project Contributors and others.
#    
#    All rights reserved. This program and the accompanying materials are
#    made available under the terms of the Apache License, Version 2.0
#    which accompanies this distribution, and is available at
#    http://www.apache.org/licenses/LICENSE-2.0


import os

env = SConscript('../../core/alljoyn/build_core/SConscript')

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

if env.get('ALLJOYN_DISTDIR'):
    # normalize ALLJOYN_DISTDIR first
    env['ALLJOYN_DISTDIR'] = env.Dir('$ALLJOYN_DISTDIR')
    env.Append(CPPPATH = [ env.Dir('$ALLJOYN_DISTDIR/cpp/inc'),
                           env.Dir('$ALLJOYN_DISTDIR/about/inc')])
    env.Append(LIBPATH = [ env.Dir('$ALLJOYN_DISTDIR/cpp/lib'),
                           env.Dir('$ALLJOYN_DISTDIR/about/lib')])

env['bindings'] = set([ b.strip() for b in env['BINDINGS'].split(',') ])

env.SConscript('SConscript')