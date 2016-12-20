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

package org.alljoyn.cdmcontroller.view.custom;

import android.app.Dialog;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.smartspaces.EnumBase;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ParamSupportedEnumDialog<T extends EnumBase<T>> extends Dialog {
    public interface OnOkClickListener {

        public void onOkClick(Object[] params);
    }
    private OnOkClickListener listener;

    private String methodName;
    private ViewGroup rootView;
    private Button cancelButton;
    private Button okButton;
    private View[] valueViews;

    private Class<?>[] paramTypes;
    private String[] paramNames;
    private String[] supportedParamNames;
    private Class<T>[] clazzes;

    private SupportedEnumParam[] supportedEnumParams;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        WindowManager.LayoutParams lpWindow = new WindowManager.LayoutParams();
        lpWindow.flags = WindowManager.LayoutParams.FLAG_DIM_BEHIND;
        lpWindow.dimAmount = 0.8f;
        getWindow().setAttributes(lpWindow);

        setContentView(R.layout.page_param);

        this.rootView = (ViewGroup) findViewById(R.id.property_body);
        int idx = 0;
        for (Class<?> type : this.paramTypes) {
            LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_param_supported, this.rootView, false);
            TextView nameView = (TextView)view.findViewById(R.id.name);
            //if (type instanceof EnumBase<?>)
            TextView textView = (TextView)view.findViewById(R.id.value);
            Spinner spinnerView = (Spinner)view.findViewById(R.id.value_supported);
          //  this.valueViews[idx] = (TextView)view.findViewById(R.id.value);
            if (supportedParamNames[idx] == null || supportedParamNames[idx].isEmpty()) {
                ViewGroup.LayoutParams txt_params = textView.getLayoutParams();
                txt_params.height = txt_params.height;
                txt_params.width = 150;
                textView.setLayoutParams(txt_params);
                textView.setVisibility(View.VISIBLE);

                ViewGroup.LayoutParams sp_params = spinnerView.getLayoutParams();
                sp_params.height = sp_params.height;
                sp_params.width = 0;
                spinnerView.setLayoutParams(sp_params);
                spinnerView.setVisibility(View.INVISIBLE);
                this.valueViews[idx] = textView;
                supportedEnumParams[idx] = null;
            } else {
                ViewGroup.LayoutParams txt_params = textView.getLayoutParams();
                txt_params.height = txt_params.height;
                txt_params.width = 0;
                textView.setLayoutParams(txt_params);
                textView.setVisibility(View.INVISIBLE);

                ViewGroup.LayoutParams sp_params = spinnerView.getLayoutParams();
                sp_params.height = sp_params.height;
                sp_params.width = 150;
                spinnerView.setLayoutParams(sp_params);

                ArrayAdapter<T> valuesSupportedAdapter = new ArrayAdapter<T>(this.getContext(), android.R.layout.simple_spinner_item);
                spinnerView.setAdapter(valuesSupportedAdapter);
                supportedEnumParams[idx] = new SupportedEnumParam(supportedParamNames[idx], clazzes[idx],
                        valuesSupportedAdapter, busObject);

                this.valueViews[idx] = spinnerView;
                //  view.findViewById(R.id.property_unit).setVisibility(View.GONE);

            }
            if (paramNames != null) {
                nameView.setText(this.paramNames[idx]);
            } else {
                nameView.setText(type.getName());
            }
            this.rootView.addView(view);
            idx++;
        }

        this.cancelButton = (Button)findViewById(R.id.btn_cancle);
        this.cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ParamSupportedEnumDialog.this.dismiss();
            }
        });

        this.okButton = (Button)findViewById(R.id.btn_ok);
        this.okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (listener != null) {
                    Object[] params = new Object[ParamSupportedEnumDialog.this.valueViews.length];
                    for (int i = 0; i < ParamSupportedEnumDialog.this.valueViews.length; i++) {
                        View vi = ParamSupportedEnumDialog.this.valueViews[i];
                        if (vi instanceof TextView) {
                            if (((TextView) vi).getText().toString().isEmpty()) {
                                Toast.makeText(ParamSupportedEnumDialog.this.getContext(), "Fill all Parameter", Toast.LENGTH_SHORT).show();
                                return;
                            }
                            params[i] = CdmUtil.parseParams(ParamSupportedEnumDialog.this.paramTypes[i], ((TextView)vi).getText())[0];

                        }
                        if (vi instanceof Spinner) {
                            if (((Spinner) vi).getSelectedItem().toString().isEmpty()) {
                                Toast.makeText(ParamSupportedEnumDialog.this.getContext(), "Fill all Parameter", Toast.LENGTH_SHORT).show();
                                return;
                            }
                            T item = (T)((Spinner) vi).getSelectedItem();
                            params[i] = CdmUtil.parseParams(ParamSupportedEnumDialog.this.paramTypes[i], item.toValue()) [0];
                        }
                    }
                    listener.onOkClick(params);
                }
                ParamSupportedEnumDialog.this.dismiss();
            }
        });
        getSupportedParams();
    }

    private void getSupportedParams() {
        for (SupportedEnumParam item : supportedEnumParams)
        {
            if (item != null)
                item.getSupportedProperty();
        }
    }

    private ParamSupportedEnumDialog(Context context) {
        super(context , android.R.style.Theme_Translucent_NoTitleBar);
    }

    protected Object busObject;

    public ParamSupportedEnumDialog(Context context, Object obj, String methodName, Class<?>[] paramTypes, String[] paramNames,
                                    String[] supportedParamNames, Class<T>[] clazzes,
                                    OnOkClickListener listener) {
        this(context);
        this.methodName = methodName;
        this.paramTypes = paramTypes;
        this.paramNames = paramNames;
        this.supportedParamNames = supportedParamNames;
        this.valueViews = new View[paramTypes.length];

        this.busObject = obj;

        this.clazzes = clazzes;
        this.supportedEnumParams = new SupportedEnumParam[paramTypes.length];
        this.listener = listener;
    }
/*
    public void onPropertiesChangedSignal(String name, Variant value) {
        Object obj = null;
        try {
            obj = value.getObject(this.valueGetter.getReturnType());
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        if (name.equals(this.supportedParamName)) {
            setSupportedEnumView(obj);
        }
    }
*/

    private class SupportedEnumParam<T extends EnumBase<T>>
    {
        private String supportedParamName;
        private Class<T> clazz;
        private ArrayAdapter<T> valuesSupportedAdapter;
        private Method supportedGetter = null;

        public SupportedEnumParam(String supportedParamName, Class<T> clazz,
                                  ArrayAdapter<T> valuesSupportedAdapter, Object obj)
        {
            this.supportedParamName = supportedParamName;
            this.clazz = clazz;
            this.valuesSupportedAdapter = valuesSupportedAdapter;
            try {
                this.supportedGetter = obj.getClass().getMethod("get" + supportedParamName);
            } catch (NoSuchMethodException e) {
                this.supportedGetter = null;
            }
        }
        public void getSupportedProperty() {

            AsyncTask<Void, Void, Object> execute = new AsyncTask<Void, Void, Object>() {

                @Override
                protected Object doInBackground(Void... voids) {
                    Object returnObj = null;
                    try {
                        if (supportedGetter != null) {
                            Class<?>[] paramTypes = supportedGetter.getParameterTypes();
                            Object[] params = new Object[paramTypes.length];
                            int idx = 0;
                            returnObj = supportedGetter.invoke(ParamSupportedEnumDialog.this.busObject);
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
                    setSupportedEnumView(o);
                }
            }.execute();
        }
        private void setSupportedEnumView(Object enumList) {
            if (enumList != null) {
                valuesSupportedAdapter.clear();
                for (Object obj : CdmUtil.toObjectArray(enumList)) {
                    T item = (T) CdmUtil.findEnum(obj, clazz);
                    valuesSupportedAdapter.add(item);
                }
            }

        }
    }
}