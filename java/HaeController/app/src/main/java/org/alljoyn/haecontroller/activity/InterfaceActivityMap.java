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

package org.alljoyn.haecontroller.activity;

import android.app.Activity;

import org.alljoyn.haecontroller.activity.environment.CurrentAirQualityActivity;
import org.alljoyn.haecontroller.activity.environment.CurrentAirQualityLevelActivity;
import org.alljoyn.haecontroller.activity.environment.CurrentHumidityActivity;
import org.alljoyn.haecontroller.activity.environment.CurrentTemperatureActivity;
import org.alljoyn.haecontroller.activity.environment.TargetHumidityActivity;
import org.alljoyn.haecontroller.activity.environment.TargetTemperatureActivity;
import org.alljoyn.haecontroller.activity.environment.TargetTemperatureLevelActivity;
import org.alljoyn.haecontroller.activity.environment.WindDirectionActivity;
import org.alljoyn.haecontroller.activity.input.HidActivity;
import org.alljoyn.haecontroller.activity.operation.AirRecirculationModeActivity;
import org.alljoyn.haecontroller.activity.operation.AudioVideoInputActivity;
import org.alljoyn.haecontroller.activity.operation.AudioVolumeActivity;
import org.alljoyn.haecontroller.activity.operation.BatteryStatusActivity;
import org.alljoyn.haecontroller.activity.operation.ChannelActivity;
import org.alljoyn.haecontroller.activity.operation.ClimateControlModeActivity;
import org.alljoyn.haecontroller.activity.operation.CurrentPowerActivity;
import org.alljoyn.haecontroller.activity.operation.CycleControlActivity;
import org.alljoyn.haecontroller.activity.operation.CyclePhaseActivity;
import org.alljoyn.haecontroller.activity.operation.EnergyUsageActivity;
import org.alljoyn.haecontroller.activity.operation.FanSpeedLevelActivity;
import org.alljoyn.haecontroller.activity.operation.FilterStatusActivity;
import org.alljoyn.haecontroller.activity.operation.HvacFanModeActivity;
import org.alljoyn.haecontroller.activity.operation.MoistureOutputLevelActivity;
import org.alljoyn.haecontroller.activity.operation.HeatingZoneActivity;
import org.alljoyn.haecontroller.activity.operation.OffControlActivity;
import org.alljoyn.haecontroller.activity.operation.OnControlActivity;
import org.alljoyn.haecontroller.activity.operation.OnOffStatusActivity;
import org.alljoyn.haecontroller.activity.operation.PlugInUnitsActivity;
import org.alljoyn.haecontroller.activity.operation.RapidModeTimedActivity;
import org.alljoyn.haecontroller.activity.operation.RepeatModeActivity;
import org.alljoyn.haecontroller.activity.operation.ResourceSavingActivity;
import org.alljoyn.haecontroller.activity.operation.ClosedStatusActivity;
import org.alljoyn.haecontroller.activity.operation.RemoteControllabilityActivity;
import org.alljoyn.haecontroller.activity.operation.RapidModeActivity;
import org.alljoyn.haecontroller.activity.environment.WaterLevelActivity;
import org.alljoyn.haecontroller.activity.operation.SoilLevelActivity;
import org.alljoyn.haecontroller.activity.operation.SpinSpeedLevelActivity;
import org.alljoyn.haecontroller.activity.operation.TimerActivity;
import org.alljoyn.haecontroller.activity.userinterfacesettings.LanguageDisplayActivity;
import org.alljoyn.haecontroller.activity.userinterfacesettings.TemperatureDisplayActivity;
import org.alljoyn.haecontroller.activity.userinterfacesettings.TimeDisplayActivity;

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