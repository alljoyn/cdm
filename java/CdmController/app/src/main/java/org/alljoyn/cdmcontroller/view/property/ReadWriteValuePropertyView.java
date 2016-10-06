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

import android.app.Activity;
import android.content.Context;
import android.text.InputType;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;

public class ReadWriteValuePropertyView extends PropertyView {
    private static final String TAG = "CDM_ReadWriteProperty";

    private TextView nameView;
    private TextView valueView;
    private TextView unitView;
    private Button submitBtn;

    boolean isSigned = true;

    public ReadWriteValuePropertyView(Context context, Object obj, String propertyName, String unit, boolean isSigned) {
        super(context, obj, propertyName, unit);
        this.isSigned = isSigned;
    }

    public ReadWriteValuePropertyView(Context context, Object obj, String propertyName, String unit) {
        this(context, obj, propertyName, unit, true);
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_readwrite_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valueView = (TextView) view.findViewById(R.id.property_value);
        this.unitView = (TextView) view.findViewById(R.id.property_unit);
        this.submitBtn = (Button) view.findViewById(R.id.submit);
        Log.d(TAG, "1: valueView is " + this.valueView.toString());

        if (this.valueGetter.getReturnType().isPrimitive()) {
            int flag = InputType.TYPE_CLASS_NUMBER;
            if (this.valueGetter.getReturnType() == Double.TYPE)
                flag |= InputType.TYPE_NUMBER_FLAG_DECIMAL;
            if (isSigned)
                flag |= InputType.TYPE_NUMBER_FLAG_SIGNED;
            this.valueView.setInputType(flag);
        }

        this.nameView.setText(this.name);
        if (this.unit != null && !this.unit.isEmpty())
            this.unitView.setText(this.unit);
        else
            this.unitView.setVisibility(View.GONE);

        valueView.setOnKeyListener(new OnKeyListener() {
            @Override
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                if (keyCode == KeyEvent.KEYCODE_ENTER) {
                    CdmUtil.hideKeyboard((Activity) ReadWriteValuePropertyView.this.getContext());
                }
                return false;
            }
        });

        this.submitBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                ReadWriteValuePropertyView.this.setProperty(ReadWriteValuePropertyView.this.valueView.getText().toString());
            }
        });
    }

    @Override
    public void setValueView(Object value) {
        this.valueView.setText(CdmUtil.toString(value));
    }
}