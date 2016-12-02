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
import org.alljoyn.cdmcontroller.view.method.MethodView;

public class EnergyUsageActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View cumulativeEnergyView = new ReadOnlyValuePropertyView(this, this.intf, "CumulativeEnergy", null);
        properties.addView(cumulativeEnergyView);

        View precisionView = new ReadOnlyValuePropertyView(this, this.intf, "Precision", null);
        properties.addView(precisionView);

        View updateMinTimeView = new ReadOnlyValuePropertyView(this, this.intf, "UpdateMinTime", null);
        properties.addView(updateMinTimeView);

        View resetCumulativeEnergyView = new MethodView(this, this.intf, "ResetCumulativeEnergy");
        methods.addView(resetCumulativeEnergyView);
    }
}