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

package org.alljoyn.cdmcontroller.view.method;

import android.content.Context;
import android.os.AsyncTask;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.view.custom.ParamDialog;

import java.lang.reflect.Method;

public class MethodView extends LinearLayout {
    private static final String TAG = "CDM_Method";

    protected Method method = null;

    protected Device device = null;

    private TextView nameView;
    protected ViewGroup resultLayout;
    protected TextView paramView;
    private TextView resultView;
    private Button submitBtn;
    protected String[] paramNames = null;
    private String objPath;
    private String interfaceName;
    private String methodName;

    public MethodView(Context context, Device obj, String objPath, String interfaceName, String methodName, String... paramNames) {
        super(context);
        this.method = null;
        this.device = obj;
        this.objPath = objPath;
        this.interfaceName = interfaceName;
        this.methodName = methodName;
        this.paramNames = paramNames;
        initView();
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_method, this, false);

        this.addView(view);
        this.resultLayout = (ViewGroup) view.findViewById(R.id.layout_result);
        this.resultLayout.setVisibility(View.GONE);
        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.paramView = (TextView) view.findViewById(R.id.params);
        this.resultView = (TextView) view.findViewById(R.id.result);

        this.submitBtn = (Button) view.findViewById(R.id.submit);

        this.submitBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                invokeMethod();
            }
        });

        this.nameView.setText(this.methodName);
    }

    protected void asyncMethodCall(Object[] params) {
        new AsyncTask<Object, Void, Object>() {
            @Override
            protected Object doInBackground(Object... params) {
                return MethodView.this.device.invokeMethod(MethodView.this.objPath, MethodView.this.interfaceName, MethodView.this.methodName, params);
            }

            @Override
            protected void onPostExecute(Object result) {
                MethodView.this.onResult(result);
            }
        }.execute(params);
    }

    protected void onResult(Object result) {
        if (result != null) {
            String strResult = "";
            if (result instanceof Object[]) {
                for (Object item : (Object[]) result) {
                    strResult += item.toString() + "\n";
                }
            } else
                strResult = result.toString();
            this.resultView.setText(strResult);
        }
        else {
            this.resultView.setText("No result  ");
        }
    }

    protected void invokeMethod() {
        if (paramNames != null) {
            Class<?>[] parameterTypes = this.device.getMethodParameterTypes(this.objPath, this.interfaceName, this.methodName);
            ParamDialog mDialog = new ParamDialog(getContext(), this.methodName, parameterTypes, this.paramNames, new ParamDialog.OnOkClickListener() {
                @Override
                public void onOkClick(Object[] params) {
                    MethodView.this.resultLayout.setVisibility(View.VISIBLE);
                    String strParam = "[ ";
                    for (Object param : params) {
                        strParam += param.toString() + " ";
                    }
                    strParam += "]";
                    MethodView.this.paramView.setText(strParam);
                    asyncMethodCall(params);
                }
            });
            mDialog.show();
        } else {
            asyncMethodCall(null);
        }
    }
}