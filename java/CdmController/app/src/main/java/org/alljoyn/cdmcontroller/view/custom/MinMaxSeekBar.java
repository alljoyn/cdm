/*
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

package org.alljoyn.cdmcontroller.view.custom;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.SeekBar;

import org.alljoyn.cdmcontroller.R;

public class MinMaxSeekBar extends LinearLayout {

    public interface OnMinMaxSeekBarChangeListener {

        void onProgressChanged(SeekBar seekBar, double value);

        void onStopTrackingTouch(SeekBar seekBar, double value);
    }

    SeekBar.OnSeekBarChangeListener seekBarListener = new SeekBar.OnSeekBarChangeListener() {
        boolean isDrag = false;
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if (MinMaxSeekBar.this.listener != null && fromUser) {
                MinMaxSeekBar.this.value = progress * MinMaxSeekBar.this.step + MinMaxSeekBar.this.min;
                MinMaxSeekBar.this.listener.onProgressChanged(seekBar, MinMaxSeekBar.this.value);
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
            if (MinMaxSeekBar.this.listener != null)
                MinMaxSeekBar.this.listener.onStopTrackingTouch(seekBar, MinMaxSeekBar.this.value);
        }
    };

    private OnMinMaxSeekBarChangeListener listener = null;
    private double min = 0;
    private double max = 0;
    private double value = 0;
    private double step = 1;
    private SeekBar seekBar;

    public MinMaxSeekBar(Context context) {
        super(context);
        InitView();
    }

    public MinMaxSeekBar(Context context, AttributeSet attrs) {
        super(context, attrs);
        InitView();
    }

    public MinMaxSeekBar(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        InitView();
    }

    private void InitView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.min_max_seekbar, this, false);
        this.addView(view);

        this.seekBar = (SeekBar) view.findViewById(R.id.seekBar);
    }

    public synchronized void setMax(double max) {
        this.max = max;
        this.seekBar.setMax((int) ((this.max - this.min) / this.step));
    }

    public synchronized void setProgress(double progress) {
        this.value = progress;
        this.seekBar.setProgress((int) ((this.value - this.min) / this.step));
    }

    public synchronized void setMin(double min) {
        this.min = min;
        this.seekBar.setMax((int) ((this.max - this.min) / this.step));
        this.setProgress(this.value);
    }

    public synchronized void setStep(double step) {
        if (step == 0) return;
        this.step = step;
        this.seekBar.setMax((int) ((this.max - this.min) / this.step));
        this.setProgress(this.value);
    }

    public synchronized double getProgress() {
        return this.seekBar.getProgress() * this.step + this.min;
    }

    public void setOnSeekBarChangeListener(OnMinMaxSeekBarChangeListener listener) {
        this.listener = listener;
        if (listener == null)
            this.seekBar.setOnSeekBarChangeListener(null);
        else
            this.seekBar.setOnSeekBarChangeListener(this.seekBarListener);
    }


}