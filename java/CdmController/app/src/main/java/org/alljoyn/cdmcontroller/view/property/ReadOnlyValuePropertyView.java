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
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;

public class ReadOnlyValuePropertyView extends PropertyView {
    private TextView nameView;
    private TextView valueView;
    private TextView valueViewExt;
    private TextView unitView;

    public ReadOnlyValuePropertyView(Context context, Object obj, String propertyName, String unit) {
        super(context, obj, propertyName, unit);
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup)inflater.inflate(R.layout.view_readonly_property, this, false);

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

    @Override
    public void setValueView(Object value) {
        if (value.getClass().isArray()){
            this.valueView.setText("");
            this.valueViewExt.setVisibility(View.VISIBLE);
            this.valueViewExt.setText(CdmUtil.toString(value));
        } else {
            this.valueView.setText(CdmUtil.toString(value));
        }
    }
}