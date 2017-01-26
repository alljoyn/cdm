import os
import time
import random

from collections import OrderedDict


class MotionSensor(object):
    def __init__(self, system, device_name):
        self._system = system
        self._device_name = device_name

        bus_path = os.path.join(os.path.sep, 'Cdm', 'MotionSensor')

        self._battery_status_interface = [bus_path, 'org.alljoyn.SmartSpaces.Operation.BatteryStatus']
        self._alerts_interface = [bus_path, 'org.alljoyn.SmartSpaces.Operation.Alerts']
        self._trigger_sensor_interface = [bus_path, 'org.alljoyn.SmartSpaces.Operation.TriggerSensor']

        self._current_battery_level = None
        self._alarm_triggered = False

    def read_current_battery(self):
        _, battery_value = self._system.read_property_file(self._battery_status_interface, 'CurrentValue')

        try:
            self._current_battery_level = int(battery_value)
        except ValueError:
            print "Error reading battery level."

    def drain_battery(self, amount):
        new_value = self._current_battery_level - amount
        new_prop_value = ('unsigned', new_value)
        self._system.write_property_file(new_prop_value, self._battery_status_interface, 'CurrentValue')
        self._system.send_property_signal(self._battery_status_interface, 'CurrentValue', silent=True)

    def _emit_alert(self, level, code, need_acknowledgement):
        alerts = self._system.read_property_file(self._alerts_interface, 'Alerts')

        new_alert = OrderedDict([
                    ('severity', ('unsigned', level)),
                    ('alertCode', ('unsigned', code)),
                    ('needAcknowledgement', ('bool', need_acknowledgement))])

        alerts.append(new_alert)
        self._system.write_property_file(alerts, self._alerts_interface, 'Alerts')
        self._system.send_property_signal(self._alerts_interface, 'Alerts')

    def emit_battery_alert(self, level):
        self._emit_alert(level, 3, False)

    def set_trigger_sensor(self, state):
        new_prop_value = ('bool', state)
        self._system.write_property_file(new_prop_value, self._trigger_sensor_interface, 'CurrentlyTriggered')
        self._system.send_property_signal(self._trigger_sensor_interface, 'CurrentlyTriggered', silent=True)

        if state:
            self._emit_alert(1, 1, True)

    def start(self):
        self._system.send_signal('reset', self._device_name)
        print "Motion Sensor Firmware running."

        random.seed()

        while True:
            time.sleep(1)
            self.read_current_battery()
            print "Current Battery Level: ", self._current_battery_level
            self.drain_battery(1)

            if random.randint(0, 10) == 10:
                print "Motion Detected"
                self.set_trigger_sensor(True)
                self._alarm_triggered = True

            if self._alarm_triggered and random.randint(0, 10) == 10:
                print "Everything is still"
                self.set_trigger_sensor(False)
                self._alarm_triggered = False

            if self._current_battery_level == 30:
                print "Warning - Low battery"
                self.emit_battery_alert(0)

            if self._current_battery_level == 15:
                print "Battery level critical"
                self.emit_battery_alert(1)

            if self._current_battery_level <= 0:
                print "Battery depleted"
                self.emit_battery_alert(1)
                break


def build(system, device_name):
    return MotionSensor(system, device_name)
