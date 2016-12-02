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
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.view.PropertyView;
import org.alljoyn.smartspaces.EnumBase;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;

public class ReadOnlyEnumPropertyView<T extends EnumBase<?>> extends PropertyView {
    private static final String TAG = "CDM_ReadWriteProperty";

    private TextView nameView;
    private TextView valueView;

    private Class<T> clazz;

    public ReadOnlyEnumPropertyView(Context context, Object obj, String propertyName, Class<T> clazz) {
        super(context, obj, propertyName, null);
        this.clazz = clazz;
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_readonly_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valueView = (TextView) view.findViewById(R.id.property_value);
        view.findViewById(R.id.property_value_ext).setVisibility(View.GONE);
        view.findViewById(R.id.property_unit).setVisibility(View.GONE);
        Log.d(TAG, "1: valueView is " + this.valueView.toString());

        this.nameView.setText(this.name);
    }

    @Override
    public void setValueView(Object value) {
        T item = (T)CdmUtil.findEnum(value, this.clazz);
        if (item != null) {
            this.valueView.setText(item.toString());
        } else {
            this.valueView.setText("Undefined");
        }
    }
}