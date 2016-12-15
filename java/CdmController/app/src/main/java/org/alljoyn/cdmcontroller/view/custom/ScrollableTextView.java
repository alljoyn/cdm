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
import android.graphics.Rect;
import android.graphics.RectF;
import android.text.method.ScrollingMovementMethod;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;

public class ScrollableTextView extends TextView {


    public ScrollableTextView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        setVerticalScrollBarEnabled(true);
        setHorizontallyScrolling(true);
        this.setMovementMethod(new ScrollingMovementMethod());
        this.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                View childV = findViewById(R.id.result);
                if (childV != null) {
                    int[] l = new int[2];
                    childV.getLocationOnScreen(l);
                    RectF rect = new RectF(l[0], l[1], l[0] + childV.getWidth(), l[1] + childV.getHeight());
                    if (rect.contains(event.getX(), event.getY())) {
                        childV.getParent()
                                .requestDisallowInterceptTouchEvent(false);
                        childV.onTouchEvent(event);
                        return true;
                    }
                    childV.getParent().requestDisallowInterceptTouchEvent(true);
                }
                return false;
            }
        });
    }

    public ScrollableTextView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setVerticalScrollBarEnabled(true);
        setHorizontallyScrolling(true);
        this.setMovementMethod(new ScrollingMovementMethod());
        this.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                View childV = findViewById(R.id.result);
                if (childV != null) {
                    int[] l = new int[2];
                    childV.getLocationOnScreen(l);
                    RectF rect = new RectF(l[0], l[1], l[0] + childV.getWidth(), l[1] + childV.getHeight());
                    if (rect.contains(event.getX(), event.getY())) {
                        childV.getParent()
                                .requestDisallowInterceptTouchEvent(false);
                        childV.onTouchEvent(event);
                        return true;
                    }
                    childV.getParent().requestDisallowInterceptTouchEvent(true);
                }
                return false;
            }
        });
    }

    public ScrollableTextView(Context context) {
        super(context);
        setVerticalScrollBarEnabled(true);
        setHorizontallyScrolling(true);
        this.setMovementMethod(new ScrollingMovementMethod());
        this.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                View childV = findViewById(R.id.result);
                if (childV != null) {
                    int[] l = new int[2];
                    childV.getLocationOnScreen(l);
                    RectF rect = new RectF(l[0], l[1], l[0] + childV.getWidth(), l[1] + childV.getHeight());
                    if (rect.contains(event.getX(), event.getY())) {
                        childV.getParent()
                                .requestDisallowInterceptTouchEvent(false);
                        childV.onTouchEvent(event);
                        return true;
                    }
                    childV.getParent().requestDisallowInterceptTouchEvent(true);
                }
                return false;
            }
        });
    }
    @Override
    protected void onFocusChanged(boolean focused, int direction, Rect previouslyFocusedRect) {
        if(focused)
            super.onFocusChanged(focused, direction, previouslyFocusedRect);
    }

    @Override
    public void onWindowFocusChanged(boolean focused) {
        if(focused)
            super.onWindowFocusChanged(focused);
    }

    @Override
    public boolean isFocused() {
        return true;
    }
} 