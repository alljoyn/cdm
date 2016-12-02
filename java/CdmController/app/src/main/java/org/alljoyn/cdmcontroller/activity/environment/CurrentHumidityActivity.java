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

package org.alljoyn.cdmcontroller.activity.environment;

import android.view.View;

import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;

public class CurrentHumidityActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View currentPowerView = new ReadOnlyValuePropertyView(this, this.intf, "CurrentValue", "%");
        properties.addView(currentPowerView);

        View maxValueView = new ReadOnlyValuePropertyView(this, this.intf, "MaxValue", "%");
        properties.addView(maxValueView);
    }
}
