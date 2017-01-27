import os
import time
import threading
import random


class TemperatureSensor(object):
    def __init__(self, system, device_name):
        self._system = system
        self._device_name = device_name

        bus_path = os.path.join(os.path.sep, 'Cdm', 'TempSensor')
        self._current_humidity_interface = [bus_path, 'org.alljoyn.SmartSpaces.Environment.CurrentHumidity']
        self._current_temperature_interface = [bus_path, 'org.alljoyn.SmartSpaces.Environment.CurrentTemperature']

        self._active = False

    def _write_value(self, interface_path, prop_name, value):
        new_prop_value = ('double', value)
        self._system.write_property_file(new_prop_value, interface_path, prop_name)

    def _temp_sensor(self):
        cur_temp = random.randint(15, 30)
        cur_hum = random.randint(30, 75)

        while self._active:
            time.sleep(1)

            cur_temp += random.random() - 0.5
            cur_hum += random.random() - 0.5

            self._write_value(self._current_temperature_interface, "CurrentValue", cur_temp)
            self._write_value(self._current_humidity_interface, "CurrentValue", cur_hum)

    def start(self):
        self._active = True
        random.seed()

        sensor = threading.Thread(target=self._temp_sensor)
        sensor.start()
        print "Temperature Sensor Firmware running...Press any key to end."
        raw_input()
        print "Done"
        self._active = False
        sensor.join()


def build(system, device_name):
    return TemperatureSensor(system, device_name)
