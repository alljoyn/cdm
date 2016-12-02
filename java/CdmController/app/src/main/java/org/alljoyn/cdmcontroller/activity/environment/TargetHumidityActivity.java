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
import org.alljoyn.cdmcontroller.view.property.MinMaxPropertyView;
import org.alljoyn.cdmcontroller.view.property.SupportedValuesPropertyView;
import org.alljoyn.smartspaces.environment.TargetHumidity;

public class TargetHumidityActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        TargetHumidity targetHumidity = (TargetHumidity)this.intf;

        byte maxValue = targetHumidity.getMaxValue();
        byte minValue = targetHumidity.getMinValue();

        if (minValue==maxValue) {
            View targetValueView = new SupportedValuesPropertyView(this, this.intf, "TargetValue", "%", "SelectableHumidityLevels");
            properties.addView(targetValueView);
        } else {
            View targetValueView = new MinMaxPropertyView(this, this.intf, "TargetValue", "%", "MinValue", "MaxValue", "StepValue");
            properties.addView(targetValueView);
        }
    }
}