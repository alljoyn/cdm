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
import org.alljoyn.cdmcontroller.view.method.MethodResultEventView;
import org.alljoyn.cdmcontroller.view.property.OnMethodResultListener;
import org.alljoyn.cdmcontroller.view.property.SupportedVendorValuesAndEnumPropertyView;
import org.alljoyn.smartspaces.operation.DishWashingCyclePhase;

public class CyclePhaseActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(InterfaceActivity.CustomView properties, CustomView methods) {

        View cycleView = new SupportedVendorValuesAndEnumPropertyView(this, this.intf, "CyclePhase", null, 1, 0, "SupportedCyclePhases", DishWashingCyclePhase.CyclePhase.class, "GetVendorPhasesDescription", "en");
        properties.addView(cycleView);

        View getVendorPhasesDescriptionView = new MethodResultEventView(this, this.intf, "GetVendorPhasesDescription", "languageTag");
        methods.addView(getVendorPhasesDescriptionView);
        ((MethodResultEventView)getVendorPhasesDescriptionView).addOnResultListener((OnMethodResultListener)cycleView);
    }
}