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

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.method.MethodSupportedParamEnumView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlySupportedEnumPropertyView;
import org.alljoyn.smartspaces.operation.CycleControl;

public class CycleControlActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View operationalStateView = new ReadOnlySupportedEnumPropertyView(this, this.intf, "OperationalState", "SupportedOperationalStates", CycleControl.OperationalState.class);
        properties.addView(operationalStateView);

        View sendCommandView = new MethodSupportedParamEnumView(this, this.intf, "ExecuteOperationalCommand", new String[]{"SupportedOperationalCommands"}, new Class[]{CycleControl.OperationalCommand.class}, "command");
        methods.addView(sendCommandView);
    }

}