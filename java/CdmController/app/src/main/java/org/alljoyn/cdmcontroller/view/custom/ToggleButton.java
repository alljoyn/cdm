/*
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

package org.alljoyn.cdmcontroller.view.custom;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import org.alljoyn.cdmcontroller.R;

public class ToggleButton extends LinearLayout {

    public interface OnToggleButtonListener{
        void onOnOffChanged(boolean value);
    }

    private OnToggleButtonListener listener = null;
    private boolean value = false;
    private ImageView toggleButton;
    private View toggleButtonDisable;

    public ToggleButton(Context context) {
        super(context);
        InitView();
    }

    public ToggleButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        InitView();
    }

    public ToggleButton(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        InitView();
    }

    private void InitView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.toggle_button, this, false);
        this.addView(view);

        this.toggleButtonDisable = view.findViewById(R.id.toggle_btn_disable);
        this.toggleButton = (ImageView) view.findViewById(R.id.toggle_btn);
        this.toggleButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ToggleButton.this.setOnOff();
                if (ToggleButton.this.listener == null)
                    return;

                ToggleButton.this.listener.onOnOffChanged(ToggleButton.this.value);
            }
        });
    }

    private void setDisable() {
        this.toggleButton.setVisibility(View.GONE);
        toggleButtonDisable.setVisibility(View.VISIBLE);
        this.toggleButton.setOnClickListener(null);
    }

    private void setOnOff() {
        setValue(!this.value);
    }

    public void setValue(boolean onOff) {
        if (this.value == onOff)
            return;
        this.value = onOff;
        if (this.value)
            this.toggleButton.setImageResource(R.drawable.toggle_btn_on);
        else
            this.toggleButton.setImageResource(R.drawable.toggle_btn_off);
    }

    public void setValue(Object onOff) {
        if (onOff instanceof Boolean) {
            setValue(onOff.equals(true));
            return;
        }

        String value = onOff.toString();
        if (value.toLowerCase().equals("-1")) {
            setDisable();
            return;
        }
        setValue(value.equals("0") ? false : true);
    }


    public void setOnToggleButtonListener(OnToggleButtonListener listener) {
        this.listener = listener;
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }
}