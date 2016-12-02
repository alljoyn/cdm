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

package org.alljoyn.cdmcontroller.logic;

import android.content.Context;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;

import java.util.Collection;
import java.util.UUID;

public abstract class DeviceManager {
    protected Context context;
    private static DeviceManager instance = null;

    public static DeviceManager getInstance() {
        return instance;
    }

    protected DeviceManager(Context c) {
        this.context = c;
        instance = this;
    }

    public abstract Device getDevice(UUID id);

    public abstract Collection<Device> getDevices();

    public abstract void registerBusObject(BusObject busObject, String objPath);

    public abstract Status registerSignalHandlers(Object handler);

    public abstract void unregisterSignalHandlers(Object handler);
}