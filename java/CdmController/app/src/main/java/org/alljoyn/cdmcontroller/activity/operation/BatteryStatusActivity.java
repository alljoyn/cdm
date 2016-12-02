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

package org.alljoyn.cdmcontroller.activity.operation;

import android.view.View;

import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;

public class BatteryStatusActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View volumeView = new ReadOnlyValuePropertyView(this, this.intf, "CurrentValue", null);
        properties.addView(volumeView);

        View isChargingView = new ReadOnlyValuePropertyView(this, this.intf, "IsCharging", null);
        properties.addView(isChargingView);
    }
}