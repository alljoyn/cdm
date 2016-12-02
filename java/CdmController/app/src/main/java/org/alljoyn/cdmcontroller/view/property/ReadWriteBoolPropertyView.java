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

package org.alljoyn.cdmcontroller.view.property;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.view.PropertyView;
import org.alljoyn.cdmcontroller.view.custom.ToggleButton;

public class ReadWriteBoolPropertyView extends PropertyView {
    private static final String TAG = "CDM_ReadWriteProperty";

    public ReadWriteBoolPropertyView(Context context, Object obj, String propertyName) {
        super(context, obj, propertyName, null);
    }

    private TextView nameView;
    private ToggleButton valueView;

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_bool_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valueView = (ToggleButton) view.findViewById(R.id.property_value);
        Log.d(TAG, "1: valueView is " + this.valueView.toString());

        this.nameView.setText(this.name);

        this.valueView.setOnToggleButtonListener(new ToggleButton.OnToggleButtonListener() {
            @Override
            public void onOnOffChanged(boolean value) {
                ReadWriteBoolPropertyView.this.setProperty(value);
            }
        });
    }

    @Override
    public void setValueView(Object value) {
        this.valueView.setValue(value);
    }
}