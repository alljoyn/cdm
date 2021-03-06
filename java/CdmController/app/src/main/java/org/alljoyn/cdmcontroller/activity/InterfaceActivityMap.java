/*
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
 */

package org.alljoyn.cdmcontroller.activity;

import android.app.Activity;

import org.alljoyn.cdmcontroller.activity.environment.CurrentAirQualityActivity;
import org.alljoyn.cdmcontroller.activity.environment.CurrentAirQualityLevelActivity;
import org.alljoyn.cdmcontroller.activity.environment.CurrentHumidityActivity;
import org.alljoyn.cdmcontroller.activity.environment.CurrentTemperatureActivity;
import org.alljoyn.cdmcontroller.activity.environment.TargetHumidityActivity;
import org.alljoyn.cdmcontroller.activity.environment.TargetTemperatureActivity;
import org.alljoyn.cdmcontroller.activity.environment.TargetTemperatureLevelActivity;
import org.alljoyn.cdmcontroller.activity.environment.WindDirectionActivity;
import org.alljoyn.cdmcontroller.activity.input.HidActivity;
import org.alljoyn.cdmcontroller.activity.operation.AirRecirculationModeActivity;
import org.alljoyn.cdmcontroller.activity.operation.AudioVideoInputActivity;
import org.alljoyn.cdmcontroller.activity.operation.AudioVolumeActivity;
import org.alljoyn.cdmcontroller.activity.operation.BatteryStatusActivity;
import org.alljoyn.cdmcontroller.activity.operation.ChannelActivity;
import org.alljoyn.cdmcontroller.activity.operation.ClimateControlModeActivity;
import org.alljoyn.cdmcontroller.activity.operation.CurrentPowerActivity;
import org.alljoyn.cdmcontroller.activity.operation.CycleControlActivity;
import org.alljoyn.cdmcontroller.activity.operation.CyclePhaseActivity;
import org.alljoyn.cdmcontroller.activity.operation.EnergyUsageActivity;
import org.alljoyn.cdmcontroller.activity.operation.FanSpeedLevelActivity;
import org.alljoyn.cdmcontroller.activity.operation.FilterStatusActivity;
import org.alljoyn.cdmcontroller.activity.operation.HvacFanModeActivity;
import org.alljoyn.cdmcontroller.activity.operation.MoistureOutputLevelActivity;
import org.alljoyn.cdmcontroller.activity.operation.HeatingZoneActivity;
import org.alljoyn.cdmcontroller.activity.operation.OffControlActivity;
import org.alljoyn.cdmcontroller.activity.operation.OnControlActivity;
import org.alljoyn.cdmcontroller.activity.operation.OnOffStatusActivity;
import org.alljoyn.cdmcontroller.activity.operation.PlugInUnitsActivity;
import org.alljoyn.cdmcontroller.activity.operation.RapidModeTimedActivity;
import org.alljoyn.cdmcontroller.activity.operation.RepeatModeActivity;
import org.alljoyn.cdmcontroller.activity.operation.ResourceSavingActivity;
import org.alljoyn.cdmcontroller.activity.operation.ClosedStatusActivity;
import org.alljoyn.cdmcontroller.activity.operation.RemoteControllabilityActivity;
import org.alljoyn.cdmcontroller.activity.operation.RapidModeActivity;
import org.alljoyn.cdmcontroller.activity.environment.WaterLevelActivity;
import org.alljoyn.cdmcontroller.activity.operation.SoilLevelActivity;
import org.alljoyn.cdmcontroller.activity.operation.SpinSpeedLevelActivity;
import org.alljoyn.cdmcontroller.activity.operation.TimerActivity;
import org.alljoyn.cdmcontroller.activity.userinterfacesettings.LanguageDisplayActivity;
import org.alljoyn.cdmcontroller.activity.userinterfacesettings.TemperatureDisplayActivity;
import org.alljoyn.cdmcontroller.activity.userinterfacesettings.TimeDisplayActivity;

import java.util.HashMap;
import java.util.Map;

public class InterfaceActivityMap {
    public static final Map<String, Class<? extends Activity>> activityMap = new HashMap<String, Class<? extends Activity>>() {{
        put("org.alljoyn.Input.Hid", HidActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentTemperature", CurrentTemperatureActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetTemperature", TargetTemperatureActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.WindDirection", WindDirectionActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", CurrentAirQualityActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel", CurrentAirQualityLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentHumidity", CurrentHumidityActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetHumidity", TargetHumidityActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel", TargetTemperatureLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.AirRecirculationMode", AirRecirculationModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.AudioVideoInput", AudioVideoInputActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.AudioVolume", AudioVolumeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.BatteryStatus", BatteryStatusActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.Channel", ChannelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.ClimateControlMode", ClimateControlModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.CurrentPower", CurrentPowerActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.EnergyUsage", EnergyUsageActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", FanSpeedLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.FilterStatus", FilterStatusActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", MoistureOutputLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OnControl", OnControlActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OffControl", OffControlActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OnOffStatus", OnOffStatusActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RapidModeTimed", RapidModeTimedActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RepeatMode", RepeatModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.ResourceSaving", ResourceSavingActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase", CyclePhaseActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.HvacFanMode", HvacFanModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.PlugInUnits", PlugInUnitsActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.ClosedStatus", ClosedStatusActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RemoteControllability", RemoteControllabilityActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RapidMode", RapidModeActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.WaterLevel", WaterLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.CycleControl", CycleControlActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.HeatingZone", HeatingZoneActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.SoilLevel", SoilLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel", SpinSpeedLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.Timer", TimerActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", CyclePhaseActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase", CyclePhaseActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OvenCyclePhase", CyclePhaseActivity.class);
        put("org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay", LanguageDisplayActivity.class);
        put("org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay", TemperatureDisplayActivity.class);
        put("org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay", TimeDisplayActivity.class);
    }};
}