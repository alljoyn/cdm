/*
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 */

package org.alljoyn.cdmcontroller.activity.userinterfacesettings;

import android.view.View;

import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.property.SupportedEnumPropertyView;
import org.alljoyn.smartspaces.userinterfacesettings.TemperatureDisplay;

public class TemperatureDisplayActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View temperatureView = new SupportedEnumPropertyView(this, this.intf, "DisplayTemperatureUnit", "SupportedDisplayTemperatureUnits", TemperatureDisplay.DisplayTemperatureUnit.class);
        properties.addView(temperatureView);
    }
}