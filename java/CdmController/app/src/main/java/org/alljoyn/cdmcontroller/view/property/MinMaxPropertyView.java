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
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.view.PropertyView;
import org.alljoyn.cdmcontroller.view.custom.MinMaxSeekBar;
import org.alljoyn.cdmcontroller.util.CdmUtil;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class MinMaxPropertyView extends PropertyView {
    private Method minGetter;
    private Method maxGetter;
    private Method stepGetter;

    private TextView nameView;
    private TextView valueView;
    private TextView minView;
    private TextView maxView;
    private MinMaxSeekBar seekBar;
    private TextView stepView;
    private TextView unitView;
    private Button submitBtn;

    private String minName;
    private String maxName;
    private String stepName;
    private double min;
    private double max;
    private double step;

    public MinMaxPropertyView(Context context, Object obj, String valuePropertyName, String unit, String minPropertyName, String maxPropertyName, String stepPropertyName) {
        super(context, obj, valuePropertyName, unit);
        this.minName = minPropertyName;
        this.maxName = maxPropertyName;
        this.stepName = stepPropertyName;
        try {
            if (minPropertyName == null || minPropertyName.isEmpty())
                this.minGetter = null;
            else
                this.minGetter = obj.getClass().getDeclaredMethod("get" + minPropertyName);

            if (maxPropertyName == null || maxPropertyName.isEmpty())
                this.maxGetter = null;
            else
                this.maxGetter = obj.getClass().getDeclaredMethod("get" + maxPropertyName);

            if (stepPropertyName == null || stepPropertyName.isEmpty())
                this.stepGetter = null;
            else
                this.stepGetter = obj.getClass().getDeclaredMethod("get" + stepPropertyName);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }

    public String[] getNames() {
        return new String[]{this.name, this.minName, this.maxName, this.stepName};
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_min_max_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valueView = (TextView) view.findViewById(R.id.property_value);
        this.minView = (TextView) view.findViewById(R.id.min_value);
        this.maxView = (TextView) view.findViewById(R.id.max_value);
        this.seekBar = (MinMaxSeekBar) view.findViewById(R.id.seekBar);
        this.stepView = (TextView) view.findViewById(R.id.step_value);
        this.unitView = (TextView) view.findViewById(R.id.property_unit);

            this.nameView.setText(this.name);
        if (this.unit != null && !this.unit.isEmpty())
            this.unitView.setText(this.unit);
        else
            this.unitView.setVisibility(View.GONE);

        this.seekBar.setOnSeekBarChangeListener(new MinMaxSeekBar.OnMinMaxSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, double progress) {
                Object obj = CdmUtil.parseParam(MinMaxPropertyView.this.valueGetter.getReturnType(), progress);
                MinMaxPropertyView.this.setValueView(obj);
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar, double progress) {
                Object obj = CdmUtil.parseParam(MinMaxPropertyView.this.valueGetter.getReturnType(), progress);
                MinMaxPropertyView.this.setProperty(obj);
            }
        });
    }

    @Override
    public void onPropertiesChangedSignal(String name, Variant value) {
        Object obj = null;
        try {
            obj = value.getObject(this.valueGetter.getReturnType());
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        if (name.equals(this.stepName)) {
            setStepView(obj);
        } else if (name.equals(this.minName)) {
            setMinView(obj);
        } else if (name.equals(this.maxName)) {
            setMaxView(obj);
        } else
            super.onPropertiesChangedSignal(name, value);
    }

    @Override
    public void setValueView(Object value) {
        this.valueView.setText(value.toString());
        this.seekBar.setProgress(Double.valueOf(value.toString()));
    }

    private void setMinView(Object value) {
        if (value != null) {
            MinMaxPropertyView.this.minView.setText(value.toString());
            MinMaxPropertyView.this.min = Double.parseDouble(value.toString());
            MinMaxPropertyView.this.seekBar.setMin(MinMaxPropertyView.this.min);
        } else {
            MinMaxPropertyView.this.minView.setText("0");
            MinMaxPropertyView.this.min = 0.0;
            MinMaxPropertyView.this.seekBar.setMin(MinMaxPropertyView.this.min);
        }
    }

    private void setMaxView(Object value) {
        if (value != null) {
            MinMaxPropertyView.this.maxView.setText(value.toString());
            MinMaxPropertyView.this.max = Double.parseDouble(value.toString());
            MinMaxPropertyView.this.seekBar.setMax(MinMaxPropertyView.this.max);
        }
    }

    private void setStepView(Object value) {
        if (value != null) {
            MinMaxPropertyView.this.step = Double.parseDouble(value.toString());
            MinMaxPropertyView.this.stepView.setText(value.toString());
            MinMaxPropertyView.this.seekBar.setStep(MinMaxPropertyView.this.step);
        } else {
            MinMaxPropertyView.this.step = 1.0;
            MinMaxPropertyView.this.stepView.setText("1");
            MinMaxPropertyView.this.seekBar.setStep(MinMaxPropertyView.this.step);
        }
    }

    @Override
    public void getProperty() {
        super.getProperty();

        new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... params) {
                Object returnObj = null;
                try {
                    if (MinMaxPropertyView.this.minGetter != null)
                        returnObj = minGetter.invoke(MinMaxPropertyView.this.busObject);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                setMinView(o);
            }
        }.execute();

        new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... params) {
                Object returnObj = null;
                try {
                    if (MinMaxPropertyView.this.maxGetter != null)
                        returnObj = maxGetter.invoke(MinMaxPropertyView.this.busObject);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                setMaxView(o);
            }
        }.execute();

        new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... params) {
                Object returnObj = null;
                try {
                    if (MinMaxPropertyView.this.stepGetter != null)
                        returnObj = stepGetter.invoke(MinMaxPropertyView.this.busObject);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                setStepView(o);
            }
        }.execute();
    }
}