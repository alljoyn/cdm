/*
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *    
 *    SPDX-License-Identifier: Apache-2.0
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *    
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
*/

package org.alljoyn.cdmcontroller.logic;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import org.alljoyn.bus.AboutKeys;
import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Mutable;
import org.alljoyn.bus.PropertiesChangedListener;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.SessionListener;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.util.CdmUtil;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;

public class DeviceImpl implements Device {
    private static final String TAG = "CDM_DeviceImpl";

    private BusAttachment bus;
    private Context context;
    private UUID id;
    private String busName;
    private int version;
    private short port;
    private AboutObjectDescription[] aboutObjectDescriptions = null;
    private Map<String, Variant> aboutData = null;
    Mutable.IntegerValue sessionId = null;
    private ProxyBusObject proxyBusObject;
    private String interfaceName;
    private String objPath;

    public DeviceImpl(Context context, BusAttachment bus, UUID deviceId, String busName, int version, short port, AboutObjectDescription[] aboutObjectDescriptions, Map<String, Variant> aboutData) {
        this.context = context;
        this.bus = bus;
        this.id = deviceId;
        this.busName = busName;
        this.version = version;
        this.port = port;
        this.aboutObjectDescriptions = aboutObjectDescriptions;
        this.aboutData = aboutData;
    }

    public String getName() {
        try {
            return (String) aboutData.get(AboutKeys.ABOUT_DEVICE_NAME).getObject(String.class);
        } catch (BusException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public String getFriendlyName() {
        try {
            return (String) aboutData.get(AboutKeys.ABOUT_APP_NAME).getObject(String.class);
        } catch (BusException e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<DeviceType> getDeviceType(String objPath) {
        List<DeviceType> result = new ArrayList<>();
        DeviceType type = DeviceType.OTHER;
        DeviceTypeDescription[] deviceTypeDescriptions = null;
        try {
            deviceTypeDescriptions = (DeviceTypeDescription[]) aboutData.get(AboutDataKeys.DEVICE_TYPE_DESCRIPTION).getObject(DeviceTypeDescription[].class);
        } catch (BusException e) {
            e.printStackTrace();
            return result;
        }
        for (DeviceTypeDescription desc : deviceTypeDescriptions) {
            if (desc.objectPath.equals(objPath)) {
                result.add((DeviceType)CdmUtil.findEnum(desc.deviceType, DeviceType.class));
            }
        }

        return result;
    }

    public UUID getId() {
        return this.id;
    }

    @Override
    public AboutObjectDescription[] getAboutObjectDescriptions() {
        return this.aboutObjectDescriptions;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Device)
            return this.id.equals(((Device) o).getId());
        else if (o instanceof UUID) {
            return this.id.equals(o);
        }
        return super.equals(o);
    }

    @Override
    public Object getInterface(String objPath, String intfName) {
        String pkg = intfName.substring(0, intfName.lastIndexOf('.'));
        String name = intfName.substring(intfName.lastIndexOf('.') + 1);
        Class<?> clazz = null;
        try {
            clazz = Class.forName(pkg.toLowerCase() + "." + name);
        } catch (ClassNotFoundException e) {
            Log.e(TAG, intfName + " interface not declared in pkg");
            return null;
        }

        if (this.sessionId == null) {
            this.sessionId = joinSession();
            if (sessionId == null)
                return null;
        }

        this.interfaceName = intfName;
        this.objPath = objPath;
        this.proxyBusObject = this.bus.getProxyBusObject(this.busName, objPath,
                sessionId.value, new Class<?>[]{clazz});

        return proxyBusObject.getInterface(clazz);
    }

    @Override
    public Status registerSignal(BusObject obj) {
        return this.bus.registerSignalHandlers(obj);
    }

    @Override
    public Status registerPropertiesChangedSignal(PropertiesChangedListener listener) {
        return this.proxyBusObject.registerPropertiesChangedListener(this.interfaceName, new String[]{}, listener);
    }

    @Override
    public void unregisterPropertiesChangedSignal(PropertiesChangedListener listener) {
        this.proxyBusObject.unregisterPropertiesChangedListener(this.interfaceName, listener);
    }


    @Override
    public void unregisterSignal(BusObject obj) {
        this.bus.unregisterSignalHandlers(obj);
    }

    protected Mutable.IntegerValue joinSession() {
        Mutable.IntegerValue sessionId = new Mutable.IntegerValue();
        SessionOpts sessionOpts = new SessionOpts(SessionOpts.TRAFFIC_MESSAGES, false, SessionOpts.PROXIMITY_ANY,
                SessionOpts.TRANSPORT_ANY);
        this.bus.enableConcurrentCallbacks();

        if (this.bus.joinSession(this.busName, this.port, sessionId, sessionOpts, new SessionListener() {
            @Override
            public void sessionLost(int sessionId, int reason) {
                Log.e(TAG, String.format("BusListener.sessionLost(sessionId = %d, reason = %d)", sessionId, reason));
            }
        }) != Status.OK) {
            Log.e(TAG, String.format("BusAttachment.joinSession() Failed - sessionId: %d", sessionId.value));
            connectionLost();
            return null;
        }
        return sessionId;
    }

    protected void connectionLost() {
        Intent intent = new Intent(MessageType.ON_DEVICE_REMOVED);
        intent.putExtra(IntentKeys.DEVICE_ID, this.id);
        this.context.sendBroadcast(intent);
    }
}