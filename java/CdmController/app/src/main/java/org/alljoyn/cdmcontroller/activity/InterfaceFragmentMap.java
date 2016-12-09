/*
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
 */

package org.alljoyn.cdmcontroller.activity;

import android.support.v4.app.Fragment;

import org.alljoyn.cdmcontroller.fragment.environment.CurrentAirQualityFragment;
import org.alljoyn.cdmcontroller.fragment.environment.CurrentAirQualityLevelFragment;
import org.alljoyn.cdmcontroller.fragment.environment.CurrentHumidityFragment;
import org.alljoyn.cdmcontroller.fragment.environment.CurrentTemperatureFragment;
import org.alljoyn.cdmcontroller.fragment.environment.TargetHumidityFragment;
import org.alljoyn.cdmcontroller.fragment.environment.TargetTemperatureFragment;
import org.alljoyn.cdmcontroller.fragment.environment.TargetTemperatureLevelFragment;
import org.alljoyn.cdmcontroller.fragment.environment.WindDirectionFragment;
import org.alljoyn.cdmcontroller.fragment.operation.AirRecirculationModeFragment;
import org.alljoyn.cdmcontroller.fragment.operation.AlertsFragment;
import org.alljoyn.cdmcontroller.fragment.operation.AudioVideoInputFragment;
import org.alljoyn.cdmcontroller.fragment.operation.AudioVolumeFragment;
import org.alljoyn.cdmcontroller.fragment.operation.BatteryStatusFragment;
import org.alljoyn.cdmcontroller.fragment.operation.BrightnessFragment;
import org.alljoyn.cdmcontroller.fragment.operation.ChannelFragment;
import org.alljoyn.cdmcontroller.fragment.operation.ClimateControlModeFragment;
import org.alljoyn.cdmcontroller.fragment.operation.ColorFragment;
import org.alljoyn.cdmcontroller.fragment.operation.ColorTemperatureFragment;
import org.alljoyn.cdmcontroller.fragment.operation.CurrentPowerFragment;
import org.alljoyn.cdmcontroller.fragment.operation.CycleControlFragment;
import org.alljoyn.cdmcontroller.fragment.operation.DishWashingCyclePhaseFragment;
import org.alljoyn.cdmcontroller.fragment.operation.EnergyUsageFragment;
import org.alljoyn.cdmcontroller.fragment.operation.FanSpeedLevelFragment;
import org.alljoyn.cdmcontroller.fragment.operation.FilterStatusFragment;
import org.alljoyn.cdmcontroller.fragment.operation.HvacFanModeFragment;
import org.alljoyn.cdmcontroller.fragment.operation.LaundryCyclePhaseFragment;
import org.alljoyn.cdmcontroller.fragment.operation.LockControlFragment;
import org.alljoyn.cdmcontroller.fragment.operation.LockedStatusFragment;
import org.alljoyn.cdmcontroller.fragment.operation.MoistureOutputLevelFragment;
import org.alljoyn.cdmcontroller.fragment.operation.HeatingZoneFragment;
import org.alljoyn.cdmcontroller.fragment.operation.OffControlFragment;
import org.alljoyn.cdmcontroller.fragment.operation.OnControlFragment;
import org.alljoyn.cdmcontroller.fragment.operation.OnOffStatusFragment;
import org.alljoyn.cdmcontroller.fragment.operation.OvenCyclePhaseFragment;
import org.alljoyn.cdmcontroller.fragment.operation.PlugInUnitsFragment;
import org.alljoyn.cdmcontroller.fragment.operation.RapidModeTimedFragment;
import org.alljoyn.cdmcontroller.fragment.operation.RepeatModeFragment;
import org.alljoyn.cdmcontroller.fragment.operation.ResourceSavingFragment;
import org.alljoyn.cdmcontroller.fragment.operation.ClosedStatusFragment;
import org.alljoyn.cdmcontroller.fragment.operation.RemoteControllabilityFragment;
import org.alljoyn.cdmcontroller.fragment.operation.RapidModeFragment;
import org.alljoyn.cdmcontroller.fragment.environment.WaterLevelFragment;
import org.alljoyn.cdmcontroller.fragment.operation.RobotCleaningCyclePhaseFragment;
import org.alljoyn.cdmcontroller.fragment.operation.SoilLevelFragment;
import org.alljoyn.cdmcontroller.fragment.operation.SpinSpeedLevelFragment;
import org.alljoyn.cdmcontroller.fragment.operation.TimerFragment;
import org.alljoyn.cdmcontroller.fragment.operation.TriggerSensorFragment;
import org.alljoyn.cdmcontroller.fragment.operation.UnlockControlFragment;
import org.alljoyn.cdmcontroller.fragment.userinterfacesettings.LanguageDisplayFragment;
import org.alljoyn.cdmcontroller.fragment.userinterfacesettings.TemperatureDisplayFragment;
import org.alljoyn.cdmcontroller.fragment.userinterfacesettings.TimeDisplayFragment;

import java.util.HashMap;
import java.util.Map;

public class InterfaceFragmentMap {
    public static final Map<String, Class<? extends Fragment>> fragmentMap = new HashMap<String, Class<? extends Fragment>>() {{
//        put("org.alljoyn.Input.Hid", HidFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentTemperature", CurrentTemperatureFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetTemperature", TargetTemperatureFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.WindDirection", WindDirectionFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", CurrentAirQualityFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel", CurrentAirQualityLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentHumidity", CurrentHumidityFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetHumidity", TargetHumidityFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel", TargetTemperatureLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.AirRecirculationMode", AirRecirculationModeFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.Alerts", AlertsFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.AudioVideoInput", AudioVideoInputFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.AudioVolume", AudioVolumeFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.BatteryStatus", BatteryStatusFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.Brightness", BrightnessFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.Channel", ChannelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.ClimateControlMode", ClimateControlModeFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.ClosedStatus", ClosedStatusFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.Color", ColorFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.ColorTemperature", ColorTemperatureFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.CurrentPower", CurrentPowerFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.EnergyUsage", EnergyUsageFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", FanSpeedLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.FilterStatus", FilterStatusFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.LockControl", LockControlFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.LockedStatus", LockedStatusFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", MoistureOutputLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.OnControl", OnControlFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.OffControl", OffControlFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.OnOffStatus", OnOffStatusFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.RapidModeTimed", RapidModeTimedFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.RepeatMode", RepeatModeFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.ResourceSaving", ResourceSavingFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase", RobotCleaningCyclePhaseFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.HvacFanMode", HvacFanModeFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.PlugInUnits", PlugInUnitsFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.ClosedStatus", ClosedStatusFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.RemoteControllability", RemoteControllabilityFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.RapidMode", RapidModeFragment.class);
        put("org.alljoyn.SmartSpaces.Environment.WaterLevel", WaterLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.CycleControl", CycleControlFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.HeatingZone", HeatingZoneFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.SoilLevel", SoilLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel", SpinSpeedLevelFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.Timer", TimerFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.TriggerSensor", TriggerSensorFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.UnlockControl", UnlockControlFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", DishWashingCyclePhaseFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase", LaundryCyclePhaseFragment.class);
        put("org.alljoyn.SmartSpaces.Operation.OvenCyclePhase", OvenCyclePhaseFragment.class);
        put("org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay", LanguageDisplayFragment.class);
        put("org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay", TemperatureDisplayFragment.class);
        put("org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay", TimeDisplayFragment.class);
    }};
}