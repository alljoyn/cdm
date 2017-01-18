import argparse
import re

from cdm_os import property_io


def _cmd_exit(shell, _):
    shell.exit()


def _cmd_cd(shell, args):
    if args.path == '~':
        shell.return_home()
        return

    if args.path == '..':
        shell.cwd_pop()
        return

    resolved_name = shell.resolve_path_name(args.path)
    if resolved_name is None:
        print "Could not resolve {} to a valid path".format(args.path)
        return

    shell.cwd_append(resolved_name)
    return


def _cmd_ls(shell, args):
    cwd, prop_lut = shell.resolve_cwd()
    ps = sorted(cwd.keys()) if type(cwd) is dict else cwd
    if not ps:
        print "Empty"
        return

    for i, p in enumerate(ps):
        if args.a:
            file_exists = " * " if p in prop_lut else "[h]"
            file_status = "[d]" if type(cwd) is dict else "[f]"
            output = "{0: >3}: {1: >3}{2} - {3}".format(i, file_exists, file_status, p)
            print output
        else:
            if p in prop_lut:
                output = "{0: >3}: {1}".format(i, p)
                print output


def _cmd_inspect(shell, args):
    file_name = shell.resolve_path_name(args.file)
    prop_data = shell.read_property_file(file_name)
    formatted_prop_data = property_io.format_property_data(prop_data)
    print formatted_prop_data


def _cmd_set(shell, args):
    def parse_file_for_properties(expected_type, prop_type):
        file_name = shell.resolve_path_name(args.file)
        if file_name is None:
            print "Could not resolve {} to a file name".format(args.file)
            return None

        prop_data = shell.read_property_file(file_name)
        if type(prop_data) is not expected_type:
            print "{} is not a {} property".format(file_name, prop_type)
            return None

        return prop_data, file_name

    def extract_scalar_from_value(prop_data, arg_value):
        data_type, _ = prop_data

        try:
            data_value = property_io.marshal_data_type(data_type, arg_value)
        except ValueError:
            print "New scalar value of {} is not of type {}".format(arg_value, data_type)
            return

        return data_type, data_value

    def setscalar():
        parse_result = parse_file_for_properties(tuple, "scalar")
        if parse_result is None:
            return

        prop_data, file_name = parse_result

        new_prop_data = extract_scalar_from_value(prop_data, args.value[0])
        if shell.write_property_file(new_prop_data, file_name):
            print "{} for {} successfully written.".format(property_io.format_property_data(new_prop_data), file_name)
            shell.send_property_signal(file_name)

    def setarray():
        def set_array_scalar_entry(array_entry):
            return extract_scalar_from_value(array_entry, args.value[0])

        def set_array_struct_entry(array_entry):
            for v in args.value:
                try:
                    field_name, value = v.split('=')
                    try:
                        data_type, new_value = [s for s in re.split(r'[()]+', value) if s]
                        entry = (data_type, new_value)
                    except ValueError:
                        new_value = value
                        entry = array_entry[field_name]
                except ValueError:
                    print "Invalid value entry ({}) found - must be in the format field=value".format(v)
                    return None

                new_prop_data = extract_scalar_from_value(entry, new_value)
                if new_prop_data is None:
                    print "Unable to set field name {}".format(field_name)
                    return

                array_entry[field_name] = new_prop_data

            return array_entry

        parse_result = parse_file_for_properties(list, "array")
        if parse_result is None:
            return

        prop_data, file_name = parse_result
        if args.index is None:
            print "Index argument is missing"
            return

        try:
            index = int(args.index)
            if index < 0 or index > len(prop_data):
                print "Index argument is out of range. {} is out of range of [0, {}]".format(index, len(prop_data))
                return
        except ValueError:
            print "Index argument '{0}' invalid - must be integer".format(args.index)
            return

        if not args.remove:
            if not args.value:
                print "Missing value parameter"

            old_entry = {} if args.insert else prop_data[index]

            new_entry = {
                tuple: set_array_scalar_entry,
                dict: set_array_struct_entry,
            }.get(type(old_entry))(old_entry)

            if new_entry is None:
                return

            if args.insert:
                prop_data.insert(index, new_entry)
            else:
                prop_data[index] = new_entry
        else:
            prop_data.pop(index)

        if shell.write_property_file(prop_data, file_name):
            print "Modified array - \n{}\n - successfully written to {}".format(
                property_io.format_property_data(prop_data), file_name)
            shell.send_property_signal(file_name)

    if args.mode == 'scalar':
        setscalar()
    elif args.mode == 'array':
        setarray()


def _cmd_factory_reset(shell, _):
    shell.send_reset_signal()
    print "A full factory reset of device state has been issued"


_shellcmds = {
    'exit': {
        'cmd': _cmd_exit,
        'args': []
    },
    'cd': {
        'cmd': _cmd_cd,
        'args': [('path', {'help': 'Path to navigate to'})]
    },
    'ls': {
        'cmd': _cmd_ls,
        'args': [('-a', {'action': 'store_true', 'help': "List paths for all interfaces."})]
    },
    'inspect': {
        'cmd': _cmd_inspect,
        'args': [('file', {'help': 'The property file to display.'})]
    },
    'set': {
        'cmd': _cmd_set,
        'args': [
            ('mode',
             {
                 'choices': ['scalar', 'struct', 'array'],
                 'help': 'The mode can be "scalar", "struct" or "array"'
             }),
            ('file', {'help': 'The property file to set a value. The file must exist'}),
            ('value', {'nargs': '*', 'help': 'The new scalar value. This option is only used in scalar mode'}),
            ('-index', {'help': 'The index of the array property to set'}),
            ('-remove', {'action': 'store_true', 'help': 'Remove an entry at the chosen index'}),
            ('-insert', {'action': 'store_true', 'help': 'Insert an entry at the chosen index'})
        ]
    },
    'reset': {
        'cmd': _cmd_factory_reset,
        'args': [('mode', {'choices': ['device'], 'help': 'Reset to factory settings'})]
    }
}


def _get_cmd_pkg(cmd_name):
    return _shellcmds.get(cmd_name, None)


def _parse_cmd(cmd_text):
    def _parse_arguments(name, cmd, input_args):
        cmd_args_meta = cmd['args']
        argument_parser = argparse.ArgumentParser(prog=name)

        for arg_name, arg_meta in cmd_args_meta:
            argument_parser.add_argument(arg_name, **arg_meta)

        try:
            return argument_parser.parse_args(input_args)
        except SystemExit:
            return None

    tokens = cmd_text.split()
    if len(tokens) < 1:
        print "Unable to parse: {}".format(cmd_text)
        return None

    cmd_name = tokens.pop(0)
    cmd_pkg = _get_cmd_pkg(cmd_name)
    if not cmd_pkg:
        print "Command {} not found.".format(cmd_name)
        return None

    parsed_args = _parse_arguments(cmd_name, cmd_pkg, tokens)
    return cmd_pkg['cmd'], parsed_args


class Shell(object):
    def __init__(self, system, device_name):
        self._cwd = []
        self._active = False
        self._system = system
        self._device_name = device_name

    def exit(self):
        self._active = False

    def return_home(self):
        self._cwd = []

    def cwd_pop(self):
        if self._cwd:
            return self._cwd.pop()
        else:
            print "Already in root directory."
        return

    def cwd_append(self, dirname):
        cwd, _ = self.resolve_cwd()
        if type(cwd) is dict:
            self._cwd.append(dirname)
        else:
            print "{} is not a directory".format(dirname)

    def resolve_cwd(self):
        return self._system.retrieve_path(self._cwd)

    def resolve_path_name(self, path_or_id):
        cwd, prop_lut = self.resolve_cwd()
        try:
            path_id = int(path_or_id)
            ps = sorted(cwd.keys()) if type(cwd) is dict else cwd
            return ps[path_id] if path_id < len(ps) else None

        except ValueError:
            return path_or_id if path_or_id in cwd else None

    def read_property_file(self, prop_file_name):
        return self._system.read_property_file(self._cwd, prop_file_name)

    def write_property_file(self, prop_data, prop_file_name):
        return self._system.write_property_file(prop_data, self._cwd, prop_file_name)

    def send_property_signal(self, file_name):
        self._system.send_property_signal(self._cwd, file_name)

    def send_reset_signal(self):
        self._system.send_signal('reset', self._device_name)

    def _shell_repl(self):
        while self._active:
            usr_cmd = raw_input("{}@{}: ".format(self._device_name, ';'.join(self._cwd)))
            cmd_pair = _parse_cmd(usr_cmd)
            if cmd_pair and all(cmd_pair):
                try:
                    cmd_func, args = cmd_pair
                    cmd_func(self, args)
                except Exception as e:
                    print "Unknown Error {}".format(e)

    def start(self):
        print ""
        self._active = True
        self._shell_repl()


def build(system, device_name):
    return Shell(system, device_name)
