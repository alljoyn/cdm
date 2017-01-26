import sys
import cmd
import argparse
import re
from collections import OrderedDict

from cdm_os import property_io

try:
    import readline
    if 'libedit' in readline.__doc__ or sys.platform == 'darwin':
        readline.parse_and_bind("bind ^I rl_complete")
    else:
        readline.parse_and_bind("tab: complete")
except ImportError:
    print " *** No tab completion available."


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
    ps = sorted(cwd.keys()) if type(cwd) is dict else sorted(cwd)
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
        if new_prop_data and shell.write_property_file(new_prop_data, file_name):
            print "{} for {} successfully written.".format(property_io.format_property_data(new_prop_data), file_name)
            shell.send_property_signal(file_name)

    def setarray():
        def set_array_scalar_entry(array_entry):
            if array_entry:
                return extract_scalar_from_value(array_entry, args.value[0])
            else:
                try:
                    data_type, new_value = [s for s in re.split(r'[()]+', args.value[0]) if s]
                    return data_type, new_value
                except ValueError:
                    print "Invalid value entry ({}) specified - must be in the format type(value) e.g., unsigned(10)".format(args.value[0])
                    return None

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

        def get_new_type():
            return OrderedDict() if type(args.value) is list else tuple()

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

            old_entry = get_new_type() if args.insert else prop_data[index]

            new_entry = {
                tuple: set_array_scalar_entry,
                OrderedDict: set_array_struct_entry,
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
    'cd': [('path', {'help': 'Path to navigate to'})],
    'ls': [('-a', {'action': 'store_true', 'help': "List paths for all interfaces."})],
    'inspect': [('file', {'help': 'The property file to display.'})],
    'set': [('mode', {
                 'choices': ['scalar', 'array'],
                 'help': 'The mode can be "scalar", "struct" or "array"'
             }),
            ('file', {'help': 'The property file to set a value. The file must exist'}),
            ('value', {'nargs': '*', 'help': 'The new scalar value. This option is only used in scalar mode'}),
            ('-index', {'help': 'The index of the array property to set'}),
            ('-remove', {'action': 'store_true', 'help': 'Remove an entry at the chosen index'}),
            ('-insert', {'action': 'store_true', 'help': 'Insert an entry at the chosen index'})],
    'reset': [('mode', {'choices': ['device'], 'help': 'Reset to factory settings'})]
}


def _get_cmd_pkg(cmd_name):
    return _shellcmds.get(cmd_name, None)


def _parse_cmd(cmd_name, input_text):
    def _parse_arguments(cmd_args_struct):
        arg_tokens = input_text.split()
        argument_parser = argparse.ArgumentParser(prog=cmd_name)

        for arg_name, arg_meta in cmd_args_struct:
            argument_parser.add_argument(arg_name, **arg_meta)

        try:
            return argument_parser.parse_args(arg_tokens)
        except SystemExit:
            return None

    if input_text is None:
        return None

    cmd_pkg = _get_cmd_pkg(cmd_name)
    if not cmd_pkg:
        print "Command {} not found.".format(cmd_name)
        return None

    return _parse_arguments(cmd_pkg)


class Shell(cmd.Cmd):
    prompt = "(Cmd)"

    def __init__(self, system, device_name):
        cmd.Cmd.__init__(self)
        self._cwd = []
        self._system = system
        self._device_name = device_name

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
            ps = sorted(cwd.keys()) if type(cwd) is dict else sorted(cwd)
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

    def _exec_cmd(self, cmd_name, args_text, cmd_func):
        if args_text is None:
            return

        try:
            parsed_args = _parse_cmd(cmd_name, args_text)
            if parsed_args is not None:
                cmd_func(self, parsed_args)
        except Exception as e:
            print "Unknown Error {}".format(e)

    def help_exit(self):
        print "Exits the shell.\n\nUsage: exit\n"

    def do_exit(self, _):
        return True

    def complete_cd(self, text, *_):
        cwd, prop_lut = self.resolve_cwd()
        ps = sorted(cwd.keys()) if type(cwd) is dict else sorted(cwd)
        return [p for p in ps if p.startswith(text)]

    def help_cd(self):
        print '\n'.join([
            '\nCommand cd (Change directory)',
            '\tUsage: cd <new path>\n',
            "\t * <new path> as '..' returns up one directory",
            "\t * <new path> as '~' returns to the root of the device\n",
            '\tExamples:',
            '\t\t'+'\n\t\t'.join(['cd ..', 'cd ~', 'cd /Org/BusPath/', 'cd org.SomeInterface', 'cd 0', 'cd 42']) + "\n"
        ])

    def do_cd(self, args_text):
        self._exec_cmd('cd', args_text, _cmd_cd)

    def help_ls(self):
        print '\n'.join([
            '\nCommand ls (List contents of current path)',
            '\nEach entry is presented with a unique id that can be used to identify the entry',
            'for other commands that accept a directory or file.',
            '\nUsage: ls <optional args>',
            '\nBasic Presentation: <ID>: <DIR/FILE NAME>',
            '\nArgument -a:',
            '\tDisplays a list of all available paths, including those not related to the running device.',
            '\tEntries are also displayed with more detail:',
            '\n\tPresentation: <ID>: <STATUS> <TYPE> - <DIR/FILE NAME>',
            '\t\tWhere <STATUS> is either * or [h]:',
            '\t\t\t * means the entry is used by the current device.',
            '\t\t\t[h] means the file is hidden and not used by current device.',
            '\t\tAnd <TYPE> is either [d] or [f] for directory or file respectively.',
            '\nExamples:',
            '\t' + '\n\t'.join(['ls', 'ls -a']) + "\n"
        ])

    def do_ls(self, args_text):
        self._exec_cmd('ls', args_text, _cmd_ls)

    def complete_set(self, text, line,  *_):
        if 'scalar' not in line and 'array' not in line:
            return [mode for mode in ['scalar', 'array'] if mode.startswith(text)]
        elif 'array' in line and '-index' not in line:
            return ['-index']
        else:
            cwd, _ = self.resolve_cwd()
            return [p for p in sorted(cwd) if p.startswith(text)] if type(cwd) is list else []

    def help_set(self):
        print '\n'.join([
            '\nCommand set (set property value)',
            '\nThis command is used to write to the devices property files with a new value.',
            'It is also responsible for alerting the device that the value has changed so the',
            'device can emit a change signal to announce the change.',
            '\nWARNING: The setting will do some type checking but it will not check if it is actually a valid',
            '          value for the actual property. It is possible to set values that are out of range as specified',
            '          by the interface xml. This can be useful for testing invalid state.',
            '\nUsage: set <args> <mode> <file> <new value(s)>',
            '  <file> must be a file number or id in the current directory.',
            '\nThere are two modes that set can work under - scalar and array.',
            'The mode has a direct impact on how the other parameters work.',
            '\nSetting a scalar value (ints, doubles, strings, booleans):',
            '\tUsage: set scalar <file> <scalar value>',
            '\t  * Note there are no args for setting a scalar',
            '\n\tExamples:',
            '\t\tset scalar MaxLevel 10',
            '\t\tset scalar IsOn true (true values can be 1, True, TRUE or true)',
            '\t\tset scalar 3 0.5 (where 3 is the files Id and 0.5 is the new value)',
            '\t\tset scalar GreetingProp Hello',
            '\t\tset scalar GreetingProp "Hello, World"',
            '\nModifying an array value (scalar and struct):',
            '\tUsage: set array -index <index> <file> <value(s)>',
            '\t  * Note - The index specified by -index must exist',
            '\t  * Note - It is possible to modify one or multiple struct fields',
            '\n\tExamples:',
            '\t\tset array -index 2 ArrayPropOfInts 10',
            '\t\tset array -index 0 ArrayPropOfStrings Hello',
            '\t\tset array -index 1 2 3 (1 is the array index, 2 is the file Id and 3 is the new value)',
            '\t\tset array -index 1 ArrayPropOfStruct field1=10 field2=true',
            '\nInserting a new array value (scalar and struct):',
            '\tUsage: set array -insert -index <index> <file> <type(value)>',
            '\t  * Note - The type must be specified for an insert',
            '\t  * Note - The index specified by -index will become the new entry',
            '\t  * Note - If the index is one after the last entry then it becomes and append',
            '\t  * Note - An index more than one after the last entry is invalid',
            '\t  * Note - Inserting a struct entry requires all fields to be specified',
            '\n\tExamples:',
            '\t\tset array -insert -index 2 ArrayPropOfInts unsigned(10)',
            '\t\tset array -insert -index 0 ArrayPropOfStrings string(Hello)',
            '\t\tset array -insert -index 1 ArrayPropOfStruct field1=int(-10) field2=bool(true) field3=double(3.14159)',
            '\t\tset array -insert -index 2 4 int(10) (2 is the array index and 4 is the file Id)',
            '\nRemoving an array value (scalar and struct):',
            '\tUsage: set array -remove -index <index> <file>',
            '\t  * Note the index specified by -index must exist',
            '\n\tExamples:',
            '\t\tset array -remove -index 2 SomeArrayProp\n',
        ])

    def do_set(self, args_text):
        self._exec_cmd('set', args_text, _cmd_set)

    def complete_inspect(self, text, *_):
        cwd, _ = self.resolve_cwd()
        return [p for p in sorted(cwd) if p.startswith(text)] if type(cwd) is list else []

    def help_inspect(self):
        print '\n'.join([
            '\nCommand inspect (Display the contents of a property file)',
            'Usage: inspect <file>\n',
            " * <file> is a property file name or Id in the current directory",
            '\nExamples:',
            '\t' + '\n\t'.join(
                ['inspect SomePropertyFile', 'inspect 4']) + "\n"
        ])

    def do_inspect(self, args_text):
        self._exec_cmd('inspect', args_text, _cmd_inspect)

    def complete_reset(self, *_):
        return ['device']

    def help_reset(self):
        print '\n'.join([
            '\nCommand reset (Resets the device to its factory setting)',
            '\tUsage: reset device\n'])

    def do_reset(self, args_text):
        self._exec_cmd('reset', args_text, _cmd_factory_reset)

    def preloop(self):
        Shell.prompt = "{}@{}: ".format(self._device_name, ';'.join(self._cwd))

    def postcmd(self, stop, line):
        Shell.prompt = "{}@{}: ".format(self._device_name, ';'.join(self._cwd))
        return cmd.Cmd.postcmd(self, stop, line)

    def _shell_repl(self):
        self.cmdloop()

    def start(self):
        self._shell_repl()


def build(system, device_name):
    return Shell(system, device_name)
