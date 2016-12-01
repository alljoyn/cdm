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
import sys
import glob
try:
    import jinja2
except ImportError as e:
    print e
    print "Please run pip install jinja2"
    sys.exit(1)
import xml_parser as xml
import argparse


class Generator(object):
    def __init__(self, args):
        self.cmd_args = args

    def get_parser(self):
        pass

    def get_render_context_root(self, saxhandler):
        pass

    def get_output_path(self, path):
        return os.path.join(self.cmd_args.output_dir, path)

    def process_xml_file(self, saxhandler, xml_file):
        pass

    def generate(self):
        print 'Running %s' % type(self).__name__

        saxhandler = self.get_parser()
        parser = xml.make_parser()
        parser.setContentHandler(saxhandler)

        env = jinja2.Environment(loader=jinja2.FileSystemLoader(self.cmd_args.template_dir), undefined=jinja2.StrictUndefined, trim_blocks=True, lstrip_blocks=True, keep_trailing_newline=True)

        env.filters["pad"] = lambda s, width: str.ljust(str(s), width)

        for xml_file in glob.iglob(self.cmd_args.xml_files):
            print xml_file
            parser.parse(xml_file)

            self.process_xml_file(saxhandler, xml_file)

            render_root = self.get_render_context_root(saxhandler)

            for root, folders, files in os.walk(self.cmd_args.template_dir):
                for template_file in filter(lambda fname: not fname.startswith('.'), files):
                    template_path = os.path.join(root, template_file)
                    relative_path = os.path.relpath(template_path, self.cmd_args.template_dir)

                    print "  " + relative_path
                    template = env.get_template(relative_path)

                    render_result = template.render(render_root)
                    result_path = jinja2.Template(relative_path).render(render_root)

                    print "    -> " + result_path

                    result_path = self.get_output_path(result_path)

                    try:
                        os.makedirs(os.path.dirname(result_path))
                    except:
                        pass

                    open(result_path, "w").write(render_result)


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
        saxhandler.root.list[0].XML = "\n".join(['"'+line.rstrip("\n").replace('"', "'")+'"' for line in open(xml_file)])
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
    argument_parser.add_argument('output_dir', nargs='?', default="./output/", help='Path to directory where the generated files will be output to')
    argument_parser.add_argument('--sample', action='store_true', required=False, help='Generate sample programs using the device emulator xml file')
    args = argument_parser.parse_args()
    if args.sample:
        generator = SampleAppGenerator(args)
    else:
        generator = InterfaceCodeGenerator(args)
    generator.generate()

if __name__ == '__main__':
    main()