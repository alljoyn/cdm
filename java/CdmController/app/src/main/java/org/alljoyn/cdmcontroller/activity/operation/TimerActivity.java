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
import org.alljoyn.cdmcontroller.view.method.MethodView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;

public class TimerActivity extends InterfaceActivity {

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {

        View referenceTimerView = new ReadOnlyValuePropertyView(this, this.intf, "ReferenceTimer", "seconds");
        properties.addView(referenceTimerView);

        View targetTimeToStartView = new ReadOnlyValuePropertyView(this, this.intf, "TargetTimeToStart", "seconds");
        properties.addView(targetTimeToStartView);

        View targetTimeToStopView = new ReadOnlyValuePropertyView(this, this.intf, "TargetTimeToStop", "seconds");
        properties.addView(targetTimeToStopView);

        View estimatedTimeToEndView = new ReadOnlyValuePropertyView(this, this.intf, "EstimatedTimeToEnd", "seconds");
        properties.addView(estimatedTimeToEndView);

        View runningTimeView = new ReadOnlyValuePropertyView(this, this.intf, "RunningTime", "seconds");
        properties.addView(runningTimeView);

        View targetDurationView = new ReadOnlyValuePropertyView(this, this.intf, "TargetDuration", "seconds");
        properties.addView(targetDurationView);

        View setTargetTimeToStartView = new MethodView(this, this.intf, "SetTargetTimeToStart", "targetTimeToStart");
        methods.addView(setTargetTimeToStartView);

        View setTargetTimeToStopView = new MethodView(this, this.intf, "SetTargetTimeToStop", "targetTimeToStop");
        methods.addView(setTargetTimeToStopView);

    }
}