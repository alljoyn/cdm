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

package org.alljoyn.cdmcontroller.activity.input;


import android.view.View;

import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.method.InjectEventsMethodView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;

public class HidActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View supportedEventsView = new ReadOnlyValuePropertyView(this, this.intf, "SupportedEvents", null);
        properties.addView(supportedEventsView);

        View injectEventsView = new InjectEventsMethodView(this, this.intf, "InjectEvents");
        methods.addView(injectEventsView);
    }
}