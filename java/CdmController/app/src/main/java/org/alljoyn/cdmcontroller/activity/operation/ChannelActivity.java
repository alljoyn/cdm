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
import org.alljoyn.cdmcontroller.view.method.MethodView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.cdmcontroller.view.property.SupportedValuesPropertyView;

public class ChannelActivity extends InterfaceActivity {

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View channelIdView = new SupportedValuesPropertyView(this, this.intf, "ChannelId", null, 0, "getChannelList", 0, 100);
        properties.addView(channelIdView);

        View totalNumberOfChannelsView = new ReadOnlyValuePropertyView(this, this.intf, "TotalNumberOfChannels", null);
        properties.addView(totalNumberOfChannelsView);

        View getChannelListView = new MethodView(this, this.intf, "GetChannelList", "startingRecord", "numRecords");
        methods.addView(getChannelListView);
    }

    @BusSignalHandler(iface = "org.alljoyn.smartspaces.operation.Channel", signal = "ChannelListChanged")
    public void channelListChanged() {
        notifyEvent("ChannelListChanged");
    }
}