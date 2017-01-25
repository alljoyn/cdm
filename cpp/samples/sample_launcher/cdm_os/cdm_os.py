import sys
import os
import random
import subprocess
import threading
import time
from xml.dom import minidom
import importlib

import property_io


_intro1 = r"""
           _ .-') _  _   .-')                         .-')
          ( (  OO) )( '.( OO )_                      ( OO ).
   .-----. \     .'_ ,--.   ,--.)       .-'),-----. (_)---\_)
  '  .--./ ,`'--..._)|   `.'   |       ( OO'  .-.  '/    _ |
  |  |('-. |  |  \  '|         |       /   |  | |  |\  :` `.
 /_) |OO  )|  |   ' ||  |'.'|  |       \_) |  |\|  | '..`''.)
 ||  |`-'| |  |   / :|  |   |  |         \ |  | |  |.-._)   \
(_'  '--'\ |  '--'  /|  |   |  |          `'  '-'  '\       /
   `-----'  -------' `--'   `--'            `-----'  `-----'
"""

_intro2 = r"""
    _______    ______     ,---.    ,---.            ,-----.       .-'''-.
   /   __  \  |    _ `''. |    \  /    |          .'  .-,  '.    / _     \
  | ,_/  \__) | _ | ) _  \|  ,  \/  ,  |         / ,-.|  \ _ \  (`' )/`--'
,-./  )       |( ''_'  ) ||  |\_   /|  |        ;  \  '_ /  | :(_ o _).
\  '_ '`)     | . (_) `. ||  _( )_/ |  |        |  _`,/ \ _/  | (_,_). '.
 > (_)  )  __ |(_    ._) '| (_ o _) |  |        : (  '\_/ \   ;.---.  \  :
(  .  .-'_/  )|  (_.\.' / |  (_,_)  |  |         \ `"/  \  ) / \    `-'  |
 `-'`-'     / |       .'  |  |      |  |          '. \_/``".'   \       /
   `._____.'  '-----'`    '--'      '--'            '-----'      `-...-'

"""

_intro3 = r"""
 _______  ______   _______    _______  _______
(  ____ \(  __  \ (       )  (  ___  )(  ____ \
| (    \/| (  \  )| () () |  | (   ) || (    \/
| |      | |   ) || || || |  | |   | || (_____
| |      | |   | || |(_)| |  | |   | |(_____  )
| |      | |   ) || |   | |  | |   | |      ) |
| (____/\| (__/  )| )   ( |  | (___) |/\____) |
(_______/(______/ |/     \|  (_______)\_______)

"""

_intro4 = r"""
   ____  ____    __  __         U  ___ u  ____
U /"___||  _"\ U|' \/ '|u        \/"_ \/ / __"| u
\| | u /| | | |\| |\/| |/        | | | |<\___ \/
 | |/__U| |_| |\| |  | |     .-,_| |_| | u___) |
  \____||____/ u|_|  |_|      \_)-\___/  |____/>>
 _// \\  |||_  <<,-,,-.            \\     )(  (__)
(__)(__)(__)_)  (./  \.)          (__)   (__)

"""

_intro5 = r"""
   ____   ______       __    __          ____      _____
  / ___) (_  __ \      \ \  / /         / __ \    / ____\
 / /       ) ) \ \     () \/ ()        / /  \ \  ( (___
( (       ( (   ) )    / _  _ \       ( ()  () )  \___ \
( (        ) )  ) )   / / \/ \ \      ( ()  () )      ) )
 \ \___   / /__/ /   /_/      \_\      \ \__/ /   ___/ /
  \____) (______/   (/          \)      \____/   /____/

"""

_intro6 = r"""
 ____ ____ ____ _________ ____ ____
||C |||D |||M |||       |||O |||S ||
||__|||__|||__|||_______|||__|||__||
|/__\|/__\|/__\|/_______\|/__\|/__\|
"""

_intro7 = r"""
.------..------..------.     .------..------.
|C.--. ||D.--. ||M.--. |.-.  |O.--. ||S.--. |
| :/\: || :/\: || (\/) ((5)) | :/\: || :/\: |
| :\/: || (__) || :\/: |'-.-.| :\/: || :\/: |
| '--'C|| '--'D|| '--'M| ((1)) '--'O|| '--'S|
`------'`------'`------'  '-'`------'`------'
"""

_intro8 = r"""
 ______________  ___  _____ _____
/  __ \  _  \  \/  | |  _  /  ___|
| /  \/ | | | .  . | | | | \ `--.
| |   | | | | |\/| | | | | |`--. \
| \__/\ |/ /| |  | | \ \_/ /\__/ /
 \____/___/ \_|  |_/  \___/\____/
"""

_intro9 = r"""
 ___   ____  ,__ __       __
 / (_) (|   \/|  |  |     /\_\/ ()
|       |    ||  |  |    |    | /\
|      _|    ||  |  |    |    |/  \
 \___/(/\___/ |  |  |_/   \__//(__/
"""

_intro10 = r"""
 _______ ______  _______    _______ ______
(_______|______)(_______)  (_______) _____)
 _       _     _ _  _  _    _     ( (____
| |     | |   | | ||_|| |  | |   | \____ \
| |_____| |__/ /| |   | |  | |___| |____) )
 \______)_____/ |_|   |_|   \_____(______/
"""

_intros = [_intro1, _intro2, _intro3, _intro4, _intro5, _intro6, _intro7, _intro8, _intro9, _intro10]


class CdmOS(object):
    def __init__(self, sys_conf, device_conf):
        self._sys_conf = sys_conf
        self._device_conf = device_conf
        self._state_dir = os.path.join(self._sys_conf.mount_dir, self._device_conf.state_dir)
        self._device_name = self._extract_device_name()
        self._file_system = {}
        self._property_lut = self._build_property_lut()

        self._boot_program = self._make_boot_program()
        self._proc = None

        self._running = False

    def _proc_poll(self):
        while self._running:
            if self._proc is None:
                print "ERROR device failed."
                quit(1)

            poll_result = self._proc.poll()
            if poll_result is not None:
                print "ERROR device failed with error code: {}".format(poll_result)
                quit(poll_result)

    def _extract_device_name(self):
        xml = minidom.parse(self._device_conf.device_xml)
        device_name_nodes = xml.getElementsByTagName('DeviceName')
        return device_name_nodes[0].childNodes[0].nodeValue if device_name_nodes and device_name_nodes[0].childNodes else "Unknown Device Name"

    def _build_property_lut(self):
        def extract_property_nodes(interface_node):
            return [str(node.attributes['name'].nodeValue) for node in interface_node.childNodes if node.nodeName == 'Property']

        def extract_interface_nodes(obj_path_node):
            def mk_tuple(n):
                return str(n.attributes['name'].nodeValue), extract_property_nodes(n)

            interface_nodes = [mk_tuple(node) for node in obj_path_node.childNodes if node.nodeName == 'Interface']
            return dict(interface_nodes)

        xml = minidom.parse(self._device_conf.device_xml)
        obj_list = xml.getElementsByTagName('Object')

        return dict([(str(obj_path.attributes['path'].nodeValue), extract_interface_nodes(obj_path)) for obj_path in obj_list])

    def _build_device_file_system(self):
        property_lut = {}

        for root, _, files in os.walk(self._state_dir):
            _, dirname = root.split(self._state_dir)
            processed_files = [filename for filename in files if not filename.startswith('.')]
            if processed_files:
                bus_path = os.path.dirname(dirname)
                interface = os.path.basename(dirname)
                property_lut.setdefault(bus_path, {})[interface] = processed_files

        return property_lut

    def _make_boot_program(self):
        try:
            boot_prog_lib = importlib.import_module("cdm_os.bin." + self._device_conf.boot_program)
            boot_prog = boot_prog_lib.build(self, self._device_name)
            print " * Boot program '{}' built".format(self._device_conf.boot_program)
            return boot_prog
        except ImportError:
            print "ERROR: Boot program {} does not exist in cdm_os.bin".format(self._device_conf.boot_program)
            return None
        except AttributeError:
            print "Error: boot program {} does not contain a 'build' function".format(self._device_conf.boot_program)

    def _find_property_file_on_disk(self, path, prop_file_name):
        cwd, prop_lut = self.retrieve_path(path)

        if not cwd:
            print "Invalid Path: {}".format(path)
            return None

        if prop_file_name in cwd:
            if type(cwd) is list:
                base_str = os.path.sep
                file_dir = base_str.join([self._state_dir] + path)
                return os.path.join(file_dir, prop_file_name)
            else:
                print "{} is not a file".format(prop_file_name)
        else:
            print "Cannot find property file {} in {}".format(prop_file_name, ';'.join(path))

        return None

    def retrieve_path(self, full_path):
        property_lut = self._property_lut
        file_system = self._file_system
        for path in full_path:
            file_system = file_system[path] if path in file_system else []
            property_lut = property_lut[path] if path in property_lut else []

        return file_system, property_lut

    def read_property_file(self, path, prop_file_name):
        try:
            full_path = self._find_property_file_on_disk(path, prop_file_name)
            return property_io.read_property_file(full_path)
        except Exception as e:
            print "An error occurred reading {}: {}".format(os.path.basename(prop_file_name), e)

    def write_property_file(self, prop_data, path, prop_file_name):
        try:
            full_path = self._find_property_file_on_disk(path, prop_file_name)
            return property_io.write_property_file(prop_data, full_path)
        except Exception as e:
            print "An error occurred reading {}: {}".format(os.path.basename(prop_file_name), e)

    def send_signal(self, signal, signal_dest):
        try:
            self._proc.stdin.write(signal + "\n")
            print "Signal emitted for {}".format(signal_dest)
        except Exception as err:
            print "Error emitting signal for {}: {}".format(signal_dest, err)

    def send_property_signal(self, path, property_name):
        signal_dest = "{} {}".format(' '.join(path), property_name)
        signal = "changed {}".format(signal_dest)
        self.send_signal(signal, signal_dest)

    def start(self):
        self._running = True

        time.sleep(0.3)
        bin_path = os.path.join(self._sys_conf.bin_dir, self._device_conf.device)
        if not os.path.exists(bin_path):
            print "Device bin {} not found in {} - Cannot start device".format(self._device_conf.device, self._sys_conf.bin_dir)
            return

        os.chdir(self._sys_conf.mount_dir)
        launch_args = [bin_path] + self._device_conf.args
        try:
            self._proc = subprocess.Popen(launch_args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            print " * Device bin {} started successfully\n".format(self._device_conf.device)
        except Exception as err:
            print "ERROR - Device bin {} failed to start: {}".format(self._device_conf.device, err)
            return

        print "Mounting state directory..."
        time.sleep(0.4)
        print "Scanning devices file system...\n"
        self._file_system = self._build_device_file_system()
        time.sleep(0.2)

        random.seed()
        intro_index = random.randint(0, len(_intros)-1)
        print "Welcome to{}\nCDM OS - for emulated CDM devices Version 16.10\n".format(_intros[intro_index])
        time.sleep(0.1)

        monitor = threading.Thread(target=self._proc_poll)
        monitor.start()

        try:
            print "Starting boot program '{}'...".format(self._device_conf.boot_program)
            self._boot_program.start()
            print "Boot program '{}' has terminated - System shutdown initiated".format(self._device_conf.boot_program)
        except Exception as err:
            print "ERROR during boot program {}: {}".format(self._device_conf.boot_program, err)

        self._running = False
        time.sleep(0.1)
        print "Shutting down device monitor..."
        monitor.join()
        print "Shutting down device bin {}...".format(self._device_conf.device)
        time.sleep(0.2)
        try:
            self._proc.kill()
        except OSError:
            pass
        print "Goodbye!"
