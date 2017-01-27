#!/usr/bin/env python

import os
import sys
import json
import argparse
import itertools
import time

import cdm_os

try:
    import readline
    if 'libedit' in readline.__doc__ or sys.platform == 'darwin':
        readline.parse_and_bind("bind ^I rl_complete")
    else:
        readline.parse_and_bind("tab: complete")

except ImportError:
    print " *** No tab completion available."
    readline = None


def _get_selection(list_options_func, choice_input_text, options):
    def completer(text, state):
        for cmd in options:
            if cmd.startswith(text):
                if not state:
                    return cmd
                else:
                    state -= 1
    while True:
        try:
            list_options_func()
            print ""

            if readline:
                old_completer = readline.get_completer()
                readline.set_completer(completer)
                choice = raw_input(choice_input_text)
                readline.set_completer(old_completer)
            else:
                choice = raw_input(choice_input_text)

            if choice == 'exit':
                print "Aborting boot sequence..."
                sys.exit(0)

            if choice not in options:
                raise ValueError

            return choice
        except ValueError:
            print "Invalid index chosen. Valid choices are: {}\n".format(
                ', '.join([]))


def _raise_value_error(msg):
    raise ValueError(msg)


class _SysConf(object):
    def __init__(self, sys_conf):
        self.bin_dir = sys_conf['bin_dir'] if os.path.exists(sys_conf['bin_dir']) else _raise_value_error("bin dir does not exist")
        self.mount_dir = sys_conf['mount_dir']
        self.device_xml_dir = sys_conf['device_xml_dir'] if os.path.exists(sys_conf['device_xml_dir']) else _raise_value_error("device xml dir does not exist")


def _extract_device_xml(boot_args, device_conf, sys_conf):
    def output_device_xmls(xmls):
        for xml in xmls:
            print "    * {}".format(xml)

    if device_conf['devicexml'] == 'from args' and not boot_args.devicexml:
        device_xmls = os.listdir(sys_conf.device_xml_dir)
        print "\nThis device requires a device xml to be specified."
        device_xml = _get_selection(
            lambda: output_device_xmls(device_xmls),
            "Input device xml name (input exit to abort): ",
            device_xmls)

        full_path = os.path.join(sys_conf.device_xml_dir, device_xml)
        if not os.path.exists(full_path):
            raise ValueError("Device configuration wants a device xml passed in as an argument but device xml not found")

        boot_args.devicexml = full_path

    xml = boot_args.devicexml if boot_args.devicexml else device_conf['devicexml']
    is_full_path = xml.startswith(sys_conf.device_xml_dir)
    device_xml_path = xml if is_full_path else os.path.join(sys_conf.device_xml_dir, xml)

    return device_xml_path


class _DeviceConf(object):
    def __init__(self, boot_args, device_conf, sys_conf):
        self.device_xml = _extract_device_xml(boot_args, device_conf, sys_conf)
        self.device = device_conf['bin']
        self.state_dir = device_conf['state_dir']
        self.certs_dir = device_conf['certs_dir']
        self.boot_program = device_conf['boot_program']
        self.args = self._process_args(device_conf['args'])

    def _process_args(self, args_list):
        _macros = {
            '%%devicexml': self.device_xml,
            '%%certs-dir': self.certs_dir,
            '%%state-dir': self.state_dir
        }

        processed_args = [_macros.get(arg, arg) for arg in args_list]

        # scan for empty args and these need to be removed. Also, if the arg is empty then remove the arg before it as
        # it will be a flag arg like --cert-dir or --state-dir
        indices_to_remove = [[i-1, i] if i != 0 and not arg else i for i, arg in enumerate(processed_args) if not arg]
        flattened_list = list(itertools.chain.from_iterable(indices_to_remove))
        final_args = [arg for i, arg in enumerate(processed_args) if i not in flattened_list]

        return final_args


_conf_dir = os.path.join('.', 'cdm_os', 'conf')
_sys_conf_path = os.path.join(_conf_dir, 'sys.conf')

_bad_conf_error = "Boot failure due to error loading {}: [{}]"
_missing_sys_conf_key = "Boot failure due to error loading {}: Critical entry {} missing from {} configuration"
_missing_device_conf_key = "Boot failure due to error loading {}: Critical entry {} missing from device configuration file"


def _load_sys_conf(system):
    try:
        with open(_sys_conf_path, 'r') as fp:
            sys_conf = json.load(fp)
            return _SysConf(sys_conf.get(system, {}))
    except ValueError as error:
        print _bad_conf_error.format(_sys_conf_path, error)
    except KeyError as error:
        print _missing_sys_conf_key.format(_sys_conf_path, error, system)

    return None


def _load_device_conf(sys_conf, args, device_conf_file):
    try:
        with open(device_conf_file, 'r') as fp:
            device_conf = json.load(fp)
            return _DeviceConf(args, device_conf, sys_conf)
    except ValueError as error:
        print _bad_conf_error.format(device_conf_file, error)
    except KeyError as error:
        print _missing_device_conf_key.format(device_conf_file, error)

    return None


def _scan_for_devices(path):
    return dict([(device[:-5], device) for device in os.listdir(path) if device.endswith('.conf')])


def _list_devices(system=None):
    def output_devices(s):
        print "\n  system={}".format(s)
        for device in _scan_for_devices(os.path.join(_conf_dir, s)):
            print "    * {}".format(device)

    print "A list of all bootable devices that can be used with the --device parameter for --system..."

    if system is None:
        output_devices('cdm')
        output_devices('cdm_tcl')
    else:
        output_devices(system)


def _set_device_boot_args(boot_args):
    print "\nNo device specified...\n"
    conf_path = os.path.join(_conf_dir, boot_args.system)
    devices = _scan_for_devices(conf_path)
    device = _get_selection(
        lambda: _list_devices(boot_args.system),
        "Input device index (input exit to abort): ",
        devices)

    boot_args.device = device


def _boot(boot_args):
    print "CDM Bootloader starting...\n"
    sys_conf = _load_sys_conf(boot_args.system)
    time.sleep(0.1)
    if not sys_conf:
        return

    print "Successfully loaded sys.conf"
    print " * System is {}".format(boot_args.system)
    print " * Device is {}".format(boot_args.device)

    if boot_args.device is None:
        _set_device_boot_args(boot_args)

    print "\nScanning available devices for system {}...".format(boot_args.system)
    available_devices = _scan_for_devices(os.path.join(_conf_dir, boot_args.system))
    for d in available_devices:
        time.sleep(0.2)
        print " * {} <- Device found".format(d) if boot_args.device == d else " * {}".format(d)

    if boot_args.device not in available_devices:
        print "\nBoot failure due to unknown device {}".format(boot_args.device)
        return

    device_conf_path = os.path.join(_conf_dir, boot_args.system, available_devices[boot_args.device])
    device_conf = _load_device_conf(sys_conf, boot_args, device_conf_path)
    if device_conf is None:
        return

    print "Successfully loaded {}".format(available_devices[boot_args.device])

    print "\nStarting CDM OS..."
    time.sleep(0.1)
    try:
        cdm_os_ = cdm_os.CdmOS(sys_conf, device_conf)
    except Exception as err:
        print "An error occurred initialising CDM OS: [{}]".format(err)
        print "Please check your configuration files"
        return

    cdm_os_.start()


def _main():
    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument('--device', required=False, help='The device to boot')
    arg_parser.add_argument('--system', choices=['cdm', 'cdm_tcl'], default='cdm', help='Which cdm build to use')
    arg_parser.add_argument('--devicexml', help='The device xml')
    arg_parser.add_argument('--list-devices', action='store_true', help='Provides a list of devices that can be launched')
    args = arg_parser.parse_args()

    _list_devices() if args.list_devices else _boot(args)


if __name__ == "__main__":
    _main()
