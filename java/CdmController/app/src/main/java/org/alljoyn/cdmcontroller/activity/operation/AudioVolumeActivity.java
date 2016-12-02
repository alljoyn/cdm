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
import org.alljoyn.cdmcontroller.view.property.MinMaxPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteBoolPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteValuePropertyView;

public class AudioVolumeActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View volumeView = new MinMaxPropertyView(this, this.intf, "Volume", null, null, "MaxVolume", null);
        properties.addView(volumeView);

        View muteView = new ReadWriteBoolPropertyView(this, this.intf, "Mute");
        properties.addView(muteView);
    }
}