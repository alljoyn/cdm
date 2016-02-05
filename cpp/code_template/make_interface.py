#/usr/bin/python

# usage:
# create hae interface files:
# python make_interface.py -n TargetTemperature -c Environment
# delete hae interface files:
# python make_interface.py -n TargetTemperature -c Environment -d

# create vendor defined interface files:
# python make_interface.py -n Test -v
# delete vendor defined interface fiels:
# python make_interface.py -n Test -v -d

import os
import argparse
import datetime

interfaceTypeMap = {
    'Hid':                    'HID_INTERFACE',
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
    'DishWashingCyclePhase' : 'DISH_WASHING_CYCLE_PHASE_INTERFACE',
    'EnergyUsage' :           'ENERGY_USAGE_INTERFACE',
    'FanSpeedLevel' :         'FAN_SPEED_LEVEL_INTERFACE',
    'FilterStatus' :          'FILTER_STATUS_INTERFACE',
    'HeatingZone' :           'HEATING_ZONE_INTERFACE',
    'HvacFanMode' :           'HVAC_FAN_MODE_INTERFACE',
    'LaundryCyclePhase' :     'LAUNDRY_CYCLE_PHASE_INTERFACE',
    'MoistureOutput' :        'MOISTURE_OUTPUT_LEVEL_INTERFACE',
    'OffControl' :            'OFF_CONTROL_INTERFACE',
    'OnControl' :             'ON_CONTROL_INTERFACE',
    'OvenCyclePhase' :        'OVEN_CYCLE_PHASE_INTERFACE',
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
    xml = ''
    filepath = 'xml/org.alljoyn.SmartSpaces.' + category + '/' + name + '-v1.xml'
    if os.path.isfile(filepath) == False:
        print 'Failed: There is no xml file('+ filepath +')'
        return

    f = open(filepath)
    while True:
        line = f.readline()
        if not line: break
        line = line.rstrip('\n')
        line = line.replace('<annotation name="org.alljoyn.Bus.Secure" value="true"/>', '<annotation name="org.alljoyn.Bus.Secure" value="false"/>')
        line = line.replace('"', "'")
        xml += '\"'+ line + '\"\n'
    f.close()
    return xml

def get_interface_type(name):
    if vendorDefined == False:
        return interfaceTypeMap.get(name)

    return 'VENDOR_DEFIEND_INTERFACE'


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

    xml = ""
    if vendorDefined == False:
        xml = get_xml(name, category)
        if not xml:
            return

    matching = {
        '{interface_type}'     : get_interface_type(name),
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
parser.add_argument('-c', '--category', action='store', dest='category', help='interface category(e.g., operatoin, environment')
parser.add_argument('-d', '--delete', action='store_true', dest='delete', default=False, help='delete files related interface')
parser.add_argument('-v', '--vendor', action='store_true', dest='vendor', default=False, help='create vendor defined interface')

args = parser.parse_args()


def main():
    global vendorDefined
    vendorDefined= args.vendor

    if vendorDefined == False and args.name not in interfaceTypeMap.keys():
        print 'Failed: check the name of interface(case sensitive).'
        return

    if vendorDefined == False and args.category not in ['Operation', 'Environment', 'UserInterfaceSettings']:
        print 'Failed: check the name of category(case sensitive).'
        return

    global inc_folder, src_folder
    if vendorDefined == True:
        template_folder='./vendor_defined_interface_template/'
        inc_folder='./vendor_defined/'
        src_folder='./vendor_defined/'
        category='VendorDefined'
    else:
        template_folder='./interface_template/'
        inc_folder = "../inc/alljoyn/hae/interfaces/" + args.category.lower() + "/"
        src_folder = '../src/interfaces/' + args.category.lower() + '/'
        category = args.category

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
        create_file(args.name, category, template_folder + 'TemplateInterface.h', inc_folder + args.name + 'Interface.h')
        create_file(args.name, category, template_folder + 'TemplateIntfControllee.h', inc_folder + args.name + 'IntfControllee.h')
        create_file(args.name, category, template_folder + 'TemplateIntfControlleeListener.h', inc_folder + args.name + 'IntfControlleeListener.h')
        create_file(args.name, category, template_folder + 'TemplateIntfController.h', inc_folder + args.name + 'IntfController.h')
        create_file(args.name, category, template_folder + 'TemplateIntfControllerListener.h', inc_folder + args.name + 'IntfControllerListener.h')
        create_file(args.name, category, template_folder + 'TemplateInterface.cc', src_folder + args.name + 'Interface.cc')
        create_file(args.name, category, template_folder + 'TemplateIntfControlleeImpl.h', src_folder + args.name + 'IntfControlleeImpl.h')
        create_file(args.name, category, template_folder + 'TemplateIntfControlleeImpl.cc', src_folder + args.name + 'IntfControlleeImpl.cc')
        create_file(args.name, category, template_folder + 'TemplateIntfControllerImpl.h', src_folder + args.name + 'IntfControllerImpl.h')
        create_file(args.name, category, template_folder + 'TemplateIntfControllerImpl.cc', src_folder + args.name + 'IntfControllerImpl.cc')

main()
