/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/DeviceTypeDescription.h>
#include "DeviceEmulator.h"
#include "../BaseSample/Controllee/CommandsFactory.h"
#include "../BaseSample/Controllee/AirRecirculationModeListener.h"
#include "../BaseSample/Controllee/AudioVideoInputListener.h"
#include "../BaseSample/Controllee/AudioVolumeListener.h"
#include "../BaseSample/Controllee/BatteryStatusListener.h"
#include "../BaseSample/Controllee/ChannelListener.h"
#include "../BaseSample/Controllee/ClimateControlModeListener.h"
#include "../BaseSample/Controllee/CurrentPowerListener.h"
#include "../BaseSample/Controllee/CurrentTemperatureListener.h"
#include "../BaseSample/Controllee/EnergyUsageListener.h"
#include "../BaseSample/Controllee/FanSpeedLevelListener.h"
#include "../BaseSample/Controllee/HidListener.h"
#include "../BaseSample/Controllee/OnControlListener.h"
#include "../BaseSample/Controllee/OffControlListener.h"
#include "../BaseSample/Controllee/OnOffStatusListener.h"
#include "../BaseSample/Controllee/RepeatModeListener.h"
#include "../BaseSample/Controllee/ResourceSavingListener.h"
#include "../BaseSample/Controllee/RobotCleaningCyclePhaseListener.h"
#include "../BaseSample/Controllee/TargetTemperatureListener.h"
#include "../BaseSample/Controllee/WindDirectionListener.h"
#include "../BaseSample/Controllee/ClosedStatusListener.h"
#include "../BaseSample/Controllee/RapidModeListener.h"
#include "../BaseSample/Controllee/RemoteControllabilityListener.h"

#include "../BaseSample/Controllee/DishWashingCyclePhaseListener.h"
#include "../BaseSample/Controllee/LaundryCyclePhaseListener.h"
#include "../BaseSample/Controllee/OvenCyclePhaseListener.h"
#include "../BaseSample/Controllee/SoilLevelListener.h"
#include "../BaseSample/Controllee/SpinSpeedLevelListener.h"
#include "../BaseSample/Controllee/WaterLevelListener.h"
#include "../BaseSample/Controllee/HeatingZoneListener.h"
#include "../BaseSample/Controllee/TimerListener.h"
#include "../BaseSample/Controllee/CycleControlListener.h"

#include "../BaseSample/Controllee/CurrentAirQualityListener.h"
#include "../BaseSample/Controllee/CurrentAirQualityLevelListener.h"
#include "../BaseSample/Controllee/CurrentHumidityListener.h"
#include "../BaseSample/Controllee/TargetHumidityListener.h"
#include "../BaseSample/Controllee/TargetTemperatureLevelListener.h"
#include "../BaseSample/Controllee/MoistureOutputLevelListener.h"
#include "../BaseSample/Controllee/FilterStatusListener.h"
#include "../BaseSample/Controllee/HvacFanModeListener.h"
#include "../BaseSample/Controllee/PlugInUnitsListener.h"
#include "../BaseSample/Controllee/RapidModeTimedListener.h"

using namespace std;
using namespace qcc;
using namespace ajn;
using namespace services;

DeviceEmulator::DeviceEmulator(const string& configPath)
: m_configLoader(configPath)
{
}

DeviceEmulator::~DeviceEmulator()
{
    if (m_bus) {
        delete m_bus;
    }

    if (m_virtualDevice) {
        delete m_virtualDevice;
    }
}

void DeviceEmulator::InitCommandsFactory()
{
    CommandsFactory* factory = CommandsFactory::GetInstance();

    if (!factory) {
        return;
    }
    factory->RegisterCreator(AIR_RECIRCULATION_MODE_INTERFACE, AirRecirculationModeCommands::CreateCommands);
    factory->RegisterCreator(AUDIO_VIDEO_INPUT_INTERFACE, AudioVideoInputCommands::CreateCommands);
    factory->RegisterCreator(AUDIO_VOLUME_INTERFACE, AudioVolumeCommands::CreateCommands);
    factory->RegisterCreator(BATTERY_STATUS_INTERFACE, BatteryStatusCommands::CreateCommands);
    factory->RegisterCreator(CHANNEL_INTERFACE, ChannelCommands::CreateCommands);
    factory->RegisterCreator(CLIMATE_CONTROL_MODE_INTERFACE, ClimateControlModeCommands::CreateCommands);
    factory->RegisterCreator(CURRENT_POWER_INTERFACE, CurrentPowerCommands::CreateCommands);
    factory->RegisterCreator(CURRENT_TEMPERATURE_INTERFACE, CurrentTemperatureCommands::CreateCommands);
    factory->RegisterCreator(ENERGY_USAGE_INTERFACE, EnergyUsageCommands::CreateCommands);
    factory->RegisterCreator(FAN_SPEED_LEVEL_INTERFACE, FanSpeedLevelCommands::CreateCommands);
    factory->RegisterCreator(HID_INTERFACE, HidCommands::CreateCommands);
    factory->RegisterCreator(ON_CONTROL_INTERFACE, OnControlCommands::CreateCommands);
    factory->RegisterCreator(OFF_CONTROL_INTERFACE, OffControlCommands::CreateCommands);
    factory->RegisterCreator(ON_OFF_STATUS_INTERFACE, OnOffStatusCommands::CreateCommands);
    factory->RegisterCreator(REPEAT_MODE_INTERFACE, RepeatModeCommands::CreateCommands);
    factory->RegisterCreator(RESOURCE_SAVING_INTERFACE, ResourceSavingCommands::CreateCommands);
    factory->RegisterCreator(TARGET_TEMPERATURE_INTERFACE, TargetTemperatureCommands::CreateCommands);
    factory->RegisterCreator(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, RobotCleaningCyclePhaseCommands::CreateCommands);
    factory->RegisterCreator(WIND_DIRECTION_INTERFACE, WindDirectionCommands::CreateCommands);
    factory->RegisterCreator(CLOSED_STATUS_INTERFACE, ClosedStatusCommands::CreateCommands);
    factory->RegisterCreator(RAPID_MODE_INTERFACE, RapidModeCommands::CreateCommands);
    factory->RegisterCreator(REMOTE_CONTROLLABILITY_INTERFACE, RemoteControllabilityCommands::CreateCommands);
    factory->RegisterCreator(DISH_WASHING_CYCLE_PHASE_INTERFACE, DishWashingCyclePhaseCommands::CreateCommands);
    factory->RegisterCreator(LAUNDRY_CYCLE_PHASE_INTERFACE, LaundryCyclePhaseCommands::CreateCommands);
    factory->RegisterCreator(OVEN_CYCLE_PHASE_INTERFACE, OvenCyclePhaseCommands::CreateCommands);

    factory->RegisterCreator(SOIL_LEVEL_INTERFACE, SoilLevelCommands::CreateCommands);
    factory->RegisterCreator(SPIN_SPEED_LEVEL_INTERFACE, SpinSpeedLevelCommands::CreateCommands);
    factory->RegisterCreator(WATER_LEVEL_INTERFACE, WaterLevelCommands::CreateCommands);
    factory->RegisterCreator(HEATING_ZONE_INTERFACE, HeatingZoneCommands::CreateCommands);
    factory->RegisterCreator(TIMER_INTERFACE, TimerCommands::CreateCommands);
    factory->RegisterCreator(CYCLE_CONTROL_INTERFACE, CycleControlCommands::CreateCommands);

    factory->RegisterCreator(CURRENT_AIR_QUALITY_INTERFACE, CurrentAirQualityCommands::CreateCommands);
    factory->RegisterCreator(CURRENT_AIR_QUALITY_LEVEL_INTERFACE, CurrentAirQualityLevelCommands::CreateCommands);
    factory->RegisterCreator(CURRENT_HUMIDITY_INTERFACE, CurrentHumidityCommands::CreateCommands);
    factory->RegisterCreator(TARGET_HUMIDITY_INTERFACE, TargetHumidityCommands::CreateCommands);
    factory->RegisterCreator(TARGET_TEMPERATURE_LEVEL_INTERFACE, TargetTemperatureLevelCommands::CreateCommands);
    factory->RegisterCreator(MOISTURE_OUTPUT_LEVEL_INTERFACE, MoistureOutputLevelCommands::CreateCommands);
    factory->RegisterCreator(FILTER_STATUS_INTERFACE, FilterStatusCommands::CreateCommands);
    factory->RegisterCreator(HVAC_FAN_MODE_INTERFACE, HvacFanModeCommands::CreateCommands);
    factory->RegisterCreator(PLUG_IN_UNITS_INTERFACE, PlugInUnitsCommands::CreateCommands);
    factory->RegisterCreator(RAPID_MODE_TIMED_INTERFACE, RapidModeTimedCommands::CreateCommands);
}

void DeviceEmulator::Startup()
{
    InitCommandsFactory();

    if (AllJoynInit() != ER_OK) {
        printf("FAILED to init alljoyn\n");
        exit(1);
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        printf("FAILED to init router\n");
        exit(1);
    }
#endif
    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());
    QCC_SetLogLevels("HAE_MODULE_LOG_NAME=15;");

    m_bus = new BusAttachment("DeviceEmulator", true);
    if (!m_bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    InterfaceList list;
    if (!m_configLoader.Load(m_aboutData, list)) {
        printf("Configuration load error\n");
        exit(1);
    }

    QStatus status = m_bus->Start();
    if (ER_OK != status) {
        printf("BusAttachment::Start failed (%s)\n", QCC_StatusText(status));
        exit(1);
    }

    status = m_bus->Connect();
    if (ER_OK != status) {
        printf("BusAttachment::Connect failed (%s)\n", QCC_StatusText(status));
        m_bus->Stop();
        m_bus->Join();
        exit(1);
    }

    m_virtualDevice = new VirtualDevice(m_bus, &m_aboutData, &list);
    if (m_virtualDevice) {
        m_virtualDevice->Startup();

        m_virtualDevice->Shutdown();
    } else {
        printf("Virtual Device creation failed.\n");
    }
}

void DeviceEmulator::Shutdown()
{
    if (m_bus) {
        m_bus->Disconnect();
        m_bus->Stop();
        m_bus->Join();
        delete m_bus;
        m_bus = NULL;
    }

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
}


