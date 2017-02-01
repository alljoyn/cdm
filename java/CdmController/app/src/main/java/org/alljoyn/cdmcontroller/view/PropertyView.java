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

package org.alljoyn.cdmcontroller.view;

import android.content.Context;
import android.os.AsyncTask;
import android.widget.LinearLayout;
import android.widget.Toast;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.util.CdmUtil;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public abstract class PropertyView extends LinearLayout {
    protected Method valueGetter = null;
    protected Method valueSetter = null;

    protected Object busObject = null;

    protected String name = null;
    protected String unit = null;

    protected Object currentValue = null;

    public PropertyView(Context context, Object obj, String propertyName, String unit) {
        super(context);
        try {
            this.valueGetter = obj.getClass().getDeclaredMethod("get" + propertyName);
        } catch (NoSuchMethodException e) {
            this.valueGetter = null;
        }

        try {
            this.valueSetter = obj.getClass().getDeclaredMethod("set" + propertyName, this.valueGetter.getReturnType());
        } catch (NoSuchMethodException e) {
            this.valueSetter = null;
        }

        this.name = propertyName;
        this.busObject = obj;
        this.unit = unit;
    }

    public String[] getNames() { return new String[]{this.name}; }

    public void onPropertiesChangedSignal(String name, Variant value) {
        if (!name.equals(this.name))
            return;

        try {
            this.currentValue = value.getObject(this.valueGetter.getReturnType());
            this.setValueView(this.currentValue);
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }
        setValueView(this.currentValue);
    }

    public abstract void initView();

    protected abstract void setValueView(Object value);

    public void setProperty(Object value) {
        if (value.equals(this.currentValue))
            return;

        AsyncTask<Object, Void, Boolean> excuteSet = new AsyncTask<Object, Void, Boolean>() {
            @Override
            protected Boolean doInBackground(Object... params) {
                try {
                    if (PropertyView.this.valueSetter != null) {
                        Object param = CdmUtil.parseParam(PropertyView.this.valueGetter.getReturnType(), params[0]);
                        valueSetter.invoke(PropertyView.this.busObject, param);
                    } else
                        return false;
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                    return false;
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                    return false;
                }
                PropertyView.this.currentValue = params[0];
                return true;
            }

            @Override
            protected void onPostExecute(Boolean result) {
                if (!result) {
                    Toast.makeText(PropertyView.this.getContext(), "Set " + PropertyView.this.name + " Property is failed", Toast.LENGTH_SHORT).show();
                    PropertyView.this.setValueView(PropertyView.this.currentValue);
                }
            }

        };
        excuteSet.execute(value);
    }

    public void getProperty() {
        AsyncTask<Void, Void, Object> excuteGet = new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... params) {
                Object returnObj = null;
                try {
                    if (PropertyView.this.valueGetter != null) {
                        returnObj = valueGetter.invoke(PropertyView.this.busObject);
                        PropertyView.this.currentValue = returnObj;
                    }
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                String strResult;
                if (o != null) {
                    PropertyView.this.setValueView(o);
                } else {
                    PropertyView.this.setValueView(PropertyView.this.currentValue);
                    Toast.makeText(PropertyView.this.getContext(), "Get " + PropertyView.this.name + " Property is failed", Toast.LENGTH_SHORT).show();
                }

            }
        };
        excuteGet.execute();
    }
}