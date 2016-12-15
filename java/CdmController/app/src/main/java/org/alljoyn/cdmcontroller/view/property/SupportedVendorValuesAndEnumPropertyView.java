/*
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
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
import android.widget.Toast;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;
import org.alljoyn.smartspaces.EnumBase;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

public class SupportedVendorValuesAndEnumPropertyView<T extends EnumBase<T>> extends PropertyView
        implements OnMethodResultListener{
    private static final String TAG = "CDM_ReadProperty";

    private TextView nameView;
    private Spinner valuesView;
    private TextView unitView;
    private Object[] params;

    private int positionValue = -1;
    private int positionName = -1;

    private ArrayAdapter<Item<Object>> valuesAdapter;
    private SpinnerInteractionListener listener = null;

    private Class<T> enumClazz = null;

    private String supportedEnumName = null;
    private Object supportedList = null;
    private Object supportedVendorList = null;

    @Override
    public void OnMethodResultReceived(Object result) {
        this.setSupportedVendorListView(result);
    }

    private class Item<Object> {
        private String name = null;
        private Object value;

        public Item(String name, Object value){
            this.name = name;
            this.value = value;
        }

        public String toString() {
            if (name == null)
                return value.toString();
            else
                return name;
        }

        public Object toValue() {
            return value;
        }
    }

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
                //ReadOnlySupportedEnumPropertyView.this.setProperty(SupportedValuesPropertyView.this.valuesAdapter.getItem(pos));
                SupportedVendorValuesAndEnumPropertyView.this.setPosition();
                SupportedVendorValuesAndEnumPropertyView.this.warning(name + " is read only property.");
                userSelect = false;
            }
        }
        @Override
        public void onNothingSelected(AdapterView<?> parent) {

        }
    }

    public SupportedVendorValuesAndEnumPropertyView(Context context, Device device, String objPath,
                                                    String interfaceName, String propertyName, String unit,
                                                    int positionName, int positionValue, String supportedEnumPropertyName,
                                                    Class<T> clazz, String SupportedListMethodName, Object... parameters) {
        super(context, device, objPath, interfaceName, propertyName, unit);

        params = parameters;

        this.positionName = positionName;
        this.positionValue = positionValue;
        this.enumClazz = clazz;
        this.supportedEnumName = supportedEnumPropertyName;
    }

    public SupportedVendorValuesAndEnumPropertyView(Context context, Device device, String objPath,
                                                    String interfaceName, String propertyName, String unit,
                                                    String supportedEnumPropertyName, Class<T> clazz, String SupportedListMethodName,
                                                    Object... parameters) {
        this(context, device, objPath, interfaceName, propertyName, unit, -1, -1, supportedEnumPropertyName, clazz, SupportedListMethodName, parameters);
    }

    public String[] getNames() {
        return new String[]{this.name, this.supportedEnumName};
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_supported_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valuesView = (Spinner) view.findViewById(R.id.property_values);
        this.unitView = (TextView) view.findViewById(R.id.property_unit);
        Log.d(TAG, "1: valueView is " + this.valuesView.toString());


        valuesAdapter = new ArrayAdapter<Item<Object>>(this.getContext(), android.R.layout.simple_spinner_item);
        this.valuesView.setAdapter(valuesAdapter);

        this.nameView.setText(this.name);
        if (this.unit != null && !this.unit.isEmpty())
            this.unitView.setText(this.unit);
        else
            this.unitView.setVisibility(View.GONE);
    }

    public void onPropertiesChangedSignal(String name, Variant value) {
        Object obj = null;
        try {
            obj = value.getObject(this.propertyType);
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        if (name.equals(this.supportedEnumName)) {
            setSupportedEnumListView(obj);
        } else
            super.onPropertiesChangedSignal(name, value);
    }

    private void setSupportedEnumListView(Object supportedList) {
        this.supportedList = supportedList;
        setSupportedListView(supportedVendorList, supportedList);
    }

    private void setSupportedVendorListView(Object supportedVendorList) {
        this.supportedVendorList = supportedVendorList;
        setSupportedListView(supportedVendorList, supportedList);
    }

    private synchronized void setSupportedListView(Object supportedVendorList, Object supportedList) {
        SupportedVendorValuesAndEnumPropertyView.this.valuesAdapter.clear();
        if (supportedList != null) {
            for (Object obj : CdmUtil.toObjectArray(supportedList)) {
                T item = (T) CdmUtil.findEnum(obj, SupportedVendorValuesAndEnumPropertyView.this.enumClazz);
                if (item != null) {
                    try {
                        Object valueI = item.toValue();
                        String nameI = item.toString();
                        if (nameI != null && valueI != null)
                            SupportedVendorValuesAndEnumPropertyView.this.valuesAdapter.add(new Item<Object>(nameI, valueI));
                    } catch (NullPointerException e) {
                        e.printStackTrace();
                    }
                } else {
                    if (supportedVendorList != null) {
                        for (Object obj1 : CdmUtil.toObjectArray(supportedVendorList)) {
                            if (SupportedVendorValuesAndEnumPropertyView.this.positionValue == -1)
                                SupportedVendorValuesAndEnumPropertyView.this.valuesAdapter.add(new Item<Object>(null,obj1));
                            else {
                                Object valueI = null;
                                String nameI = null;
                                for (Field field : obj1.getClass().getFields()) {
                                    if (field.getAnnotation(Position.class).value() == SupportedVendorValuesAndEnumPropertyView.this.positionName) {
                                        try {
                                            nameI = field.get(obj1).toString();
                                        } catch (IllegalAccessException e) {
                                            e.printStackTrace();
                                        }
                                    }
                                    if (field.getAnnotation(Position.class).value() == SupportedVendorValuesAndEnumPropertyView.this.positionValue) {
                                        try {
                                            valueI = field.get(obj1);
                                        } catch (IllegalAccessException e) {
                                            e.printStackTrace();
                                        }
                                    }
                                }
                                if (nameI != null && valueI != null) {
                                    if (valueI.toString().equals(obj.toString()))
                                        SupportedVendorValuesAndEnumPropertyView.this.valuesAdapter.add(new Item<Object>(nameI, valueI));
                                }
                            }
                        }
                    }
                }
            }
        }

        if (this.currentValue != null) {
            setValueView(this.currentValue);
        }
    }

    int positionC = 0;
    
    @Override
    public void setValueView(Object value) {
        positionC = findPosition(value);
        if (positionC != -1)
            this.valuesView.setSelection(positionC);
        if (this.listener == null) {
            this.listener = new SpinnerInteractionListener();
            this.valuesView.setOnItemSelectedListener(this.listener);
            this.valuesView.setOnTouchListener(this.listener);
        }
    }
    private void setPosition(){
        this.valuesView.setSelection(positionC);
    }

    private int findPosition(Object value) {
        Item<Object> item = null;
        for (int i = 0; i< this.valuesAdapter.getCount(); i++) {
            item = this.valuesAdapter.getItem(i);
            if (item.toValue().toString().equals(value.toString()))
                return i;
        }
        return -1;
    }

    @Override
    public void getProperty() {
        new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... voids) {
                Object returnObj = null;
                try {
                    Class<?>[] paramTypes = SupportedVendorValuesAndEnumPropertyView.this.propertyParameterTypes;
                    int idx = 0;
                    for (Class<?> clazz : paramTypes) {
                        SupportedVendorValuesAndEnumPropertyView.this.params[idx] = CdmUtil.parseParam(clazz, SupportedVendorValuesAndEnumPropertyView.this.params[idx]);
                        idx++;
                    }
                    returnObj = device.getProperty(
                            SupportedVendorValuesAndEnumPropertyView.this.objPath,
                            SupportedVendorValuesAndEnumPropertyView.this.interfaceName,
                            SupportedVendorValuesAndEnumPropertyView.this.name,
                            SupportedVendorValuesAndEnumPropertyView.this.params);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                setSupportedVendorListView(o);
            }
        }.execute();

        new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... voids) {
                return device.getProperty(
                        SupportedVendorValuesAndEnumPropertyView.this.objPath,
                        SupportedVendorValuesAndEnumPropertyView.this.interfaceName,
                        SupportedVendorValuesAndEnumPropertyView.this.supportedEnumName);
            }

            @Override
            protected void onPostExecute(Object o) {
                setSupportedEnumListView(o);
            }
        }.execute();

        super.getProperty();
    }

    private void warning(String msg) {
        Toast.makeText(this.getContext(), msg, Toast.LENGTH_SHORT).show();
    }

}