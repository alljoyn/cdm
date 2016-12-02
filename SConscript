# Copyright AllSeen Alliance. All rights reserved.
#
#    Permission to use, copy, modify, and/or distribute this software for any
#    purpose with or without fee is hereby granted, provided that the above
#    copyright notice and this permission notice appear in all copies.
#
#    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import os
import platform

WINDOWS = "Windows"

Import('env')

env['_ALLJOYN_CDM_'] = True
env['OBJDIR_SERVICES_CDM'] = env['OBJDIR'] + '/services/cdm'

if env['OS'] == 'darwin' and env['CPU'] == 'x86':
    env.Append(CPPPATH = [os.popen('brew --prefix openssl').read().strip() + '/include'])

if 'c' not in env['bindings']:
    list = env['LIBPATH']
    if '$DISTDIR/c/lib' in list:
        list.remove('$DISTDIR/c/lib')
        env['LIBPATH'] = list

if not env.has_key('_ALLJOYN_ABOUT_') and os.path.exists('../../core/alljoyn/services/about/SConscript'):
    env.SConscript('../../core/alljoyn/services/about/SConscript')

if 'cpp' in env['bindings'] and not env.has_key('_ALLJOYNCORE_') and os.path.exists('../../core/alljoyn/alljoyn_core/SConscript'):
    env.SConscript('../../core/alljoyn/alljoyn_core/SConscript')

if 'java' in env['bindings'] and not env.has_key('_ALLJOYN_JAVA_') and os.path.exists('../../core/alljoyn/alljoyn_java/SConscript'):
   env.SConscript('../../core/alljoyn/alljoyn_java/SConscript')

if platform.system() != WINDOWS:
    env.Append(CPPFLAGS=['-Wno-unused-variable', '-Wno-unused-parameter'])
else:
    env.Append(CPPFLAGS=['/wd4100', '/wd4189'])
    # Disable due to bug in VS 2015 update 1 http://stackoverflow.com/questions/34013930/error-c4592-symbol-will-be-dynamically-initialized-vs2015-1-static-const-std
    env.Append(CPPFLAGS=['/wd4592'])

cdm_env = env.Clone()
cdm_env.Append(LIBPATH = '$DISTDIR/cdm/lib')
cdm_env.Append(CPPPATH = '$DISTDIR/cdm/framework/inc')
cdm_env.Append(CPPPATH = '$DISTDIR/cdm/interfaces/inc')

#do not allow variable length arrays on the heap
if platform.system() != WINDOWS:
    cdm_env.Append(CPPFLAGS = '-Werror=vla');

# Allow dynamic casts and exceptions in CDM
cdm_env.Append(CXXFLAGS = ['-frtti', '-fexceptions'])

for b in cdm_env['bindings']:
    if os.path.exists('%s/SConscript' % b):
# if SDKROOT set will build from core build instead of include library if no library copied into include
        cdm_env.Append(LIBPATH = '#../../core/alljoyn/build/$OS/$CPU/$VARIANT/dist/%s/lib' % b)
        cdm_env.VariantDir('$OBJDIR_SERVICES_CDM/%s' % b, b, duplicate = 0)
        cdm_env.SConscript(['$OBJDIR_SERVICES_CDM/%s/SConscript' % b for b in env['bindings'] ], exports = ['cdm_env'])
