#!/usr/bin/python

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
#

# Another copy of this whitespace.py file exists in ajtcl to support Thin Client builds.
# That copy is located in 'ajtcl/tools'
# Changes to this file must be done here (build_core) and in ajtcl

import sys, os, fnmatch, re, filecmp, difflib, textwrap
import hashlib, pickle, time
from subprocess import Popen, STDOUT, PIPE

def main(argv=None):
    start_time = time.clock()
    dir_ignore = ["stlport", "build", ".git", ".repo", "alljoyn_objc", "ios", "external", ".sconf_temp" ]
    file_ignore_patterns = ['\.#.*', 'alljoyn_java\.h', 'Status\.h', 'Internal\.h',
                            'ManagedObj.h', #uncrustify has a problem with its private constructor
                            'org_alljoyn_jni_AllJoynAndroidExt\.h',
                            'org_alljoyn_bus_samples_chat_Chat\.h',
                            'org_allseen_sample_event_tester_BusHandler\.h',
                            'org_allseen_sample_action_tester_BusHandler\.h',
                            'org_alljoyn_bus_samples_simpleclient_Client\.h',
                            'org_alljoyn_bus_samples_simpleservice_Service\.h']
    file_patterns = ['*.c', '*.h', '*.cpp', '*.cc']
    valid_commands = ["check", "detail", "fix", "off"]
    uncrustify_config = None
    supported_uncrustify_versions = ["0.57", "0.61"]
    recommended_uncrustify_version =  "0.61"
    unc_suffix = ".uncrustify"
    wscfg = None
    xit=0
    sha_hash = hashlib.sha1()
    whitespace_db = {}
    whitespace_db_updated = False
    run_ws_check = True
    uncfile = None

    '''Verify uncrustify install and version'''
    version = get_uncrustify_version()
    if not version in supported_uncrustify_versions:
        print ("******************************************************************************")
        print ("*         NOTICE         **         NOTICE         **         NOTICE         *")
        print ("******************************************************************************")
        print ("You are using uncrustify v" + version + ".")
        print ("You must be using one of the following versions of uncrustify v" + (", v".join(supported_uncrustify_versions)) + "." )
        print ("Please use the recommended version of uncrustify v" + recommended_uncrustify_version + ".");
        print "(Or, run SCons with 'WS=off' to bypass the whitespace check)"
        print ("******************************************************************************")
        sys.exit(2)

    if version != recommended_uncrustify_version:
        print ("******************************************************************************")
        print ("*         NOTICE         **         NOTICE         **         NOTICE         *")
        print ("******************************************************************************")
        print ("You are using uncrustify v" + version + ".")
        print ("Using an older version of uncrustify may result in inaccurate white space scans.")
        print ("Please use the recommended version of uncrustify v" + recommended_uncrustify_version + ".");
        print ("******************************************************************************")

    # if an legacy version of uncrustify does not correctly work for a specific file
    # and we can not find another way around the issues we can selectively ignore
    # files only for the legacy version of uncrustify.
    if version == "0.57":
        # v0.57 does not process #if <value> and <value> correctly
        file_ignore_patterns.append("atomic.cc")
        # v0.57 does not process the case statements correctly for the json_value.cc file
        file_ignore_patterns.append("json_value\.cc")
        # v0.57 does not process the case statements correctly
        file_ignore_patterns.append("BusAttachment\.cc")
        file_ignore_patterns.append("FileStream\.cc")
        # v0.57 does not process the case statements and goto labels correctly
        file_ignore_patterns.append("alljoyn_java\.cc")
        file_ignore_patterns.append("ProxyBusObject\.cc")
        # v0.57 of has a problem with multi-line strings and lines that start with
        # the '<<' stream operator most of these issues only exist in unit-test code
        file_ignore_patterns.append("SessionListenerTest\.cc")
        file_ignore_patterns.append("ProxyBusObjectTest\.cc")
        file_ignore_patterns.append("InterfaceDescriptionTest\.cc")
        file_ignore_patterns.append("MarshalTest\.cc")
        file_ignore_patterns.append("SRPTest\.cc")
        file_ignore_patterns.append("SessionTest\.cc")
        file_ignore_patterns.append("IPAddressTest\.cc")
        file_ignore_patterns.append("ASN1Test\.cc")
        file_ignore_patterns.append("bigNumTest\.cc")
        file_ignore_patterns.append("SocketTest\.cc")
        file_ignore_patterns.append("UtilTest\.cc")
        # v0.57 CruptoECC.cc has a return statement with a buch of ifdefs that
        # confuse the whitespace checker.
        file_ignore_patterns.append("CryptoECC\.cc")
        # v0.57 the use of QCC_DEPRECATED confuses the parser.
        file_ignore_patterns.append("AboutClient\.h")
        file_ignore_patterns.append("AboutIconClient\.h")



    # try an load the whitespace.db file.  The file is dictionary of key:value pairs
    # where the key is the name of a file that has been checked by the WS checker
    # and the value is a sha1 blob calculated for the file.  specified for the key
    # if the key is not found (i.e. a new file or first time this script has been
    # run) then the key will be added.  If the  file fails the WS check it will be
    # removed from the dictionary.  If the file is new or the calculated hash has
    # changed the WS checker will check the file to see if it complies with the WS
    # rules.
    try:
        f = open('whitespace.db', 'r')
        try:
            whitespace_db = pickle.load(f)
        except pickle.UnpicklingError:
            os.remove('whitespace.db')
        finally:
            f.close()
    except IOError:
        print 'whitespace.db not found a new one will be created.'

    if argv is None:
        argv=[]
    if len(argv) > 0:
        wscmd = argv[0]
    else:
        wscmd = valid_commands[0]

    if len(argv) > 1:
        wscfg = os.path.normpath(argv[1])

    if wscmd not in valid_commands:
        print "\'" + wscmd + "\'" + " is not a valid command"
        print_help()
        sys.exit(2)

    '''If config specified in CL then use that, otherwise search for it'''
    if wscfg:
        uncrustify_config = wscfg
    else:
        uncrustify_config = find_config()

    '''Cannot find config file'''
    if not uncrustify_config:
        print "Unable to find a config file"
        print_help()
        sys.exit(2)

    '''Specified config file is invalid'''
    if not os.path.isfile(uncrustify_config):
        print uncrustify_config + " does not exist or is not a file"
        print_help()
        sys.exit(2)

    print "whitespace %s %s" % (wscmd,uncrustify_config)
    print "cwd=%s" % (os.getcwd())
    if wscmd == 'off':
        return 0

    '''Get a list of source files and apply uncrustify to them'''
    for srcfile in locate(file_patterns, file_ignore_patterns, dir_ignore):
        f = open(srcfile, 'rb')
        uncfile = None
        filesize = os.path.getsize(srcfile)
        sha_digest = None
        try:
            # Compute the sha tag for the file the same way as git computes sha
            # tags this prevents whitespace changes being ignored.
            sha_hash.update("blob %u\0" % filesize)
            sha_hash.update(f.read())
            sha_digest = sha_hash.hexdigest()
        finally:
            f.close()

        if sha_digest != None:
            try:
                if whitespace_db[srcfile] == sha_digest:
                    run_ws_check = False
                else:
                    whitespace_db[srcfile] = sha_digest
                    run_ws_check = True
                    whitespace_db_updated = True
            except KeyError:
                whitespace_db[srcfile] = sha_digest
                run_ws_check = True
                whitespace_db_updated = True

        if run_ws_check:
            uncfile = srcfile + unc_suffix

            '''Run uncrustify and generate uncrustify output file'''
            p = Popen( [ "uncrustify", "-c", uncrustify_config, srcfile, ],
                stdout=PIPE, stderr=STDOUT )
            output = p.communicate()[0]
            if p.returncode:
                print "error exit, uncrustify -c %s %s" % ( uncrustify_config, srcfile )
                print output
                print "whitespace check is not complete"
                del whitespace_db[srcfile]
                xit=2
                break

            '''check command'''
            if wscmd == valid_commands[0]:

                '''If the src file and the uncrustify file are different
                then print the filename'''
                if not filecmp.cmp(srcfile, uncfile, False):
                    print srcfile
                    del whitespace_db[srcfile]
                    xit=1

            '''detail command'''
            if wscmd == valid_commands[1]:

                '''If the src file and the uncrustify file are different
                then diff the files'''
                if not filecmp.cmp(srcfile, uncfile, False):
                    print ''
                    print '******** FILE: ' + srcfile
                    print ''
                    print '******** BEGIN DIFF ********'

                    fromlines = open(srcfile, 'U').readlines()
                    tolines = open(uncfile, 'U').readlines()
                    diff = difflib.unified_diff(fromlines, tolines, n=0)
                    sys.stdout.writelines(diff)

                    print ''
                    print '********* END DIFF *********'
                    print ''
                    del whitespace_db[srcfile]
                    xit=1

            '''fix command'''
            if wscmd == valid_commands[2]:

                '''If the src file and the uncrustify file are different
                then print the filename so that the user can see what will
                be fixed'''
                if not filecmp.cmp(srcfile, uncfile, False):
                    print srcfile
                    del whitespace_db[srcfile]

                '''run uncrustify again and overwrite the non-compliant file with
                the uncrustify output'''
                p = Popen( [ "uncrustify", "-c", uncrustify_config, "--no-backup", srcfile, ],
                    stdout=PIPE, stderr=STDOUT )
                output = p.communicate()[0]
                if p.returncode:
                    print "error exit, uncrustify -c %s --no-backup %s" % ( uncrustify_config, srcfile )
                    print output
                    print "whitespace check is not complete"
                    del whitespace_db[srcfile]
                    xit=2
                    break

            '''remove the uncrustify output file'''
            if os.path.exists(uncfile):
                try:
                    os.remove(uncfile)
                except OSError:
                    print "Unable to remove uncrustify output file: " + uncfile

    # end srcfile loop

    if uncfile and os.path.exists(uncfile):
        try:
            os.remove(uncfile)
        except OSError:
            print "Unable to remove uncrustify output file: " + uncfile

    # write the whitespace_db to a file so it is avalible next time the whitespace
    # checker is run.
    if whitespace_db_updated:
        try:
            f = open('whitespace.db', 'w')
            try:
                pickle.dump(whitespace_db, f)
            finally:
                f.close()
        except IOError:
            print 'Unable to create whitespace.db file.'
    print 'WS total run time: {0:.2f} seconds'.format(time.clock() - start_time)
    return xit

'''Return the uncrustify version number'''
def get_uncrustify_version( ):
    version = None

    try:
        '''run the uncrustify version command'''
        output = Popen(["uncrustify", "-v"], stdout=PIPE).communicate()[0]

    except OSError:
        '''OSError probably indicates that uncrustify is not installed,
         so bail after printing helpful message'''
        print ("It appears that \'uncrustify\' is not installed or is not " +
            "on your PATH. Please check your system and try again.")
        print "(Or, run SCons with 'WS=off' to bypass the whitespace check)"
        sys.exit(2)

    else:
        '''extract version from output string'''
        p = re.compile('^uncrustify (\d.\d{2})')
        m = re.search(p, output)
        version = m.group(1)

    return version

'''Command line argument help'''
def print_help( ):
        prog = 'whitespace.py'
        print textwrap.dedent('''\
        usage: %(prog)s [-h] [command] [uncrustify config]

        Apply uncrustify to C++ source files (.c, .h, .cc, .cpp),
        recursively, from the present working directory.  Skips
        'stlport', 'build', 'alljoyn_objc', 'ios', 'external', '.git', and '.repo' directories.

        Note:  present working directory is presumed to be within,
        or the parent of, one of the AllJoyn archives.

        Script will automatically locate the uncrustify config file
        in build_core, or alternatively, the user may specify one.

        Enables users to see which source files are not in compliance
        with the AllJoyn whitespace policy and fix them as follows:

            check     - prints list of non-compliant files (default)
            detail    - prints diff of non-compliant files
            fix       - modifies (fixes) non-compliant files

        Note that all files generated by uncrustify are removed.

        positional arguments:
          command            options: check(default) | detail | fix
          uncrustify config  specify an alternative uncrustify config (default=none)

        optional arguments:
          -h, --help         show this help message and exit

        Examples:

        Get a list of non-compliant files using the alljoyn uncrustify config:
            >python %(prog)s  --OR--
            >python %(prog)s check

        Get a list of non-compliant files using your own uncrustify config:
            >python %(prog)s check r'myconfig.cfg' (note: use raw string)

        Get a diff of non-compliant files using the alljoyn uncrustify config:
            >python %(prog)s detail

        Fix non-compliant files using the alljoyn uncrustify config:
            >python %(prog)s fix''' % { 'prog': prog } )

'''Search for the uncrustify config file'''
def find_config( ):
    tgtdir = "build_core"
    cfgname = "ajuncrustify.cfg"
    ajcfgrelpath = os.path.join(tgtdir, "tools", "conf", cfgname)
    ajcfgpath = None
    foundit = 0
    DIRDEPTHMAX = 6

    '''Limit directory search to depth DIRDEPTHMAX'''
    curdir = os.path.abspath(os.curdir)
    for i in range(DIRDEPTHMAX):
        if tgtdir in os.listdir(curdir):
            foundit = 1
            break
        else:
            curdir = os.path.abspath(os.path.join(curdir, ".."))

    if foundit == 1 and os.path.exists(os.path.join(curdir, ajcfgrelpath)):
        ajcfgpath = os.path.join(curdir, ajcfgrelpath)
    return ajcfgpath

'''Recurse through directories and locate files that match a given pattern'''
def locate(file_patterns, file_ignore_patterns, dir_ignore_patterns, root=os.curdir):
    for path, dirs, files in os.walk(os.path.abspath(root)):
        '''Remove unwanted dirs'''
        for dip in dir_ignore_patterns:
            for dyr in dirs:
                if dyr == dip:
                    dirs.remove(dyr)
        '''Remove unwanted files'''
        files_dict = {}
        for filename in files:
            files_dict[filename] = True
        for filename in files:
            for fip in file_ignore_patterns:
                if re.search(fip, filename) != None:
                    del files_dict[filename]
        '''Collect the filtered list'''
        filtered_files = []
        for filename in files_dict.keys():
            filtered_files.append(filename)
        '''Filter the remainder using our wanted file pattern list'''
        for pattern in file_patterns:
            for filename in fnmatch.filter(filtered_files, pattern):
                yield os.path.join(path, filename)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        sys.exit(main(sys.argv[1:]))
    else:
        sys.exit(main())

#end