/*
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 */

package org.alljoyn.cdmcontroller.view.custom;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;

public class ParamDialog extends Dialog {
    public interface OnOkClickListener {

        public void onOkClick(Object[] params);
    }
    private OnOkClickListener listener;

    private String methodName;
    private ViewGroup rootView;
    private Button cancelButton;
    private Button okButton;
    private TextView[] valueViews;

    private Class<?>[] paramTypes;
    private String[] paramNames;

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
            ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_param, this.rootView, false);
            TextView nameView = (TextView)view.findViewById(R.id.name);
            this.valueViews[idx] = (TextView)view.findViewById(R.id.value);
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
                ParamDialog.this.dismiss();
            }
        });

        this.okButton = (Button)findViewById(R.id.btn_ok);
        this.okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (listener != null) {
                    Object[] params = new Object[ParamDialog.this.valueViews.length];
                    for (int i = 0; i < ParamDialog.this.valueViews.length; i++) {
                        if (ParamDialog.this.valueViews[i].getText().toString().isEmpty()) {
                            Toast.makeText(ParamDialog.this.getContext(), "Fill all Parameter", Toast.LENGTH_SHORT).show();
                            return;
                        }
                        params[i] = CdmUtil.parseParams(ParamDialog.this.paramTypes[i], ParamDialog.this.valueViews[i].getText())[0];
                    }
                    listener.onOkClick(params);
                }
                ParamDialog.this.dismiss();
            }
        });
    }

    private ParamDialog(Context context) {
        super(context , android.R.style.Theme_Translucent_NoTitleBar);
    }

    public ParamDialog(Context context, String methodName, Class<?>[] paramTypes, String[] paramNames,
                        OnOkClickListener listener) {
        this(context);
        this.methodName = methodName;
        this.paramTypes = paramTypes;
        this.paramNames = paramNames;
        this.valueViews = new TextView[paramTypes.length];
        this.listener = listener;
    }
}