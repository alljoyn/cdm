#include <cstdlib>

#include "DeviceCommands.h"
#include "ControllerSample.h"
#include "AudioVolumeCommands.h"
#include "ChannelCommands.h"
#include "AudioVideoInputCommands.h"
#include "HidCommands.h"
#include "OnControlCommands.h"
#include "OffControlCommands.h"
#include "OnOffStatusCommands.h"
#include "ResourceSavingCommands.h"
#include "FanSpeedLevelCommands.h"
#include "CurrentTemperatureCommands.h"
#include "TargetTemperatureCommands.h"
#include "ClimateControlModeCommands.h"
#include "WindDirectionCommands.h"
#include "AirRecirculationModeCommands.h"
#include "VendorDefinedCommands.h"
#include "BatteryStatusCommands.h"
#include "RepeatModeCommands.h"
#include "RobotCleaningCyclePhaseCommands.h"
#include "CurrentPowerCommands.h"
#include "EnergyUsageCommands.h"
#include "CycleControlCommands.h"
#include "RemoteControllabilityCommands.h"
#include "RapidModeCommands.h"
#include "SoilLevelCommands.h"
#include "SpinSpeedLevelCommands.h"
#include "WaterLevelCommands.h"
#include "HeatingZoneCommands.h"
#include "DishWashingCyclePhaseCommands.h"
#include "LaundryCyclePhaseCommands.h"
#include "OvenCyclePhaseCommands.h"
#include "TimerCommands.h"
#include "ClosedStatusCommands.h"
#include "AlertsCommands.h"

DeviceCommands::DeviceCommands(ControllerSample* sample, DeviceInfoPtr& info)
: ControllerCommands(sample)
, m_sample(sample)
, m_deviceInfo(info)
{
}

DeviceCommands::~DeviceCommands()
{
}

void DeviceCommands::Init()
{
    RegisterCommand(&DeviceCommands::OnCmdSelectInterface, "si", "select interface");
    PrintCommands();
}

void DeviceCommands::OnCmdSelectInterface(Commands* commands, std::string& cmd)
{
    ControllerSample* sample = static_cast<DeviceCommands*>(commands)->GetControllerSample();
    DeviceInfoPtr& info = static_cast<DeviceCommands*>(commands)->GetDeviceInfo();
    int order = 0;
    char buf[1024];
    std::map<int, std::string> indexKeyMap;

    size_t path_num = info->GetAboutObjectDescription().GetPaths(NULL, 0);
    const char** paths = new const char*[path_num];
    info->GetAboutObjectDescription().GetPaths(paths, path_num);

    for (size_t i = 0; i < path_num; ++i) {
        if (!strncmp(paths[i], "/About", strlen(paths[i]))) {
            continue;
        }

        cout << paths[i] << endl;
        size_t intf_num = info->GetAboutObjectDescription().GetInterfaces(paths[i], NULL, 0);
        const char** intfs = new const char*[intf_num];
        info->GetAboutObjectDescription().GetInterfaces(paths[i], intfs, intf_num);

        for (size_t j = 0; j < intf_num; ++j) {
            order++;
            cout << order << " : " << intfs[j] << endl;
            sprintf(buf, "%s:%s", paths[i], intfs[j]);
            std::string key(buf);

            if (!(sample->GetCurrentCommands()->GetChild(key))) {
                Commands* intfCommands = static_cast<DeviceCommands*>(commands)->CreateInterfaceCommands(commands, intfs[j], paths[i]);
                if (!intfCommands) {
                    cout << "Command object creation for interface " << intfs[j] << " is failed" << endl;
                    continue;
                }

                sample->GetCurrentCommands()->RegisterChildCommands(key, intfCommands);
            }
            indexKeyMap[order] = key;
        }
        delete [] intfs;
    }
    delete [] paths;

    int index = ReadIndex();
    Commands* selected = sample->GetCurrentCommands()->GetChild(indexKeyMap[index]);
    sample->PushCommands(selected);
}

Commands* DeviceCommands::CreateInterfaceCommands(Commands* commands, const char* intfName, const char* objectPath)
{
    Commands* intfCommands = NULL;

    ControllerSample* sample = static_cast<DeviceCommands*>(commands)->GetControllerSample();
    DeviceInfoPtr& info = static_cast<DeviceCommands*>(commands)->GetDeviceInfo();

    if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.AudioVolume", strlen(intfName))) {
        intfCommands = new AudioVolumeCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.Channel", strlen(intfName))) {
        intfCommands = new ChannelCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", strlen(intfName))) {
        intfCommands = new AudioVideoInputCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.Input.Hid", strlen(intfName))) {
        intfCommands = new HidCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.OnControl", strlen(intfName))) {
        intfCommands = new OnControlCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.OffControl", strlen(intfName))) {
        intfCommands = new OffControlCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", strlen(intfName))) {
        intfCommands = new OnOffStatusCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.ResourceSaving", strlen(intfName))) {
        intfCommands = new ResourceSavingCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", strlen(intfName))) {
        intfCommands = new FanSpeedLevelCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.BatteryStatus", strlen(intfName))) {
        intfCommands = new BatteryStatusCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Environment.CurrentTemperature", strlen(intfName))) {
        intfCommands = new CurrentTemperatureCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Environment.TargetTemperature", strlen(intfName))) {
        intfCommands = new TargetTemperatureCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", strlen(intfName))) {
        intfCommands = new ClimateControlModeCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Environment.WindDirection", strlen(intfName))) {
        intfCommands = new WindDirectionCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode", strlen(intfName))) {
        intfCommands = new AirRecirculationModeCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.RepeatMode", strlen(intfName))) {
        intfCommands = new RepeatModeCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase", strlen(intfName))) {
        intfCommands = new RobotCleaningCyclePhaseCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.EnergyUsage", strlen(intfName))) {
        intfCommands = new EnergyUsageCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "com.foo.bar.test", strlen(intfName))) {
        intfCommands = new VendorDefinedCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.CurrentPower", strlen(intfName))) {
        intfCommands = new CurrentPowerCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.CycleControl", strlen(intfName))) {
        intfCommands = new CycleControlCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.RapidMode", strlen(intfName))) {
        intfCommands = new RapidModeCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.SoilLevel", strlen(intfName))) {
        intfCommands = new SoilLevelCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel", strlen(intfName))) {
        intfCommands = new SpinSpeedLevelCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Environment.WaterLevel", strlen(intfName))) {
        intfCommands = new WaterLevelCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.HeatingZone", strlen(intfName))) {
        intfCommands = new HeatingZoneCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", strlen(intfName))) {
        intfCommands = new DishWashingCyclePhaseCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase", strlen(intfName))) {
        intfCommands = new OvenCyclePhaseCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase", strlen(intfName))) {
        intfCommands = new LaundryCyclePhaseCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.Timer", strlen(intfName))) {
        intfCommands = new TimerCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.RemoteControllability", strlen(intfName))) {
        intfCommands = new RemoteControllabilityCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.ClosedStatus", strlen(intfName))) {
        intfCommands = new ClosedStatusCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.Alerts", strlen(intfName))) {
        intfCommands = new AlertsCommands(sample, info, objectPath);
    }
    return intfCommands;
}
