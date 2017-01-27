#!/usr/bin/env python
# 
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


import os
import sys
import glob
try:
    import jinja2
except ImportError as e:
    print e
    print "Please run pip install jinja2"
    sys.exit(1)
except BaseException:
    sys.exit(1)

import xml_parser as xml
import argparse

# Ugly global for the current template relative path
CurrentRelativePath = ""

# Load local macro files from the current directory.
class LocalLoader(jinja2.BaseLoader):

    def __init__(self):
        self.files = ["macros", "tcl_macros"]

    def get_source(self, environment, template):
        # "patch/foo" maps to somewhere in the patches tree according to the template relative path
        if template in self.files:
            path = template
            if not os.path.exists(path):
                raise jinja2.TemplateNotFound(template)
            mtime = os.path.getmtime(path)
            with file(path) as f:
                source = f.read().decode('utf-8')
            return source, path, lambda: mtime == os.path.getmtime(path)
        raise jinja2.TemplateNotFound(template)


class PatchLoader(jinja2.BaseLoader):

    def __init__(self, patchespath):
        self.patchespath = patchespath

    def get_source(self, environment, template):
        # "patch/foo" maps to somewhere in the patches tree according to the template relative path
        if template.startswith("patch/") and self.patchespath:
            base = template[6:]
            path = os.path.join(self.patchespath, CurrentRelativePath, base)
            #print "looking for patch:", path
            if not os.path.exists(path):
                #print "patch not found:", path
                raise jinja2.TemplateNotFound(template)
            mtime = os.path.getmtime(path)
            with file(path) as f:
                source = f.read().decode('utf-8')
            return source, path, lambda: mtime == os.path.getmtime(path)
        raise jinja2.TemplateNotFound(template)


class Generator(object):
    def __init__(self, args):
        self.cmd_args = args

        self._binding_checks_metadata = (
                (('all', 'cpp'),  ('cpp',  ['.cc', '.cpp', '.h'])),
                (('all', 'java'), ('java', ['.java'])),
                (('all', 'tcl'), ('tcl', ['.c', '.h'])),
                (('all', 'ios'), ('ios', ['.mm', '.h']))
            )

        self._component_checks_metadata = (
                (('all', 'controller'), ('/', ['controller', 'smartspaces'])),
                (('all', 'controllee'), ('/', ['controllee'])),
                (('all', 'common'),     ('/', ['common'])),
                (('all', 'samples'),    ('/', ['samples'])),
                (('all', 'tcl'),        ('/', ['cdm_tcl']))
            )

    def get_parser(self):
        pass

    def get_render_context_root(self, saxhandler):
        pass

    def get_output_path(self, path):
        return os.path.join(self.cmd_args.output_dir, path)

    def process_xml_file(self, saxhandler, xml_file):
        pass

    def generate(self):
        global CurrentRelativePath

        def file_checker(fname):
            not_hidden = not (os.path.basename(fname).startswith('.') or fname.endswith('~'))

            def do_check(valid_matches, chosen):
                return any([match in chosen for match in valid_matches])

            def file_is_check(searches):
                required, sub_checks = searches
                return any([(required in fname and sub_check in fname) for sub_check in sub_checks])

            def build_check_pair(elem, search, chosen):
                return do_check(elem, chosen), file_is_check(search)

            def build_checks(category, metadata):
                return [(build_check_pair(elems, search_tokens, category)) for elems, search_tokens in metadata]

            def validate_checks(checks_list):
                return any([(do_this and file_is_this) for do_this, file_is_this in checks_list])

            binding_checks = build_checks(self.cmd_args.bindings, self._binding_checks_metadata)
            component_checks = build_checks(self.cmd_args.components, self._component_checks_metadata)
            is_valid = not_hidden and validate_checks(binding_checks) and validate_checks(component_checks)
            return is_valid

        # print 'Running %s' % type(self).__name__

        saxhandler = self.get_parser()
        parser = xml.make_parser()
        parser.setContentHandler(saxhandler)

        myLoader = jinja2.ChoiceLoader([
            LocalLoader(),
            PatchLoader(self.cmd_args.patches),
            jinja2.FileSystemLoader(self.cmd_args.template_dir)
            ])

        env = jinja2.Environment(loader=myLoader, undefined=jinja2.StrictUndefined, trim_blocks=True, lstrip_blocks=True, keep_trailing_newline=True)

        env.filters["pad"] = lambda s, width: str.ljust(str(s), width)

        for xml_file in glob.iglob(self.cmd_args.xml_files):
            print "XML:", xml_file
            parser.parse(xml_file)

            self.process_xml_file(saxhandler, xml_file)

            render_root = self.get_render_context_root(saxhandler)

            for root, _, files in os.walk(self.cmd_args.template_dir):
                template_paths = [os.path.join(root, fname) for fname in files]
                for template_path in filter(file_checker, template_paths):

                    relative_path = os.path.relpath(template_path, self.cmd_args.template_dir)
                    result_path = jinja2.Template(relative_path).render(render_root)

                    # See if we can load a whole file from the patches directory
                    # The path components don't contain variables and the patches
                    # aren't rendered
                    whole_path = os.path.join(self.cmd_args.patches, relative_path)
                    whole_path = jinja2.Template(whole_path).render(render_root)
                    #print "whole_path", whole_path

                    if os.path.exists(whole_path):
                        try:
                            f = open(whole_path)
                            render_result = f.read()
                            f.close()
                            print "  using whole file", whole_path
                        except OSError:
                            print "ERROR reading path:", whole_path
                            render_result = ("ERROR unreadable %s\n" % whole_path)
                    else:
                        print "  " + relative_path
                        template = env.get_template(relative_path)

                        CurrentRelativePath = os.path.dirname(result_path)
                        render_result = template.render(render_root)

                    result_path = self.get_output_path(result_path)
                    result_dir  = os.path.dirname(result_path)
                    print "    -> " + result_path

                    if not self.cmd_args.dryrun:
                        try:
                            if not os.path.exists(result_dir):
                                os.makedirs(result_dir)
                        except OSError:
                            print "ERROR creating path:", result_dir

                        try:
                            open(result_path, "w").write(render_result)
                        except OSError:
                            print "ERROR writing file:", result_path


class InterfaceCodeGenerator(Generator):
    def get_parser(self):
        return xml.AJXMLParser()

    def get_render_context_root(self, saxhandler):
        interface = saxhandler.root.list[0]
        return {
            "Interface": interface,
            "InterfaceName": interface.Name,
            "InterfaceCategory": interface.Category,
            "Version": interface.Version,
        }

    def process_xml_file(self, saxhandler, xml_file):
        saxhandler.root.list[0].XML = "\n".join(['"'+line.rstrip("\n").replace('"', "'")+'"' for line in open(xml_file) if "org.twobulls." not in line])
        xml_version = xml_file.split("-v")[-1][:-4]
        saxhandler.root.list[0].Version = xml_version


class SampleAppGenerator(Generator):
    def get_parser(self):
        return xml.AJEmulatorXMLParser()

    def get_render_context_root(self, saxhandler):
        device = saxhandler.root
        return {
            "Device": device,
            "DeviceName": device.Name,
        }


def main():
    argument_parser = argparse.ArgumentParser()
    argument_parser.add_argument('template_dir', help='Path to directory with the templates to be used for code generation')
    argument_parser.add_argument('xml_files', help='Unix style pathname pattern expansion to xml files to be used for pystache rendering context')
    argument_parser.add_argument('--output_dir', nargs='?', default="output/", help='Path to directory where the generated files will be output to')
    argument_parser.add_argument('--bindings', nargs='*', default=["all"], help="The bindings to generate")
    argument_parser.add_argument('--components', nargs='*', default=["all"], help="The components to generate (controller, controllee or all")
    argument_parser.add_argument('--sample', action='store_true', required=False, help='Generate sample programs using the device emulator xml file')
    argument_parser.add_argument('--patches', required=False, default="", help='Path to the root for patch templates')
    argument_parser.add_argument('--dryrun', action='store_true', required=False, default=False, help="Executes but doesn't write any files")
    args = argument_parser.parse_args()

    generator = SampleAppGenerator(args) if args.sample else InterfaceCodeGenerator(args)

    try:
        generator.generate()
    except KeyboardInterrupt:
        print "main, KeyboardInterrupt"
        sys.exit(1)

if __name__ == '__main__':
    main()
