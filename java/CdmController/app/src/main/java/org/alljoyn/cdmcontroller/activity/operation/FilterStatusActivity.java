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

public class FilterStatusActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View expectedLifeInDaysView = new ReadOnlyValuePropertyView(this, this.intf, "ExpectedLifeInDays", null);
        properties.addView(expectedLifeInDaysView);

        View isCleanableView = new ReadOnlyValuePropertyView(this, this.intf, "IsCleanable", null);
        properties.addView(isCleanableView);

        View orderPercentageView = new ReadOnlyValuePropertyView(this, this.intf, "OrderPercentage", null);
        properties.addView(orderPercentageView);

        View manufacturerView = new ReadOnlyValuePropertyView(this, this.intf, "Manufacturer", null);
        properties.addView(manufacturerView);

        View partNumberView = new ReadOnlyValuePropertyView(this, this.intf, "PartNumber", null);
        properties.addView(partNumberView);

        View urlView = new ReadOnlyValuePropertyView(this, this.intf, "Url", null);
        properties.addView(urlView);

        View lifeRemainingView = new ReadOnlyValuePropertyView(this, this.intf, "LifeRemaining", null);
        properties.addView(lifeRemainingView);
    }
}