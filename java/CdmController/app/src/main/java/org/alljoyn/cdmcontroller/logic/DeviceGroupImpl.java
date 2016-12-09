/*
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 */

package org.alljoyn.cdmcontroller.logic;

import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.PropertiesChangedListener;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.ifaces.About;
import org.alljoyn.cdmcontroller.view.PropertyView;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.UUID;


public class DeviceGroupImpl implements Device
{
    private List<Device> children;
    private String name;
    private UUID uuid;

    public DeviceGroupImpl(String name, List<Device> devices) {
        this.children = devices;
        this.name = name;
        this.uuid = UUID.randomUUID();
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getFriendlyName() {
        return name;
    }

    @Override
    public List<DeviceType> getDeviceType(String objPath) {
        List<DeviceType> deviceTypes = new ArrayList<>();

        for (Device device : children) {
            for (AboutObjectDescription aboutObjDesc : device.getAboutObjectDescriptions()) {
                if (aboutObjDesc.path.toUpperCase().contains("CDM")) {
                    deviceTypes.addAll(device.getDeviceType(aboutObjDesc.path));
                }
            }
        }

        return deviceTypes;
    }

    @Override
    public UUID getId() {
        return uuid;
    }

    @Override
    public AboutObjectDescription[] getAboutObjectDescriptions() {
        Set<String> interfaceSet = new HashSet<>();

        for (Device device : children) {
            for (AboutObjectDescription description : device.getAboutObjectDescriptions()) {
                for (String intf : description.interfaces) {
                    interfaceSet.add(intf);
                }
            }
        }

        AboutObjectDescription groupObjectDescription = new AboutObjectDescription();
        groupObjectDescription.path = "/Cdm/Group/" + name.replace(' ', '_');
        groupObjectDescription.interfaces = interfaceSet.toArray(new String[]{});

        AboutObjectDescription[] group = {groupObjectDescription};

        return group;
    }

    @Override
    public Object getInterface(String objPath, String intfName) {
        List<Object> childrenWithInterface = new ArrayList<>();

        for (Device device : children) {
            for(AboutObjectDescription aboutObjectDescription : device.getAboutObjectDescriptions()) {
                for(String intf : aboutObjectDescription.interfaces) {
                    if(intf.equals(intfName)) {
                        Object proxyIntf = device.getInterface(aboutObjectDescription.path, intfName);
                        childrenWithInterface.add(proxyIntf);
                    }
                }
            }

        }

        return childrenWithInterface;
    }

    @Override
    public Status registerSignal(BusObject obj) {
        Status status = Status.OK;

        for (Device device : children) {
            status = device.registerSignal(obj);
            if(status != Status.OK) {
                return status;
            }
        }

        return status;
    }

    @Override
    public Status registerPropertiesChangedSignal(String objPath, String interfaceName, PropertiesChangedListener listener) {
        Status status = Status.FAIL;

        for (Device device : children) {
            for(AboutObjectDescription aboutObjDesc : device.getAboutObjectDescriptions()) {
                if(!aboutObjDesc.path.contains("Cdm")) {
                    continue;
                }
                for(String intf : aboutObjDesc.interfaces) {
                    if(intf.equals(interfaceName)) {
                        status = device.registerPropertiesChangedSignal(aboutObjDesc.path, interfaceName, listener);
                        if (status != Status.OK) {
                            return status;
                        }
                        break;
                    }
                }
            }
        }

        return status;
    }

    @Override
    public void unregisterSignal(BusObject obj) {
        for (Device device : children) {
            device.unregisterSignal(obj);
        }
    }

    @Override
    public void unregisterPropertiesChangedSignal(String objPath, String interfaceName, PropertiesChangedListener listener) {
        for (Device device : children) {
            for(AboutObjectDescription aboutObjDesc : device.getAboutObjectDescriptions()) {
                if(!aboutObjDesc.path.contains("Cdm")) {
                    continue;
                }
                for(String intf : aboutObjDesc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        device.unregisterPropertiesChangedSignal(aboutObjDesc.path, interfaceName, listener);
                    }
                }
            }
        }
    }

    @Override
    public boolean hasInterface(String interfaceName) {
        for (Device device : children) {
            if (device.hasInterface(interfaceName)){
                return true;
            }
        }
        return false;
    }

    @Override
    public Object getProperty(String objPath, String interfaceName, String propertyName, Object... params) {
        List<Object> values = new ArrayList<>();

        for(Device device : children) {
            for(AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                for(String intf : desc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        Object property = device.getProperty(desc.path, interfaceName, propertyName, params);
                        if (property != null) {
                            values.add(property);
                        }
                    }
                }
            }
        }

        Object currentValue = null;
        for(Object value : values){
            currentValue = value;
            if(currentValue != null){
                break;
            }
        }

        for(Object value : values) {
            if(value == null) {
                continue;
            }
            if(!currentValue.equals(value)) {
                return "-";
            }
        }

        return currentValue;
    }

    @Override
    public Class<?> getPropertyType(String objPath, String interfaceName, String propertyName) {
        for(Device device : children) {
            for(AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                for(String intf : desc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        Class<?> propertyType = device.getPropertyType(desc.path, interfaceName, propertyName);
                        if (propertyType != null) {
                            return propertyType;
                        }
                    }
                }
            }
        }

        return null;
    }

    @Override
    public Class<?>[] getPropertyParameterTypes(String objPath, String interfaceName, String propertyName) {
        for(Device device : children) {
            for(AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                for(String intf : desc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        Class<?>[] propertyTypes = device.getPropertyParameterTypes(desc.path, interfaceName, propertyName);
                        if (propertyTypes != null) {
                            return propertyTypes;
                        }
                    }
                }
            }
        }

        return null;
    }

    @Override
    public void setProperty(String objPath, String interfaceName, String propertyName, Object value) {
        for(Device device : children) {
            for(AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                for(String intf : desc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        device.setProperty(desc.path, interfaceName, propertyName, value);
                    }
                }
            }
        }
    }

    @Override
    public Object invokeMethod(String objPath, String interfaceName, String methodName, Object... params) {
        List<Object> methodResults = new ArrayList<>();

        for(Device device : children) {
            for (AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                for(String intf : desc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        Object result = device.invokeMethod(desc.path, interfaceName, methodName, params);
                        if (result != null) {
                            methodResults.add(result);
                        }
                    }
                }
            }
        }

        return methodResults.toArray();
    }

    @Override
    public Class<?>[] getMethodParameterTypes(String objPath, String interfaceName, String methodName) {
        for(Device device : children) {
            for (AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                for(String intf : desc.interfaces) {
                    if (intf.equals(interfaceName)) {
                        Class<?>[] parameterTypes = device.getMethodParameterTypes(desc.path, interfaceName, methodName);
                        if (parameterTypes != null) {
                            return parameterTypes;
                        }
                    }
                }
            }
        }

        return null;
    }

    @Override
    public boolean canAddChildren() {
        return true;
    }

    @Override
    public void applyPreset(String objPath, String interfaceName, Preset preset) {
        for(Device child : children) {
            for(AboutObjectDescription aboutObjectDescription: child.getAboutObjectDescriptions()) {
                for(String intf : aboutObjectDescription.interfaces) {
                    if(intf.equals(interfaceName)) {
                        child.applyPreset(aboutObjectDescription.path, interfaceName, preset);
                    }
                }
            }
        }
    }
}