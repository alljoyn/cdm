/******************************************************************************
 * 
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 * 
 *    SPDX-License-Identifier: Apache-2.0
 * 
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 * 
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 * 
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
using namespace std;

#include <alljoyn/cdm/controllee/CdmBusObject.h>

#include <interfaces/controllee/input/HidIntfControllee.h>
#include <interfaces/controllee/environment/CurrentAirQualityIntfControllee.h>
#include <interfaces/controllee/environment/CurrentAirQualityLevelIntfControllee.h>
#include <interfaces/controllee/environment/CurrentHumidityIntfControllee.h>
#include <interfaces/controllee/environment/CurrentTemperatureIntfControllee.h>
#include <interfaces/controllee/environment/TargetHumidityIntfControllee.h>
#include <interfaces/controllee/environment/TargetTemperatureIntfControllee.h>
#include <interfaces/controllee/environment/TargetTemperatureLevelIntfControllee.h>
#include <interfaces/controllee/environment/WaterLevelIntfControllee.h>
#include <interfaces/controllee/environment/WindDirectionIntfControllee.h>
#include <interfaces/controllee/operation/AirRecirculationModeIntfControllee.h>
#include <interfaces/controllee/operation/AlertsIntfControllee.h>
#include <interfaces/controllee/operation/AudioVideoInputIntfControllee.h>
#include <interfaces/controllee/operation/AudioVolumeIntfControllee.h>
#include <interfaces/controllee/operation/BatteryStatusIntfControllee.h>
#include <interfaces/controllee/operation/BrightnessIntfControllee.h>
#include <interfaces/controllee/operation/ChannelIntfControllee.h>
#include <interfaces/controllee/operation/ClimateControlModeIntfControllee.h>
#include <interfaces/controllee/operation/ClosedStatusIntfControllee.h>
#include <interfaces/controllee/operation/ColorIntfControllee.h>
#include <interfaces/controllee/operation/ColorTemperatureIntfControllee.h>
#include <interfaces/controllee/operation/CurrentPowerIntfControllee.h>
#include <interfaces/controllee/operation/CycleControlIntfControllee.h>
#include <interfaces/controllee/operation/DishWashingCyclePhaseIntfControllee.h>
#include <interfaces/controllee/operation/EnergyUsageIntfControllee.h>
#include <interfaces/controllee/operation/FanSpeedLevelIntfControllee.h>
#include <interfaces/controllee/operation/FilterStatusIntfControllee.h>
#include <interfaces/controllee/operation/HeatingZoneIntfControllee.h>
#include <interfaces/controllee/operation/HvacFanModeIntfControllee.h>
#include <interfaces/controllee/operation/LaundryCyclePhaseIntfControllee.h>
#include <interfaces/controllee/operation/LockControlIntfControllee.h>
#include <interfaces/controllee/operation/LockedStatusIntfControllee.h>
#include <interfaces/controllee/operation/MoistureOutputLevelIntfControllee.h>
#include <interfaces/controllee/operation/OffControlIntfControllee.h>
#include <interfaces/controllee/operation/OnControlIntfControllee.h>
#include <interfaces/controllee/operation/OnOffStatusIntfControllee.h>
#include <interfaces/controllee/operation/OvenCyclePhaseIntfControllee.h>
#include <interfaces/controllee/operation/PlugInUnitsIntfControllee.h>
#include <interfaces/controllee/operation/RapidModeIntfControllee.h>
#include <interfaces/controllee/operation/RapidModeTimedIntfControllee.h>
#include <interfaces/controllee/operation/RemoteControllabilityIntfControllee.h>
#include <interfaces/controllee/operation/RepeatModeIntfControllee.h>
#include <interfaces/controllee/operation/ResourceSavingIntfControllee.h>
#include <interfaces/controllee/operation/RobotCleaningCyclePhaseIntfControllee.h>
#include <interfaces/controllee/operation/SoilLevelIntfControllee.h>
#include <interfaces/controllee/operation/SpinSpeedLevelIntfControllee.h>
#include <interfaces/controllee/operation/TimerIntfControllee.h>
#include <interfaces/controllee/operation/TriggerSensorIntfControllee.h>
#include <interfaces/controllee/operation/UnlockControlIntfControllee.h>
#include <interfaces/controllee/userinterfacesettings/LanguageDisplayIntfControllee.h>
#include <interfaces/controllee/userinterfacesettings/TemperatureDisplayIntfControllee.h>
#include <interfaces/controllee/userinterfacesettings/TimeDisplayIntfControllee.h>

#include "Models/input/HidModel.h"
#include "Models/environment/CurrentAirQualityModel.h"
#include "Models/environment/CurrentAirQualityLevelModel.h"
#include "Models/environment/CurrentHumidityModel.h"
#include "Models/environment/CurrentTemperatureModel.h"
#include "Models/environment/TargetHumidityModel.h"
#include "Models/environment/TargetTemperatureModel.h"
#include "Models/environment/TargetTemperatureLevelModel.h"
#include "Models/environment/WaterLevelModel.h"
#include "Models/environment/WindDirectionModel.h"
#include "Models/operation/AirRecirculationModeModel.h"
#include "Models/operation/AlertsModel.h"
#include "Models/operation/AudioVideoInputModel.h"
#include "Models/operation/AudioVolumeModel.h"
#include "Models/operation/BatteryStatusModel.h"
#include "Models/operation/BrightnessModel.h"
#include "Models/operation/ChannelModel.h"
#include "Models/operation/ClimateControlModeModel.h"
#include "Models/operation/ClosedStatusModel.h"
#include "Models/operation/ColorModel.h"
#include "Models/operation/ColorTemperatureModel.h"
#include "Models/operation/CurrentPowerModel.h"
#include "Models/operation/CycleControlModel.h"
#include "Models/operation/DishWashingCyclePhaseModel.h"
#include "Models/operation/EnergyUsageModel.h"
#include "Models/operation/FanSpeedLevelModel.h"
#include "Models/operation/FilterStatusModel.h"
#include "Models/operation/HeatingZoneModel.h"
#include "Models/operation/HvacFanModeModel.h"
#include "Models/operation/LaundryCyclePhaseModel.h"
#include "Models/operation/LockControlModel.h"
#include "Models/operation/LockedStatusModel.h"
#include "Models/operation/MoistureOutputLevelModel.h"
#include "Models/operation/OffControlModel.h"
#include "Models/operation/OnControlModel.h"
#include "Models/operation/OnOffStatusModel.h"
#include "Models/operation/OvenCyclePhaseModel.h"
#include "Models/operation/PlugInUnitsModel.h"
#include "Models/operation/RapidModeModel.h"
#include "Models/operation/RapidModeTimedModel.h"
#include "Models/operation/RemoteControllabilityModel.h"
#include "Models/operation/RepeatModeModel.h"
#include "Models/operation/ResourceSavingModel.h"
#include "Models/operation/RobotCleaningCyclePhaseModel.h"
#include "Models/operation/SoilLevelModel.h"
#include "Models/operation/SpinSpeedLevelModel.h"
#include "Models/operation/TimerModel.h"
#include "Models/operation/TriggerSensorModel.h"
#include "Models/operation/UnlockControlModel.h"
#include "Models/userinterfacesettings/LanguageDisplayModel.h"
#include "Models/userinterfacesettings/TemperatureDisplayModel.h"
#include "Models/userinterfacesettings/TimeDisplayModel.h"

#include "SuperControllee.h"
#include "../Utils/HAL.h"

namespace ajn {
namespace services {
namespace emulator {
//======================================================================

SuperControllee::SuperControllee(
        BusAttachment& bus,
        const Config& config,
        const std::string& certPath
        )
  : m_announcer(bus),
    m_security(bus),
    m_controllee(bus),
    m_config(config)
{
    m_security.LoadFiles(certPath);
    m_announcer.SetAboutData(config.GetAboutData());
}



QStatus SuperControllee::Start(bool emitOnSet)
{
    return SetupDevice(emitOnSet);
}



QStatus SuperControllee::CreateInterfaces()
{
    QStatus status = ER_OK;
    const Config::ObjectVec& objects = m_config.GetObjects();

    for (const auto& obj : objects)
    {
        for (const auto& iface : obj.interfaces)
        {
            auto& name = iface.name;

            if (name == "org.alljoyn.Input.Hid")
            {
                status = mkInterface<HidIntfControllee, HidModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality")
            {
                status = mkInterface<CurrentAirQualityIntfControllee, CurrentAirQualityModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel")
            {
                status = mkInterface<CurrentAirQualityLevelIntfControllee, CurrentAirQualityLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.CurrentHumidity")
            {
                status = mkInterface<CurrentHumidityIntfControllee, CurrentHumidityModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.CurrentTemperature")
            {
                status = mkInterface<CurrentTemperatureIntfControllee, CurrentTemperatureModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.TargetHumidity")
            {
                status = mkInterface<TargetHumidityIntfControllee, TargetHumidityModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.TargetTemperature")
            {
                status = mkInterface<TargetTemperatureIntfControllee, TargetTemperatureModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel")
            {
                status = mkInterface<TargetTemperatureLevelIntfControllee, TargetTemperatureLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.WaterLevel")
            {
                status = mkInterface<WaterLevelIntfControllee, WaterLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Environment.WindDirection")
            {
                status = mkInterface<WindDirectionIntfControllee, WindDirectionModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode")
            {
                status = mkInterface<AirRecirculationModeIntfControllee, AirRecirculationModeModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.Alerts")
            {
                status = mkInterface<AlertsIntfControllee, AlertsModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.AudioVideoInput")
            {
                status = mkInterface<AudioVideoInputIntfControllee, AudioVideoInputModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.AudioVolume")
            {
                status = mkInterface<AudioVolumeIntfControllee, AudioVolumeModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.BatteryStatus")
            {
                status = mkInterface<BatteryStatusIntfControllee, BatteryStatusModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.Brightness")
            {
                status = mkInterface<BrightnessIntfControllee, BrightnessModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.Channel")
            {
                status = mkInterface<ChannelIntfControllee, ChannelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.ClimateControlMode")
            {
                status = mkInterface<ClimateControlModeIntfControllee, ClimateControlModeModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.ClosedStatus")
            {
                status = mkInterface<ClosedStatusIntfControllee, ClosedStatusModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.Color")
            {
                status = mkInterface<ColorIntfControllee, ColorModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.ColorTemperature")
            {
                status = mkInterface<ColorTemperatureIntfControllee, ColorTemperatureModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.CurrentPower")
            {
                status = mkInterface<CurrentPowerIntfControllee, CurrentPowerModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.CycleControl")
            {
                status = mkInterface<CycleControlIntfControllee, CycleControlModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase")
            {
                status = mkInterface<DishWashingCyclePhaseIntfControllee, DishWashingCyclePhaseModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.EnergyUsage")
            {
                status = mkInterface<EnergyUsageIntfControllee, EnergyUsageModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel")
            {
                status = mkInterface<FanSpeedLevelIntfControllee, FanSpeedLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.FilterStatus")
            {
                status = mkInterface<FilterStatusIntfControllee, FilterStatusModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.HeatingZone")
            {
                status = mkInterface<HeatingZoneIntfControllee, HeatingZoneModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.HvacFanMode")
            {
                status = mkInterface<HvacFanModeIntfControllee, HvacFanModeModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase")
            {
                status = mkInterface<LaundryCyclePhaseIntfControllee, LaundryCyclePhaseModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.LockControl")
            {
                status = mkInterface<LockControlIntfControllee, LockControlModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.LockedStatus")
            {
                status = mkInterface<LockedStatusIntfControllee, LockedStatusModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel")
            {
                status = mkInterface<MoistureOutputLevelIntfControllee, MoistureOutputLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.OffControl")
            {
                status = mkInterface<OffControlIntfControllee, OffControlModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.OnControl")
            {
                status = mkInterface<OnControlIntfControllee, OnControlModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.OnOffStatus")
            {
                status = mkInterface<OnOffStatusIntfControllee, OnOffStatusModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase")
            {
                status = mkInterface<OvenCyclePhaseIntfControllee, OvenCyclePhaseModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.PlugInUnits")
            {
                status = mkInterface<PlugInUnitsIntfControllee, PlugInUnitsModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.RapidMode")
            {
                status = mkInterface<RapidModeIntfControllee, RapidModeModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.RapidModeTimed")
            {
                status = mkInterface<RapidModeTimedIntfControllee, RapidModeTimedModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.RemoteControllability")
            {
                status = mkInterface<RemoteControllabilityIntfControllee, RemoteControllabilityModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.RepeatMode")
            {
                status = mkInterface<RepeatModeIntfControllee, RepeatModeModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.ResourceSaving")
            {
                status = mkInterface<ResourceSavingIntfControllee, ResourceSavingModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase")
            {
                status = mkInterface<RobotCleaningCyclePhaseIntfControllee, RobotCleaningCyclePhaseModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.SoilLevel")
            {
                status = mkInterface<SoilLevelIntfControllee, SoilLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel")
            {
                status = mkInterface<SpinSpeedLevelIntfControllee, SpinSpeedLevelModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.Timer")
            {
                status = mkInterface<TimerIntfControllee, TimerModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.TriggerSensor")
            {
                status = mkInterface<TriggerSensorIntfControllee, TriggerSensorModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.Operation.UnlockControl")
            {
                status = mkInterface<UnlockControlIntfControllee, UnlockControlModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay")
            {
                status = mkInterface<LanguageDisplayIntfControllee, LanguageDisplayModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay")
            {
                status = mkInterface<TemperatureDisplayIntfControllee, TemperatureDisplayModel>(obj.path);
            }
            else
            if (name == "org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay")
            {
                status = mkInterface<TimeDisplayIntfControllee, TimeDisplayModel>(obj.path);
            }
            else
            {
                cerr << "Skipping unrecognised interface name " << name << "\n";
                status = ER_OK;
            }

            if (status != ER_OK)
            {
                return status;
            }
        }
    }

    return status;
}



QStatus SuperControllee::PreloadHAL()
{
    auto& objects = m_config.GetObjects();

    for (auto& obj : objects)
    {
        for (auto& iface : obj.interfaces)
        {
            for (auto& prop : iface.properties)
            {
                if (!prop.initialState.empty())
                {
                    bool force = (prop.mode == Config::PropMode::Initialize);
                    HAL::X::instance().WritePropertyXml(obj.path, iface.name, prop.name, prop.initialState, force);
                }
            }
        }
    }

    return ER_OK;
}



QStatus SuperControllee::SetupDevice(bool emitOnSet)
{
    QStatus status = PreloadHAL();
    if (status != ER_OK)
    {
        return status;
    }

    status = CreateInterfaces();
    if (status != ER_OK)
    {
        return status;
    }

    status = m_security.Enable();
    if (status != ER_OK)
    {
        return status;
    }

    status = m_controllee.Start(emitOnSet);
    if (status != ER_OK)
    {
        return status;
    }

    return m_announcer.Announce();
}



QStatus SuperControllee::Stop()
{
    m_announcer.Unannounce();

    return m_controllee.Stop();
}



QStatus HandleCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_OK;

    if (cmd.name == "changed")
    {
        if (cmd.interface == "org.alljoyn.Input.Hid")
        {
            status = HandleHidCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality")
        {
            status = HandleCurrentAirQualityCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel")
        {
            status = HandleCurrentAirQualityLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.CurrentHumidity")
        {
            status = HandleCurrentHumidityCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.CurrentTemperature")
        {
            status = HandleCurrentTemperatureCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.TargetHumidity")
        {
            status = HandleTargetHumidityCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.TargetTemperature")
        {
            status = HandleTargetTemperatureCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel")
        {
            status = HandleTargetTemperatureLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.WaterLevel")
        {
            status = HandleWaterLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Environment.WindDirection")
        {
            status = HandleWindDirectionCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode")
        {
            status = HandleAirRecirculationModeCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.Alerts")
        {
            status = HandleAlertsCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.AudioVideoInput")
        {
            status = HandleAudioVideoInputCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.AudioVolume")
        {
            status = HandleAudioVolumeCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.BatteryStatus")
        {
            status = HandleBatteryStatusCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.Brightness")
        {
            status = HandleBrightnessCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.Channel")
        {
            status = HandleChannelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.ClimateControlMode")
        {
            status = HandleClimateControlModeCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.ClosedStatus")
        {
            status = HandleClosedStatusCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.Color")
        {
            status = HandleColorCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.ColorTemperature")
        {
            status = HandleColorTemperatureCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.CurrentPower")
        {
            status = HandleCurrentPowerCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.CycleControl")
        {
            status = HandleCycleControlCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase")
        {
            status = HandleDishWashingCyclePhaseCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.EnergyUsage")
        {
            status = HandleEnergyUsageCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel")
        {
            status = HandleFanSpeedLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.FilterStatus")
        {
            status = HandleFilterStatusCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.HeatingZone")
        {
            status = HandleHeatingZoneCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.HvacFanMode")
        {
            status = HandleHvacFanModeCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase")
        {
            status = HandleLaundryCyclePhaseCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.LockControl")
        {
            status = HandleLockControlCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.LockedStatus")
        {
            status = HandleLockedStatusCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel")
        {
            status = HandleMoistureOutputLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.OffControl")
        {
            status = HandleOffControlCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.OnControl")
        {
            status = HandleOnControlCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.OnOffStatus")
        {
            status = HandleOnOffStatusCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase")
        {
            status = HandleOvenCyclePhaseCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.PlugInUnits")
        {
            status = HandlePlugInUnitsCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.RapidMode")
        {
            status = HandleRapidModeCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.RapidModeTimed")
        {
            status = HandleRapidModeTimedCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.RemoteControllability")
        {
            status = HandleRemoteControllabilityCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.RepeatMode")
        {
            status = HandleRepeatModeCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.ResourceSaving")
        {
            status = HandleResourceSavingCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase")
        {
            status = HandleRobotCleaningCyclePhaseCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.SoilLevel")
        {
            status = HandleSoilLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel")
        {
            status = HandleSpinSpeedLevelCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.Timer")
        {
            status = HandleTimerCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.TriggerSensor")
        {
            status = HandleTriggerSensorCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.Operation.UnlockControl")
        {
            status = HandleUnlockControlCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay")
        {
            status = HandleLanguageDisplayCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay")
        {
            status = HandleTemperatureDisplayCommand(cmd, controllee);
        }
        else
        if (cmd.interface == "org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay")
        {
            status = HandleTimeDisplayCommand(cmd, controllee);
        }
        else
        {
            status = ER_FAIL;
        }
    }

    return status;
}

//======================================================================
}}}
