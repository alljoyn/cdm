/*
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
import org.alljoyn.cdmcontroller.view.PropertyView;
import org.alljoyn.cdmcontroller.view.method.MethodView;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.HashMap;
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
    private Map<String, Map<String, ProxyBusObject>> proxyBusObjects;
    private Map<String, Map<String, Object>> interfaceBusObjects;

    public DeviceImpl(Context context, BusAttachment bus, UUID deviceId, String busName, int version, short port, AboutObjectDescription[] aboutObjectDescriptions, Map<String, Variant> aboutData) {
        this.context = context;
        this.bus = bus;
        this.id = deviceId;
        this.busName = busName;
        this.version = version;
        this.port = port;
        this.aboutObjectDescriptions = aboutObjectDescriptions;
        this.aboutData = aboutData;
        this.proxyBusObjects = new HashMap<>();
        this.interfaceBusObjects = new HashMap<>();
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
        Object proxyBusObjectIntf = getFromMap(this.interfaceBusObjects, objPath, intfName);
        if(proxyBusObjectIntf != null) {
            return proxyBusObjectIntf;
        }

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

        ProxyBusObject proxyBusObject = this.bus.getProxyBusObject(this.busName, objPath,
                sessionId.value, new Class<?>[]{clazz});
        addToMap(this.proxyBusObjects, objPath, intfName, proxyBusObject);
        proxyBusObjectIntf = proxyBusObject.getInterface(clazz);
        addToMap(this.interfaceBusObjects, objPath, intfName, proxyBusObjectIntf);
        return proxyBusObjectIntf;
    }

    private <T> void addToMap(Map<String, Map<String, T>> map, String objPath, String intfName, T value) {
        Map<String, T> innerMap = map.get(objPath);
        if (innerMap == null) {
            innerMap = new HashMap<>();
            map.put(objPath, innerMap);
        }
        innerMap.put(intfName, value);
    }

    private <T> T getFromMap(Map<String, Map<String, T>> map, String objPath, String intfName) {
        Map<String, T> innerMap = map.get(objPath);
        if (innerMap == null) {
            return null;
        }
        return innerMap.get(intfName);
    }

    @Override
    public Status registerSignal(BusObject obj) {
        return this.bus.registerSignalHandlers(obj);
    }

    @Override
    public void unregisterSignal(BusObject obj) {
        this.bus.unregisterSignalHandlers(obj);
    }

    @Override
    public Status registerPropertiesChangedSignal(String objPath, String interfaceName, PropertiesChangedListener listener) {
        ProxyBusObject proxyBusObject = getFromMap(this.proxyBusObjects, objPath, interfaceName);
        if(proxyBusObject == null) {
            getInterface(objPath, interfaceName);
            proxyBusObject = getFromMap(this.proxyBusObjects, objPath, interfaceName);
        }
        return proxyBusObject.registerPropertiesChangedListener(interfaceName, new String[]{}, listener);
    }

    @Override
    public void unregisterPropertiesChangedSignal(String objPath, String interfaceName, PropertiesChangedListener listener) {
        ProxyBusObject proxyBusObject = getFromMap(this.proxyBusObjects, objPath, interfaceName);
        if(proxyBusObject == null) {
            getInterface(objPath, interfaceName);
            proxyBusObject = getFromMap(this.proxyBusObjects, objPath, interfaceName);
        }
        proxyBusObject.unregisterPropertiesChangedListener(interfaceName, listener);
    }

    @Override
    public boolean hasInterface(String interfaceName) {
        for(AboutObjectDescription aboutObjectDescription: aboutObjectDescriptions) {
            for(String intf : aboutObjectDescription.interfaces) {
                if(intf.equals(interfaceName)) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public Object getProperty(String objPath, String interfaceName, String propertyName, Object... params) {
        if(objPath != null) {
            Object intf = getInterface(objPath, interfaceName);
            try {
                Method valueGetter = intf.getClass().getDeclaredMethod("get" + propertyName);
                return valueGetter.invoke(intf, params);
            } catch (NoSuchMethodException e) {
                Log.d(TAG, "Method does not exist: " + e.getMessage());
            } catch (InvocationTargetException e) {
                Throwable currentException = e;
                while(currentException.getMessage() == null) {
                    currentException = currentException.getCause();
                }
                Log.d(TAG, "Method returned error: " + currentException.getMessage());
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }

        return null;
    }

    @Override
    public Class<?> getPropertyType(String objPath, String interfaceName, String propertyName) {
        if(objPath != null) {
            Object intf = getInterface(objPath, interfaceName);
            try {
                Method valueGetter = intf.getClass().getDeclaredMethod("get" + propertyName);
                return valueGetter.getReturnType();
            } catch (NoSuchMethodException e) {
                Log.d(TAG, "Method does not exist: " + e.getMessage());
            }
        }

        return null;
    }

    @Override
    public Class<?>[] getPropertyParameterTypes(String objPath, String interfaceName, String propertyName) {
        if(objPath != null) {
            Object intf = getInterface(objPath, interfaceName);
            try {
                Method valueGetter = intf.getClass().getDeclaredMethod("get" + propertyName);
                return valueGetter.getParameterTypes();
            } catch (NoSuchMethodException e) {
                Log.d(TAG, "Method does not exist: " + e.getMessage());
            }
        }

        return null;
    }

    @Override
    public void setProperty(String objPath, String interfaceName, String propertyName, Object value) {
        if(objPath != null) {
            Object intf = getInterface(objPath, interfaceName);
            try {
                Method valueGetter = intf.getClass().getDeclaredMethod("get" + propertyName);
                Method valueSetter = intf.getClass().getDeclaredMethod("set" + propertyName, valueGetter.getReturnType());
                Object param = CdmUtil.parseParam(valueGetter.getReturnType(), value);
                valueSetter.invoke(intf, param);
            } catch (NoSuchMethodException e) {
                Log.d(TAG, "Method does not exist: " + e.getMessage());
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public Object invokeMethod(String objPath, String interfaceName, String methodName, Object... params) {
        if(objPath != null) {
            try {
                Method method = getMethod(objPath, interfaceName, methodName);
                return method.invoke(getInterface(objPath, interfaceName), params);
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }

        return null;
    }

    @Override
    public Class<?>[] getMethodParameterTypes(String objPath, String interfaceName, String methodName) {
        if(objPath != null) {
            Method method = getMethod(objPath, interfaceName, methodName);
            return method.getParameterTypes();
        }
        return null;
    }

    private Method getMethod(String objPath, String interfaceName, String methodName) {
        if(objPath != null) {
            Object intf = getInterface(objPath, interfaceName);
            String methodNameUpper = methodName.toUpperCase();
            for (Method method : intf.getClass().getDeclaredMethods()) {
                if (method.getName().toUpperCase().equals(methodNameUpper)) {
                    return method;
                }
            }
        }

        return null;
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

    @Override
    public boolean canAddChildren() {
        return false;
    }

    @Override
    public void applyPreset(String objPath, String interfaceName, Preset preset) {
        Map<String, Object> propertyValues = preset.getMap();
        for (String key : propertyValues.keySet()) {
            this.setProperty(objPath, interfaceName, key, propertyValues.get(key));
        }
    }
}
