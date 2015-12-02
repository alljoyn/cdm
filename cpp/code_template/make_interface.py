#/usr/bin/python

# usage:
# create interface files:
# python make_interface.py -n TargetTemperature -c Environment
# delete interface files:
# python make_interface.py -n TargetTemperature -c Environment -d

import os
import argparse
import datetime

interfaceTypeMap = {
    'Hid':                   'HID_INTERFACE',
    'AirQuality' :            'CURRENT_AIR_QUALITY_INTERFACE',
    'AirQualityLevel' :       'CURRENT_AIR_QUALITY_LEVEL_INTERFACE',
    'CurrentHumidity' :       'CURRENT_HUMIDITY_INTERFACE',
    'CurrentTemperature' :    'CURRENT_TEMPERATURE_INTERFACE',
    'TargetHumidity' :        'TARGET_HUMIDITY_INTERFACE',
    'TargetTemperature' :     'TARGET_TEMPERATURE_INTERFACE',
    'TargetTemperatureLevel' :'TARGET_TEMPERATURE_LEVEL_INTERFACE',
    'WaterLevel' :            'WATER_LEVEL_INTERFACE',
    'WindDirection' :         'WIND_DIRECTION_INTERFACE',
    'AirRecirculationMode' :  'AIR_RECIRCULATION_MODE_INTERFACE',
    'Alerts' :                'ALERTS_INTERFACE',
    'AudioVideoInput' :       'AUDIO_VIDEO_INPUT_INTERFACE',
    'AudioVolume' :           'AUDIO_VOLUME_INTERFACE',
    'BatteryStatus' :         'BATTERY_STATUS_INTERFACE',
    'Channel' :               'CHANNEL_INTERFACE',
    'ClimateControl' :        'CLIMATE_CONTROL_INTERFACE',
    'ClosedStatus' :          'CLOSED_STATUS_INTERFACE',
    'CurrentPower' :          'CURRENT_POWER_INTERFACE',
    'CycleControl' :          'CYCLE_CONTROL_INTERFACE',
    'DishWashingCycle' :      'DISH_WASHING_CYCLE_INTERFACE',
    'EnergyUsage' :           'ENERGY_USAGE_INTERFACE',
    'FanSpeedLevel' :         'FAN_SPEED_LEVEL_INTERFACE',
    'FilterStatus' :          'FILTER_STATUS_INTERFACE',
    'HeatingZone' :           'HEATING_ZONE_INTERFACE',
    'HvacFanMode' :           'HVAC_FAN_MODE_INTERFACE',
    'LaundryCycle' :          'LAUNDRY_CYCLE_INTERFACE',
    'MoistureOutput' :        'MOISTURE_OUTPUT_LEVEL_INTERFACE',
    'OffControl' :            'OFF_CONTROL_INTERFACE',
    'OnControl' :             'ON_CONTROL_INTERFACE',
    'OvenCycle' :             'OVEN_CYCLE_INTERFACE',
    'PlugInUnit' :            'PLUG_IN_UNITS_INTERFACE',
    'RapidMode' :             'RAPID_MODE_INTERFACE',
    'RapidModeTimed' :        'RAPID_MODE_TIMED_INTERFACE',
    'Controllability' :       'REMOTE_CONTROLLABILITY_INTERFACE',
    'RepeatMode' :            'REPEAT_MODE_INTERFACE',
    'ResourceSaving' :        'RESOURCE_SAVING_INTERFACE',
    'RobotCleaningCycle' :    'ROBOT_CLEANING_CYCLE_INTERFACE',
    'SoilLevel' :             'SOIL_LEVEL_INTERFACE',
    'SpinSpeedLevel' :        'SPIN_SPEED_LEVEL_INTERFACE',
    'Timer' :                 'TIMER_INTERFACE',
    'LanguageDisplay' :       'LANGUAGE_DISPLAY_INTERFACE',
    'TemperatureDisplay' :    'TEMPERATURE_DISPLAY_INTERFACE',
    'TimeDisplay' :           'TIME_DISPLAY_INTERFACE',
}

categoryList = ['Operation', 'Environment', 'UserInterfaceSettings']

def get_xml(name, category):
    xml = ""
    f = open('xml/org.alljoyn.SmartSpaces.' + category + '/' + name + '-v1.xml')
    while True:
        line = f.readline()
        if not line: break
        line = line.rstrip('\n')
        line = line.replace('<annotation name="org.alljoyn.Bus.Secure" value="true"/>', '<annotation name="org.alljoyn.Bus.Secure" value="false"/>')
        line = line.replace('"', "'")
        xml += '\"'+ line + '\"\n'
    f.close()
    return xml

def create_file(name, category, infile, outfile):

    if os.path.isfile(outfile):
        print 'Failed: Target file is already exist. ('+ outfile +')'
        return

    dir = os.path.dirname(outfile)
    try:
        os.makedirs(dir)
    except OSError:
        if not os.path.isdir(dir):
            raise

    xml = get_xml(name, category)
    matching = {
        '{interface_type}'     : interfaceTypeMap.get(name),
        '{interface_name}'     : name,
        '{interface_nameu}'    : name.upper(),
        '{interface_category}' : category.lower(),
        '{interface_xml}'      : xml
    }

    f1 = open(infile, 'r')
    f2 = open(outfile, 'w+')

    for line in f1.readlines():
        out_line = line

        for k,v in matching.items():
            out_line = out_line.replace(k,v)

        f2.write(out_line)

    f1.close()
    f2.close()

    print 'Created: ' + outfile
    return

def delete_confirm(prompt = 'Do you want to delete [yes/no] : '):
    while True:
        try:
            i = raw_input(prompt)
        except KeyboardInterrupt:
            return False
        if i.lower() in ('yes','y'): return True
        elif i.lower() in ('no','n'): return False

def delete_file(file_path):
    if os.path.isfile(file_path):
        os.remove(file_path)
        print 'Deleted: ' + file_path

parser = argparse.ArgumentParser()

parser.add_argument('-n', '--name', action='store', dest='name', required=True, help='interface name(e.g., TargetTemperature')
parser.add_argument('-c', '--category', action='store', dest='category', required=True, help='interface category(e.g., operatoin, environment')
parser.add_argument('-d', '--delete', action='store_true', dest='delete', default=False, help='delete files related interface')

args = parser.parse_args()

inc_folder = "../inc/alljoyn/hae/interfaces/" + args.category.lower() + "/"
src_folder = '../src/interfaces/' + args.category.lower() + '/'

def main():
    if args.name not in interfaceTypeMap.keys():
        print 'Failed: check the name of interface(case sensitive).'
        return

    if args.category not in ['Operation', 'Environment', 'UserInterfaceSettings']:
        print 'Failed: check the name of category(case sensitive).'
        return

    if args.delete == True:
        if delete_confirm() == True:
            delete_file(inc_folder + args.name + 'Interface.h')
            delete_file(inc_folder + args.name + 'IntfControllee.h')
            delete_file(inc_folder + args.name + 'IntfControlleeListener.h')
            delete_file(inc_folder + args.name + 'IntfController.h')
            delete_file(inc_folder + args.name + 'IntfControllerListener.h')
            delete_file(src_folder + args.name + 'Interface.cc')
            delete_file(src_folder + args.name + 'IntfControlleeImpl.h')
            delete_file(src_folder + args.name + 'IntfControlleeImpl.cc')
            delete_file(src_folder + args.name + 'IntfControllerImpl.h')
            delete_file(src_folder + args.name + 'IntfControllerImpl.cc')
    else:
        create_file(args.name, args.category, 'TemplateInterface.h', inc_folder + args.name + 'Interface.h')
        create_file(args.name, args.category, 'TemplateIntfControllee.h', inc_folder + args.name + 'IntfControllee.h')
        create_file(args.name, args.category, 'TemplateIntfControlleeListener.h', inc_folder + args.name + 'IntfControlleeListener.h')
        create_file(args.name, args.category, 'TemplateIntfController.h', inc_folder + args.name + 'IntfController.h')
        create_file(args.name, args.category, 'TemplateIntfControllerListener.h', inc_folder + args.name + 'IntfControllerListener.h')
        create_file(args.name, args.category, 'TemplateInterface.cc', src_folder + args.name + 'Interface.cc')
        create_file(args.name, args.category, 'TemplateIntfControlleeImpl.h', src_folder + args.name + 'IntfControlleeImpl.h')
        create_file(args.name, args.category, 'TemplateIntfControlleeImpl.cc', src_folder + args.name + 'IntfControlleeImpl.cc')
        create_file(args.name, args.category, 'TemplateIntfControllerImpl.h', src_folder + args.name + 'IntfControllerImpl.h')
        create_file(args.name, args.category, 'TemplateIntfControllerImpl.cc', src_folder + args.name + 'IntfControllerImpl.cc')

main()
