#!/usr/bin/env python

import os
import json
import argparse
import itertools
import time

import cdm_os


def _raise_value_error(msg):
    raise ValueError(msg)


class _SysConf(object):
    def __init__(self, sys_conf):
        self.bin_dir = sys_conf['bin_dir'] if os.path.exists(sys_conf['bin_dir']) else _raise_value_error("bin dir does not exist")
        self.mount_dir = sys_conf['mount_dir']

def _extract_device_xml(boot_args, device_conf):
    if device_conf['devicexml'] == 'from args' and not boot_args.devicexml:
        raise ValueError("Device configuration wants a device xml passed in as an argument but argument missing")

    return boot_args.devicexml if boot_args.devicexml else device_conf['devicexml']


class _DeviceConf(object):
    def __init__(self, boot_args, device_conf):
        self.device_xml = _extract_device_xml(boot_args, device_conf)
        self.device = device_conf['bin']
        self.state_dir = device_conf['state_dir']
        self.certs_dir = device_conf['certs_dir']
        self.boot_program = device_conf['boot_program']
        self.args = self._process_args(boot_args, device_conf['args'])

    def _process_args(self, boot_args, args_list):
        _macros = {
            '%%devicexml': self.device_xml,
            '%%certs-dir': boot_args.cert_dir if boot_args.cert_dir else self.certs_dir,
            '%%state-dir': boot_args.state_dir if boot_args.state_dir else self.state_dir
        }

        processed_args = [_macros.get(arg, arg) for arg in args_list]

        # scan for empty args and these need to be removed. Also, if the arg is empty then remove the arg before it as
        # it will be a flag arg like --cert-dir or --state-dir
        indices_to_remove = [[i-1, i] if i != 0 and not arg else i for i, arg in enumerate(processed_args) if not arg]
        flattened_list = list(itertools.chain.from_iterable(indices_to_remove))
        final_args = [arg for i, arg in enumerate(processed_args) if i not in flattened_list]

        return final_args


_conf_dir = os.path.join('.', 'conf')
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


def _load_device_conf(args, device_conf_file):
    try:
        with open(device_conf_file, 'r') as fp:
            device_conf = json.load(fp)
            return _DeviceConf(args, device_conf)
    except ValueError as error:
        print _bad_conf_error.format(device_conf_file, error)
    except KeyError as error:
        print _missing_device_conf_key.format(device_conf_file, error)

    return None


def _scan_for_devices(path):
    return dict([(device[:-5], device) for device in os.listdir(path) if device.endswith('.conf')])


def _boot(boot_args):
    print "CDM Bootloader starting...\n"
    sys_conf = _load_sys_conf(boot_args.system)
    time.sleep(0.1)
    if not sys_conf:
        return

    print "Successfully loaded sys.conf"
    print " * System is {}".format(boot_args.system)
    print " * Device is {}".format(boot_args.device)
    print "\nScanning available devices..."
    available_devices = _scan_for_devices(os.path.join(_conf_dir, boot_args.system))
    for d in available_devices:
        time.sleep(0.2)
        print " * {} <- Device found".format(d) if boot_args.device == d else " * {}".format(d)

    if boot_args.device not in available_devices:
        print "Boot failure due to unknown device {}".format(boot_args.device)
        return

    device_conf_path = os.path.join(_conf_dir, boot_args.system, available_devices[boot_args.device])
    device_conf = _load_device_conf(boot_args, device_conf_path)
    print "Successfully loaded {}".format(available_devices[boot_args.device])

    print "\nStarting CDM OS..."
    time.sleep(0.1)
    cdm_os_ = cdm_os.CdmOS(sys_conf, device_conf)
    cdm_os_.start()


def _main():
    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument('device', help='The device to boot')
    arg_parser.add_argument('--system', choices=['cdm', 'cdm_tcl'], default='cdm', help='Which cdm build to use')
    arg_parser.add_argument('--devicexml', help='An override for the device xml')
    arg_parser.add_argument('--cert-dir', help='An override for the certificate directory')
    arg_parser.add_argument('--state-dir', help='An override for the devices state directory')
    arg_parser.add_argument('--emit-on-set', help='An override for the devices state directory')
    args = arg_parser.parse_args()

    _boot(args)


if __name__ == "__main__":
    _main()
