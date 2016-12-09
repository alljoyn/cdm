/******************************************************************************
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

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmInterface.h>

namespace ajn {
namespace services {

std::map<CdmInterfaceType, qcc::String> InterfaceTypesMap = {
    {HID_INTERFACE, "org.alljoyn.Input.Hid"},
    {CURRENT_AIR_QUALITY_INTERFACE, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality"},
    {CURRENT_AIR_QUALITY_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel"},
    {CURRENT_HUMIDITY_INTERFACE, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity"},
    {CURRENT_TEMPERATURE_INTERFACE, "org.alljoyn.SmartSpaces.Environment.CurrentTemperature"},
    {TARGET_HUMIDITY_INTERFACE, "org.alljoyn.SmartSpaces.Environment.TargetHumidity"},
    {TARGET_TEMPERATURE_INTERFACE, "org.alljoyn.SmartSpaces.Environment.TargetTemperature"},
    {TARGET_TEMPERATURE_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel"},
    {WATER_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Environment.WaterLevel"},
    {WIND_DIRECTION_INTERFACE, "org.alljoyn.SmartSpaces.Environment.WindDirection"},
    {AIR_RECIRCULATION_MODE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode"},
    {ALERTS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Alerts"},
    {AUDIO_VIDEO_INPUT_INTERFACE, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput"},
    {AUDIO_VOLUME_INTERFACE, "org.alljoyn.SmartSpaces.Operation.AudioVolume"},
    {BATTERY_STATUS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.BatteryStatus"},
    {BRIGHTNESS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Brightness"},
    {CHANNEL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Channel"},
    {CLIMATE_CONTROL_MODE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode"},
    {CLOSED_STATUS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.ClosedStatus"},
    {COLOR_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Color"},
    {COLOR_TEMPERATURE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.ColorTemperature"},
    {CURRENT_POWER_INTERFACE, "org.alljoyn.SmartSpaces.Operation.CurrentPower"},
    {CYCLE_CONTROL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.CycleControl"},
    {DISH_WASHING_CYCLE_PHASE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase"},
    {ENERGY_USAGE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.EnergyUsage"},
    {FAN_SPEED_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel"},
    {FILTER_STATUS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.FilterStatus"},
    {HEATING_ZONE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.HeatingZone"},
    {HVAC_FAN_MODE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.HvacFanMode"},
    {LAUNDRY_CYCLE_PHASE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase"},
    {MOISTURE_OUTPUT_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel"},
    {ON_OFF_STATUS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
    {OFF_CONTROL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.OffControl"},
    {ON_CONTROL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.OnControl"},
    {OVEN_CYCLE_PHASE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase"},
    {PLUG_IN_UNITS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.PlugInUnits"},
    {RAPID_MODE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.RapidMode"},
    {RAPID_MODE_TIMED_INTERFACE, "org.alljoyn.SmartSpaces.Operation.RapidModeTimed"},
    {REMOTE_CONTROLLABILITY_INTERFACE, "org.alljoyn.SmartSpaces.Operation.RemoteControllability"},
    {REPEAT_MODE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.RepeatMode"},
    {RESOURCE_SAVING_INTERFACE, "org.alljoyn.SmartSpaces.Operation.ResourceSaving"},
    {ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase"},
    {SOIL_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.SoilLevel"},
    {SPIN_SPEED_LEVEL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel"},
    {TIMER_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Timer"},
    {LANGUAGE_DISPLAY_INTERFACE, "org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay"},
    {TEMPERATURE_DISPLAY_INTERFACE, "org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay"},
    {TIME_DISPLAY_INTERFACE, "org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay"},
    {BRIGHTNESS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Brightness"},
    {COLOR_INTERFACE, "org.alljoyn.SmartSpaces.Operation.Color"},
    {COLOR_TEMPERATURE_INTERFACE, "org.alljoyn.SmartSpaces.Operation.ColorTemperature"},
    {LOCK_CONTROL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.LockControl"},
    {LOCKED_STATUS_INTERFACE, "org.alljoyn.SmartSpaces.Operation.LockedStatus"},
    {TRIGGER_SENSOR_INTERFACE, "org.alljoyn.SmartSpaces.Operation.TriggerSensor"},
    {UNLOCK_CONTROL_INTERFACE, "org.alljoyn.SmartSpaces.Operation.UnlockControl"}
};

std::map<ErrorCode, qcc::String> CdmInterface::InterfaceErrorNameMap = {
    {INVALID_VALUE, "org.alljoyn.Error.InvalidValue"},
    {FEATURE_NOT_AVAILABLE, "org.alljoyn.Error.FeatureNotAvailable"},
    {LANGUAGE_NOT_SUPPORTED, "org.alljoyn.Error.LanguageNotSupported"},
    {NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE, "org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState"},
    {REMOTE_CONTROL_DISABLED, "org.alljoyn.SmartSpaces.Error.RemoteControlDisabled"},
};

std::map<ErrorCode, qcc::String> CdmInterface::InterfaceErrorMessageMap = {
    {INVALID_VALUE, "Invalid value"},
    {FEATURE_NOT_AVAILABLE, "Feature not available"},
    {LANGUAGE_NOT_SUPPORTED, "The language specified is not supported."},
    {NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE, "The value is not acceptable due to internal state."},
    {REMOTE_CONTROL_DISABLED, "Remote control disabled"},
};

QStatus CdmInterface::Init()
{
    QStatus status = ER_OK;

    BusAttachment& busAttachment = GetBusAttachment();

    status = busAttachment.CreateInterfacesFromXml(GetIntrospectionXml().c_str());
    if (status != ER_OK && status != ER_BUS_IFACE_ALREADY_EXISTS) {
        QCC_LogError(status, ("%s: failed to initialize.", __func__));
        return status;
    }
    m_interfaceDescription = busAttachment.GetInterface(GetInterfaceName().c_str());
    if (!m_interfaceDescription) {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: failed to get interface description.", __func__));
        return status;
    }

    return status;
}

} //namespace services
} //namespace ajn