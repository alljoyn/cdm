/*
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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

package org.alljoyn.cdmcontroller.view.property;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.concurrent.Executor;

public class SupportedValuesPropertyView extends PropertyView {
    private static final String TAG = "CDM_ReadWriteProperty";

    private Method supportedGetter = null;
    private String supportedName = null;

    private TextView nameView;
    private Spinner valuesView;
    private TextView unitView;
    private Object[] params;
    private int position = -1;

    private ArrayAdapter<Object> valuesAdapter;

    public class SpinnerInteractionListener implements AdapterView.OnItemSelectedListener, View.OnTouchListener {

        boolean userSelect = false;

        @Override
        public boolean onTouch(View v, MotionEvent event) {
            userSelect = true;
            return false;
        }

        @Override
        public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
            if (userSelect) {
                SupportedValuesPropertyView.this.setProperty(SupportedValuesPropertyView.this.valuesAdapter.getItem(pos));
                userSelect = false;
            }
        }

        @Override
        public void onNothingSelected(AdapterView<?> parent) {

        }
    }

    public SupportedValuesPropertyView(Context context, Object obj, String propertyName, String unit, int position, String supportedListPropertyName) {
        super(context, obj, propertyName, unit);
        this.supportedName = supportedListPropertyName;
        this.position = position;
        try {
            this.supportedGetter = obj.getClass().getMethod("get" + supportedListPropertyName);
        } catch (NoSuchMethodException e) {
            this.supportedGetter = null;
        }
    }

    public SupportedValuesPropertyView(Context context, Object obj, String propertyName, String unit, String SupportedListPropertyName) {
        this(context, obj, propertyName, unit, -1, SupportedListPropertyName);
    }

    public SupportedValuesPropertyView(Context context, Object obj, String propertyName, String unit, int position, String SupportedListMethodName, Object... parameters) {
        super(context, obj, propertyName, unit);

        params = parameters;

        this.position = position;

        this.supportedGetter = null;
        for (Method method : obj.getClass().getDeclaredMethods()) {
            if (method.getName().equals(SupportedListMethodName)) {
                this.supportedGetter = method;
                break;
            }
        }
    }

    public SupportedValuesPropertyView(Context context, Object obj, String propertyName, String unit, String SupportedListMethodName, Object... parameters) {
        this(context, obj, propertyName, unit, -1, SupportedListMethodName, parameters);
    }

    public String[] getNames() {
        return new String[]{this.name, this.supportedName};
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_supported_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valuesView = (Spinner) view.findViewById(R.id.property_values);
        this.unitView = (TextView) view.findViewById(R.id.property_unit);
        Log.d(TAG, "1: valueView is " + this.valuesView.toString());


        valuesAdapter = new ArrayAdapter<Object>(this.getContext(), android.R.layout.simple_spinner_item);
        this.valuesView.setAdapter(valuesAdapter);

        this.nameView.setText(this.name);
        if (this.unit != null && !this.unit.isEmpty())
            this.unitView.setText(this.unit);
        else
            this.unitView.setVisibility(View.GONE);

        SpinnerInteractionListener listener = new SpinnerInteractionListener();
        this.valuesView.setOnTouchListener(listener);
        this.valuesView.setOnItemSelectedListener(listener);
    }

    public void onPropertiesChangedSignal(String name, Variant value) {
        Object obj = null;
        try {
            obj = value.getObject(this.valueGetter.getReturnType());
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        if (name.equals(this.supportedName)) {
            setSupportedListView(obj);
        } else
            super.onPropertiesChangedSignal(name, value);
    }

    private void setSupportedListView(Object supportedList) {
        if (supportedList != null) {
            SupportedValuesPropertyView.this.valuesAdapter.clear();
            for (Object obj : CdmUtil.toObjectArray(supportedList)) {
                if (SupportedValuesPropertyView.this.position == -1)
                    SupportedValuesPropertyView.this.valuesAdapter.add(obj);
                else {
                    for (Field field : obj.getClass().getFields()) {
                        if (field.getAnnotation(Position.class).value() == SupportedValuesPropertyView.this.position) {
                            Object value = null;
                            try {
                                value = field.get(obj);
                                SupportedValuesPropertyView.this.valuesAdapter.add(value);
                            } catch (IllegalAccessException e) {
                                e.printStackTrace();
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (this.currentValue != null) {
            setValueView(this.currentValue);
        }
    }

    @Override
    public void setValueView(Object value) {
        this.valuesView.setSelection(this.valuesAdapter.getPosition(value));
    }

    @Override
    public void getProperty() {
        AsyncTask<Void, Void, Object> execute = new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... voids) {
                Object returnObj = null;
                try {
                    if (SupportedValuesPropertyView.this.supportedGetter != null) {
                        Class<?>[] paramTypes = SupportedValuesPropertyView.this.supportedGetter.getParameterTypes();
                        Object[] params = new Object[paramTypes.length];
                        int idx = 0;
                        for (Class<?> clazz : paramTypes) {
                            SupportedValuesPropertyView.this.params[idx] = CdmUtil.parseParam(clazz, SupportedValuesPropertyView.this.params[idx]);
                            idx++;
                        }
                        returnObj = supportedGetter.invoke(SupportedValuesPropertyView.this.busObject, SupportedValuesPropertyView.this.params);
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
                setSupportedListView(o);
            }
        }.execute();
        super.getProperty();
    }
}