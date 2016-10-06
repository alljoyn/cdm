/*
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

public class ListWithSubValuesPropertyView extends PropertyView {
    private static final String TAG = "CDM_ReadProperty";

    private TextView nameView;
    private TextView valueView;
    private TextView valueViewExt;
    private TextView unitView;
    private TextView[][] subValueViews;

    private SupportedSubValue[] supportedSubValues;
    private String paramName;

    public ListWithSubValuesPropertyView(Context context, Object obj, String propertyName, String paramName, String unit, String... supportedNames) {
        super(context, obj, propertyName, unit);

        supportedSubValues = new SupportedSubValue[supportedNames.length];
        int idx = 0;
        for (String supportedName : supportedNames)
        {
            supportedSubValues[idx] = new SupportedSubValue(obj, supportedName, idx, this);
            idx++;
        }
        this.paramName = paramName;
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_list_with_sub_values_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valueView = (TextView) view.findViewById(R.id.property_value);
        this.unitView = (TextView) view.findViewById(R.id.property_unit);
        this.valueViewExt = (TextView) view.findViewById(R.id.property_value_ext);
        this.valueViewExt.setVisibility(View.GONE);

        this.nameView.setText(this.name);
        if (this.unit != null && !this.unit.isEmpty())
            this.unitView.setText(this.unit);
        else
            this.unitView.setVisibility(View.GONE);

    }

    public void updateSupportedSubValueViews(int iInItem) {
        if (subValueViews == null) return;
        Object val;
        for (int i = 0; i < (Byte) this.currentValue; i++)
        {
            val = supportedSubValues[iInItem].getSupportedValue(i);
            if (val != null)
                subValueViews[i][iInItem].setText(val.toString());
            else
                subValueViews[i][iInItem].setText("Value");
        }
    }
    public void onPropertiesChangedSignal(String name, Variant value) {
        Object obj = null;
        try {
            obj = value.getObject(this.valueGetter.getReturnType());
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        boolean b = false;
        for (SupportedSubValue item : supportedSubValues)
        {
            b = item.onPropertiesChangedSignal(name, value);
        }
        if (!b)
            super.onPropertiesChangedSignal(name, value);
    }

    @Override
    public void getProperty() {
        super.getProperty();
        for (SupportedSubValue item : supportedSubValues)
        {
            item.getSupportedSubValuesProperty();
        }
    }

    @Override
    public void setValueView(Object value) {
        if (value.getClass().isArray()){
            this.valueView.setText("");
            this.valueViewExt.setVisibility(View.VISIBLE);
            this.valueViewExt.setText(CdmUtil.toString(value));
        } else {
            this.valueView.setText(CdmUtil.toString(value));
        }

        ViewGroup rootView = (ViewGroup) findViewById(R.id.property_list);
        //clear all views
        rootView.removeAllViewsInLayout();
        subValueViews = null;

        int idx = 0;
        if (value instanceof Byte) {
            idx = ((Byte) value).byteValue();
        } else if (value instanceof Short) {
            idx = ((Short) value).shortValue();
        } else
            return;
        subValueViews = new TextView[idx][supportedSubValues.length];
        int iInItem = 0;

        for (int i = 0; i< idx; i++) {

            LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            ViewGroup viewI = (ViewGroup) inflater.inflate(R.layout.view_list_item_with_sub_values_property, rootView, false);
            TextView nameViewI = (TextView)viewI.findViewById(R.id.property_name);

            if (paramName != null) {
                nameViewI.setText(this.paramName + " "+ i);
            } else {
                nameViewI.setText(value.getClass().getName());
            }
            TextView unitViewI = (TextView) viewI.findViewById(R.id.property_unit);
            if (this.unit != null && !this.unit.isEmpty())
                unitViewI.setText(this.unit);
            else
                unitViewI.setVisibility(View.GONE);

            TextView valueViewExtI = (TextView) viewI.findViewById(R.id.property_value_ext);
            valueViewExtI.setVisibility(View.GONE);

            ViewGroup rootViewIV = (ViewGroup) viewI.findViewById(R.id.property_sub_list);
            iInItem = 0;
            for (SupportedSubValue subValue : supportedSubValues) {
                ViewGroup viewIV = (ViewGroup) inflater.inflate(R.layout.view_list_item_with_sub_values_item_property, rootViewIV, false);
                TextView nameViewIV = (TextView) viewIV.findViewById(R.id.property_name);
                TextView valueViewIV = (TextView) viewIV.findViewById(R.id.property_value);
                TextView unitViewIV = (TextView) viewIV.findViewById(R.id.property_unit);
                TextView valueViewExtIV = (TextView) viewIV.findViewById(R.id.property_value_ext);
                valueViewExtIV.setVisibility(View.GONE);

                nameViewIV.setText(subValue.getSupportedName());
                Object valueIV = subValue.getSupportedValue(i);
                if (valueIV != null)
                    valueViewIV.setText(valueIV.toString());
                else
                    valueViewIV.setText("Value");
               // if (this.unit != null && !this.unit.isEmpty())
               //     this.unitView.setText(this.unit);
               // else
                unitViewIV.setVisibility(View.GONE);
                subValueViews[i][iInItem] = valueViewIV;
                rootViewIV.addView(viewIV);
                iInItem++;
            }
            rootView.addView(inflater.inflate(R.layout.view_seperator, rootView, false));
            rootView.addView(viewI);
        }
    }

    private class SupportedSubValue {
        private Method supportedGetter = null;
        private String supportedName = null;
        public String getSupportedName()
        {
            return supportedName;
        }
        private int id;

        private ArrayList<Object> values;
        private ListWithSubValuesPropertyView parent;

        public SupportedSubValue(Object obj, String supportedName, int id, ListWithSubValuesPropertyView parent) {
            try {
                this.supportedGetter = obj.getClass().getMethod("get" + supportedName);
            } catch (NoSuchMethodException e) {
                this.supportedGetter = null;
            }
            this.supportedName = supportedName;
            this.id = id;
            this.parent = parent;
            values = new ArrayList<Object>();
        }

        public boolean onPropertiesChangedSignal(String name, Variant value) {
            Object obj = null;
            try {
                //or valueGetter need to check
                obj = value.getObject(this.supportedGetter.getReturnType());
            } catch (BusException e) {
                e.printStackTrace();
                return false;
            }

            if (name.equals(this.supportedName)) {
                setSupportedList(obj);
                return true;
            } else
                return false;
        }

        public void getSupportedSubValuesProperty() {

            AsyncTask<Void, Void, Object> execute = new AsyncTask<Void, Void, Object>() {
                @Override
                protected Object doInBackground(Void... voids) {
                    Object returnObj = null;
                    try {
                        if (supportedGetter != null) {
                            Class<?>[] paramTypes = supportedGetter.getParameterTypes();
                            Object[] params = new Object[paramTypes.length];
                            int idx = 0;
                            for (Class<?> clazz : paramTypes) {
                                params[idx] = CdmUtil.parseParam(clazz, params[idx]);
                                idx++;
                            }
                            returnObj = supportedGetter.invoke(ListWithSubValuesPropertyView.this.busObject, params);
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
                    setSupportedList(o);
                }
            }.execute();
        }

        private void setSupportedList(Object supportedList) {
            if (supportedList != null) {
                values.clear();

                for (Object obj : CdmUtil.toObjectArray(supportedList)) {
                    values.add(obj);
                }
                parent.updateSupportedSubValueViews(id);
            }
        }

        public Object getSupportedValue(int i) {
            if ((values == null) || (values.isEmpty()) || (values.size()< i))
                return null;
            else
                return values.get(i);
        }
    }
}