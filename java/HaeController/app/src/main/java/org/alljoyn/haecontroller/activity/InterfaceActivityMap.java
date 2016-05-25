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

import org.alljoyn.haecontroller.activity.environment.CurrentTemperatureActivity;
import org.alljoyn.haecontroller.activity.environment.TargetTemperatureActivity;
import org.alljoyn.haecontroller.activity.environment.WindDirectionActivity;
import org.alljoyn.haecontroller.activity.input.HidActivity;
import org.alljoyn.haecontroller.activity.operation.AirRecirculationModeActivity;
import org.alljoyn.haecontroller.activity.operation.AudioVideoInputActivity;
import org.alljoyn.haecontroller.activity.operation.AudioVolumeActivity;
import org.alljoyn.haecontroller.activity.operation.BatteryStatusActivity;
import org.alljoyn.haecontroller.activity.operation.ChannelActivity;
import org.alljoyn.haecontroller.activity.operation.ClimateControlModeActivity;
import org.alljoyn.haecontroller.activity.operation.CurrentPowerActivity;
import org.alljoyn.haecontroller.activity.operation.CyclePhaseActivity;
import org.alljoyn.haecontroller.activity.operation.EnergyUsageActivity;
import org.alljoyn.haecontroller.activity.operation.FanSpeedLevelActivity;
import org.alljoyn.haecontroller.activity.operation.OffControlActivity;
import org.alljoyn.haecontroller.activity.operation.OnControlActivity;
import org.alljoyn.haecontroller.activity.operation.OnOffStatusActivity;
import org.alljoyn.haecontroller.activity.operation.RepeatModeActivity;
import org.alljoyn.haecontroller.activity.operation.ResourceSavingActivity;

import java.util.HashMap;
import java.util.Map;

public class InterfaceActivityMap {
    public static final Map<String, Class<? extends Activity>> activityMap = new HashMap<String, Class<? extends Activity>>() {{
        put("org.alljoyn.Input.Hid", HidActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.CurrentTemperature", CurrentTemperatureActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.TargetTemperature", TargetTemperatureActivity.class);
        put("org.alljoyn.SmartSpaces.Environment.WindDirection", WindDirectionActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.AirRecirculationMode", AirRecirculationModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.AudioVideoInput", AudioVideoInputActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.AudioVolume", AudioVolumeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.BatteryStatus", BatteryStatusActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.Channel", ChannelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.ClimateControlMode", ClimateControlModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.CurrentPower", CurrentPowerActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.EnergyUsage", EnergyUsageActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", FanSpeedLevelActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OnControl", OnControlActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OffControl", OffControlActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.OnOffStatus", OnOffStatusActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RepeatMode", RepeatModeActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.ResourceSaving", ResourceSavingActivity.class);
        put("org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase", CyclePhaseActivity.class);
    }};
}
