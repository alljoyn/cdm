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

import org.alljoyn.cdmcontroller.view.property.ReadWriteBoolPropertyView;
import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.property.MinMaxPropertyView;

public class WindDirectionActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View horizontalDirectionView = new MinMaxPropertyView(this, this.intf, "HorizontalDirection", null, null, "HorizontalMax", null);
        properties.addView(horizontalDirectionView);
        View horizontalAutoModeView = new ReadWriteBoolPropertyView(this, this.intf, "HorizontalAutoMode");
        properties.addView(horizontalAutoModeView);
        View verticalDirectionView = new MinMaxPropertyView(this, this.intf, "VerticalDirection", null, null, "VerticalMax", null);
        properties.addView(verticalDirectionView);
        View verticalAutoModeView = new ReadWriteBoolPropertyView(this, this.intf, "VerticalAutoMode");
        properties.addView(verticalAutoModeView);
    }
}