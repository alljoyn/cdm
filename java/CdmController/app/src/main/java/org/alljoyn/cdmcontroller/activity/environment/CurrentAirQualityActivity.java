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
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.smartspaces.environment.CurrentAirQuality;

public class CurrentAirQualityActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {

        CurrentAirQuality intf = (CurrentAirQuality)this.intf;

        CurrentAirQuality.ContaminantType type = (CurrentAirQuality.ContaminantType)CdmUtil.findEnum(intf.getContaminantType(), CurrentAirQuality.ContaminantType.class);

        View contaminantTypeView = new ReadOnlyEnumPropertyView(this, this.intf, "ContaminantType", CurrentAirQuality.ContaminantType.class);
        properties.addView(contaminantTypeView);

        View currentValueView = new ReadOnlyValuePropertyView(this, this.intf, "CurrentValue", type.getUnit());
        properties.addView(currentValueView);

        View maxValueView = new ReadOnlyValuePropertyView(this, this.intf, "MaxValue", type.getUnit());
        properties.addView(maxValueView);

        View minValueView = new ReadOnlyValuePropertyView(this, this.intf, "MinValue", type.getUnit());
        properties.addView(minValueView);

        View precisionView = new ReadOnlyValuePropertyView(this, this.intf, "Precision", type.getUnit());
        properties.addView(precisionView);

        View updateMinTimeView = new ReadOnlyValuePropertyView(this, this.intf, "UpdateMinTime", "ms");
        properties.addView(updateMinTimeView);
    }
}