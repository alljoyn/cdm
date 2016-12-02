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
import org.alljoyn.cdmcontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.smartspaces.environment.CurrentAirQualityLevel;

public class CurrentAirQualityLevelActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View contaminantTypeView = new ReadOnlyEnumPropertyView(this, this.intf, "ContaminantType", CurrentAirQualityLevel.ContaminantType.class);
        properties.addView(contaminantTypeView);

        View currentLevelView = new ReadOnlyValuePropertyView(this, this.intf, "CurrentLevel", null);
        properties.addView(currentLevelView);

        View maxLevelView = new ReadOnlyValuePropertyView(this, this.intf, "MaxLevel", null);
        properties.addView(maxLevelView);
    }
}